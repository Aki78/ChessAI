#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "position.h"
#include "move.h"
#include <map>
#include <climits>
#include <algorithm>
#include <random>
#include <mutex>
#include<atomic>
#include<thread>

using namespace std;

Move find_best_greedy_move(vector<Move> moves, Position position){

	Move maxMove(0,0,0,0);
	int maxValue = -100000; 
	map<Move, int> action_value;

	for(auto m: moves){ // trying out moves to get state action values
		Position test_position = position; // copying new position for test
		test_position.make_move(m);
		vector<int> state_values = test_position.get_state_value();
		int state_value = 0;
		if(position._turn == WHITE) state_value = state_values[0] - state_values[1];
		else if(position._turn == BLACK) state_value = state_values[1] - state_values[0];
		cout << "values are: " <<state_values[0] << " " << state_values[1] << endl;
		cout << "action is: " << endl;
		m.print_move();
		cout << "state value is: " << state_value << endl;
		action_value[m] = state_value;
		cout << "size is: " << action_value.size();
	}

	for (const auto& pair : action_value) {
		cout << pair.second << endl;
		if (pair.second > maxValue) {
			maxValue = pair.second;
			maxMove = pair.first;
			maxMove.print_move();
		}
	}

	return maxMove;
}


// Try 3 still very dumb, can't do more than depth = 4
int minimax(Position position, int depth, bool maximizingPlayer){ // move is just a place holder at start
	if(depth == 0){
		vector<int> state_values = position.get_state_value(); // split to white and black
		int state_value = 0;

		if(position._turn == WHITE) state_value = state_values[0] - state_values[1];
		else if(position._turn == BLACK ) state_value = state_values[1] - state_values[0];

//		cout << "Max depth reached: " << state_value << endl;

		return state_value; 
	}

	vector<Move> moves = position.generate_legal_moves();
	//cout << "starting evaluation" << endl;
	if(maximizingPlayer){
		int maxEval = -99999;

		for(auto m: moves){ //getting all legal moves (children)
			Position test_position = position; 
			test_position.make_move(m);
			int moveEval = minimax(test_position, depth - 1, false);
			maxEval = max(maxEval, moveEval);
		}

//	cout << "starting evaluation: " << maxEval <<endl;
		return maxEval;
	}
	else if(!maximizingPlayer){
		int minEval = +99999;

		for(auto m: moves){ //getting all legal moves (children)
			Position test_position = position; 
			test_position.make_move(m);
			int moveEval = minimax(test_position, depth - 1, true);
			minEval = min(minEval, moveEval);
		}

		return minEval;
	}
}


//Try4 with alpha beta pruning, can do depth of 5 now,
// even 6 if you wait minutes per tern,
// but with a bad evaluation function, still bad
int minimax_alphabeta(Position& position, int depth, bool maximizingPlayer, int alpha, int beta){ // move is just a place holder at start
	if(depth == 0){
		vector<int> state_values = position.get_state_value(); // split to white and black
		int state_value = 0;

		if(position._turn == BLACK) state_value = state_values[0] - state_values[1];
		else if(position._turn == WHITE ) state_value = state_values[1] - state_values[0];

//		cout << "Max depth reached: " << state_value << endl;

		return state_value; 
	}

	vector<Move> moves = position.generate_legal_moves();
	//cout << "starting evaluation" << endl;
	if(maximizingPlayer){
		int maxEval = -99999;

		for(auto m: moves){ //getting all legal moves (children)
			Position test_position = position; 
			test_position.make_move(m);
			int moveEval = minimax_alphabeta(test_position, depth - 1, false, alpha, beta);
			maxEval = max(maxEval, moveEval);
			alpha = max(alpha, moveEval);
			if (beta <= alpha) break; 
		}

//	cout << "starting evaluation: " << maxEval <<endl;
		return maxEval;
	}
	else {
		int minEval = +99999;

		for(auto m: moves){ //getting all legal moves (children)
			Position test_position = position; 
			test_position.make_move(m);
			int moveEval = minimax_alphabeta(test_position, depth - 1, true, alpha, beta);
			minEval = min(minEval, moveEval);
			beta = min(beta, moveEval);
			if (beta <= alpha) break; 
		}

		return minEval;
	}
}

Move getBestMove(Position position, int depth, auto g) {
	int bestValue = -99999;
	Move bestMove(0,0,0,0);
	vector<Move> moves = position.generate_legal_moves();
	int alpha = -99999;
	int beta = +99999;

	shuffle(moves.begin(), moves.end(), g);

	for (const Move& m : moves) {
		Position test_position = position; 
		test_position.make_move(m);
		int moveValue = minimax_alphabeta(test_position, depth - 1, false, alpha, beta); 

		if (moveValue > bestValue) {
			bestValue = moveValue;
			bestMove = m;
		}

		alpha = max(alpha, bestValue);
		if (beta <= alpha) break;
	}

	return bestMove;
}


