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

using namespace std;

Move find_best_greedy_move(vector<Move> moves, Position position){

	Move maxMove(0,0,0,0);
	int maxValue = -1000; // Include <climits> for INT_MIN
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


map<Move, int> get_max(map<Move, int> a, map<Move, int> b){

	int valA = a.begin() -> second;
	int valB = b.begin() -> second;

	if(valA > valB) return a;
	else return b;



}

map<Move, int> get_min(map<Move, int> a, map<Move, int> b){

	int valA = a.begin() -> second;
	int valB = b.begin() -> second;

	cout << "VAL A " << valA << endl;

	if(valA < valB) return a;
	else return b;

}

// Try 1
//map<Move, int> minimax(Move move, Position position, int depth, bool maximizingPlayer){ // move is just a place holder at start
//	if(depth == 0){
//		vector<int> state_values = position.get_state_value(); // split to white and black
//		map<Move, int> action_value;
//		int state_value = 0;
//
//		if(position._turn == WHITE) state_value = state_values[0] - state_values[1];
//		else if(position._turn == BLACK) state_value = state_values[1] - state_values[0];
//
//		action_value[move] = state_value;
//		cout << "Max depth reached: " << state_value << endl;
//
//		return action_value; 
//	}
//
//	vector<Move> moves = position.generate_legal_moves();
//	cout << "starting evaluation" << endl;
//	if(maximizingPlayer){
//		int maxEval = -999;
//		Move init_move(0,0,0,0);
//
//		map<Move, int> maxMove;
//		maxMove[init_move] = maxEval;
//		for(auto m: moves){ //getting all legal moves (children)
//			Position test_position = position; 
//			test_position.make_move(m);
//			map<Move, int> moveEval = minimax(m, test_position, depth - 1, false);
//			maxMove = get_max(maxMove, moveEval);
//		}
//
//		return maxMove;
//	}
//	if(!maximizingPlayer){
//		int minEval = +999;
//		Move init_move(0,0,0,0);
//
//		map<Move, int> minMove;
//		minMove[init_move] = minEval;
//
//		for(auto m: moves){ //getting all legal moves (children)
//			Position test_position = position; 
//			test_position.make_move(m);
//			map<Move, int> moveEval = minimax(m, test_position, depth - 1, true);
//			minMove = get_min(minMove, moveEval);
//		}
//
//		return minMove;
//	}
//
//
//}

// Try 2
//map<Move, int> minimax(Move move, Position position, int depth, bool maximizingPlayer, auto g) {
//	if (depth == 0) {
//		vector<int> state_values = position.get_state_value(); 
//		map<Move, int> action_value;
//		int state_value = 0;
//
//		if (position._turn == BLACK) state_value = state_values[0] - state_values[1];
//		else if (position._turn == WHITE) state_value = state_values[1] - state_values[0];
//
//		action_value[move] = state_value;
//
//		return action_value;
//	}
//
//	vector<Move> moves = position.generate_legal_moves();
//	shuffle(moves.begin(), moves.end(), g);
//
//	if (maximizingPlayer) {
//		int maxEval = -999;
//		Move bestMove(0,0,0,0); 
//
//		for (auto& m : moves) {
//			Position test_position = position;
//			test_position.make_move(m);
//			map<Move, int> moveEval = minimax(m, test_position, depth - 1, false, g);
//			int currentEval = moveEval.begin()->second; 
//
//			if (currentEval > maxEval) {
//				maxEval = currentEval;
//				bestMove = m;
//			}
//		}
//
//		map<Move, int> bestMoveMap;
//		bestMoveMap[bestMove] = maxEval;
//		return bestMoveMap;
//	} else { 
//		int minEval = 999;
//		Move bestMove(0,0,0,0);
//
//		for (auto& m : moves) {
//			Position test_position = position;
//			test_position.make_move(m);
//			map<Move, int> moveEval = minimax(m, test_position, depth - 1, true, g);
//			int currentEval = moveEval.begin()->second;
//
//			if (currentEval < minEval) {
//				minEval = currentEval;
//				bestMove = m;
//			}
//		}
//
//		map<Move, int> bestMoveMap;
//		bestMoveMap[bestMove] = minEval;
//		return bestMoveMap;
//	}
//}


// Try 3
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

Move getBestMove(Position position, int depth) {
	int bestValue = -999;
	Move bestMove(0,0,0,0);
	vector<Move> moves = position.generate_legal_moves();

	for (const Move& m : moves) {
		Position test_position = position; 
		test_position.make_move(m);
		int moveValue = minimax(test_position, depth - 1, false); 
		cout << moveValue << endl;

		if (moveValue > bestValue) {
			cout << "Best HIT" << moveValue << " " << bestValue << endl;
			bestValue = moveValue;
			bestMove = m;
		}
	}

	return bestMove;
}


int main(){
	random_device rd;
	mt19937 g(rd()); // initializing a random seed;

		// Initial position.
		Position position;
	vector<Move> moves;
	moves = position.generate_legal_moves();
//	map<Move, int> action_value;
	


		while (!moves.empty()){
		string input_move_string;
		cout << "Printing out all moves: " << endl;
		for(auto m: moves) m.print_move();
//		action_value.clear();

				position.print();
		cout << "Input your move: ";
		cin >> input_move_string;
//		bool possible_move= true;
		Move new_move(input_move_string);

//		if (!count(moves.begin(),moves.end(), new_move)) continue; // checking if moves exist
		if (!count(moves.begin(),moves.end(), new_move)) cout << "GAME OVER!!!!"; // checking if moves exist

//		Move maxMove = find_best_move(moves, position);
//		map<Move, int> maxMoveMap = minimax(Move(1,1,1,1), position, 3, true, g);
//		Move maxMove = maxMoveMap.begin() -> first;
		Move maxMove = getBestMove(position, 4);

		cout << "MAX MOVE MADE:::" << endl;
		maxMove.print_move();
		position.make_move(maxMove);
		moves.clear();
		moves = position.generate_legal_moves();


		
		cout << "values are: " << position.get_state_value()[0] << " " << position.get_state_value()[1] << endl;
	}
	

		return 0;
}