// with thread, it can go deepth 7 or even 8
Move getBestMoveThread(Position position, int depth, auto g) {
	vector<Move> moves = position.generate_legal_moves();
	shuffle(moves.begin(), moves.end(), g);

	atomic<int> bestValue(-99999);
	Move bestMove(0,0,0,0);
	mutex bestMoveMutex;

	int alpha = -99999;
	int beta = 99999;

	// determine the number of threads to use 
	unsigned num_threads = thread::hardware_concurrency();
	vector<thread> threads(num_threads);

	auto processMoves = [&](int start, int end) {
		int localBestValue = -99999;
		Move localBestMove(0,0,0,0);
		int localAlpha = alpha, localBeta = beta;

		for (int i = start; i < end; ++i) {
			Position test_position = position;
			test_position.make_move(moves[i]);
			int moveValue = minimax_alphabeta(test_position, depth - 1, false, localAlpha, localBeta);

			if (moveValue > localBestValue) {
				localBestValue = moveValue;
				localBestMove = moves[i];
			}

			localAlpha = max(localAlpha, localBestValue);
			if (localBeta <= localAlpha) break;
		}

		lock_guard<mutex> lock(bestMoveMutex);
		if (localBestValue > bestValue) {
			bestValue = localBestValue;
			bestMove = localBestMove;
		}
	};

	// divide the work among the threads
	int moves_per_thread = moves.size() / num_threads;
	for (int i = 0; i < num_threads; ++i) {
		int start = i * moves_per_thread;
		int end = (i + 1) * moves_per_thread;
		if (i == num_threads - 1) {
			end = moves.size(); // ensure the last thread picks up the remainder
		}

		threads[i] = thread(processMoves, start, end);
	}

	for (auto& t : threads) {
		if (t.joinable()) {
			t.join();
		}
	}

	return bestMove;
}



int main(){
	random_device rd;
	mt19937 g(rd()); // initializing a random seed;
	int depth = 5;

		// Initial position.
	Position position;
//	double current_value;

//	double total_value = (double) (position.get_state_value()[0] + position.get_state_value()[1]);
	vector<Move> moves;
	moves = position.generate_legal_moves();
//	map<Move, int> action_value;
	int select;
	while(select != 1 and select != 2 and select != 3){
		cout << "1: AI vs AI. 2: AI(BLACK) vs HUMAN. 3: HUMAN vs AI(WHITE)" << endl; 
		cin >> select;
	}

// AI playing
	if(select == 1)
		while (!moves.empty()){
			if (position.get_state_value()[0] + position.get_state_value()[1]  < 100) depth = 6;
			if (position.get_state_value()[0] + position.get_state_value()[1]  < 90) depth = 7;
			if (position.get_state_value()[0] + position.get_state_value()[1]  < 80) depth = 8;
			if (position.get_state_value()[0] + position.get_state_value()[1]  < 70) depth = 9;
			if (position.get_state_value()[0] + position.get_state_value()[1]  < 60) depth = 10;
			if (position.get_state_value()[0] + position.get_state_value()[1]  < 50) depth = 11;
			position.print();
			Move maxMove = getBestMoveThread(position, depth, g);
			maxMove.print_move();
			position.make_move(maxMove);
			moves.clear();
			moves = position.generate_legal_moves();
		}


	else if(select == 2)
		while (!moves.empty()){
			string input_move_string;
			if(position._turn == WHITE){
				cout << "Printing out all moves: " << endl;

				for(auto m: moves) m.print_move();

				position.print();
				cout << "Input your move: ";
				cin >> input_move_string;

				Move new_move(input_move_string);

				if (!count(moves.begin(),moves.end(), new_move)) continue; // checking if input moves exist

				position.make_move(new_move);
				moves.clear();
				moves = position.generate_legal_moves();
			}else{
				position.print();
				Move maxMove = getBestMoveThread(position, 5, g);
				maxMove.print_move();
				position.make_move(maxMove);
				moves.clear();
				moves = position.generate_legal_moves();

			} 

			
		}
	else if(select == 3)
		while (!moves.empty()){
			string input_move_string;
			if(position._turn == BLACK){
				cout << "Printing out all moves: " << endl;

				for(auto m: moves) m.print_move();

				position.print();
				cout << "Input your move: ";
				cin >> input_move_string;

				Move new_move(input_move_string);

				if (!count(moves.begin(),moves.end(), new_move)) continue; // checking if input moves exist

				position.make_move(new_move);
				moves.clear();
				moves = position.generate_legal_moves();
			}else{
				position.print();
				Move maxMove = getBestMoveThread(position, 5, g);
				maxMove.print_move();
				position.make_move(maxMove);
				moves.clear();
				moves = position.generate_legal_moves();

			} 

			
		}



	if(position._turn == WHITE) cout << "Winnter: BLACK" << endl;
	if(position._turn == BLACK) cout << "Winnter: WHITE" << endl;

	

		return 0;
}
