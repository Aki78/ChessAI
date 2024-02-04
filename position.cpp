#include <iostream>
#include <string>
#include <vector>
#include "position.h"
#include "piece.h"
using namespace std;

// Clears the board
void Position::clear() {
	for (int row = 0; row < 8; ++row)
		for (int column = 0; column < 8; ++column)
			_board[row][column] = NA;
}

// Execute a move
void Position::make_move(const Move& m) {
	
	int piece = _board[m._start_row][m._start_column]; // Store the piece in the starting square.

	_board[m._start_row][m._start_column] = NA; // Clear the starting square
	_board[m._end_row][m._end_column] = piece; // Place the original piece in the destination square

	switch_turns();
}

bool Position::check_and_push_move(int row, int column, int player, vector<Move>& moves){ // woudl this logic really work?

	if (row < 0 || row > 7 || column < 0 || column > 7) return true; // Off the board?
	if (_board[row][column] == NA){ // Empty square?
		moves.push_back(Move(row, column, row, column));
		return false; // false in thise case meens success and continue
	}
	if (piece_color(_board[row][column]) == player) return true; // Encounter own piece?
	
	moves.push_back(Move(row, column, row, column)); // Capture opponent's piece.
	return true;

}
bool Position::check_pawn_and_push_move(vector<int> move,int row, int column, int player, vector<Move>& moves){ // woudl this logic really work?
// bool depricated, it used to be used for breaking while loops

	if (row < 0 || row > 7 || column < 0 || column > 7) return true; // Off the board?
	if (_board[row][column] == NA){ // Empty square?
		moves.push_back(Move(row, column, row, column));
		return false; // false in thise case meens success and continue
	}
	if (piece_color(_board[row][column]) == player) return true; // Encounter own piece?
	if (piece_color(_board[row][column]) != player and (move[0]==0 and (move[1]==1 || move[1] ==-1) )) return true; // Enemy piece infront?

	if (_board[row][column] == NA){ // Empty square?
		moves.push_back(Move(row, column, row, column));
		return false; // false in thise case meens success and continue
	}
	
	if (piece_color(_board[row][column]) != player and (move[0]==1 || move[0]== -1) and (move[1]==1 || move[1] ==-1) )  
		moves.push_back(Move(row, column, row, column)); // Capture opponent's piece.
	return true;

}

// Generate rook's raw moves
void Position::give_rook_raw_moves(int row, int column, int player, vector<Move>& moves) {
	// Up
	int current_row = row;
	int current_column = column;

	while (true) {
		current_row--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;

	while (true) {
		current_row++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;

	while (true) {
		current_column--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_column = column;

	while (true) {
		current_column++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

}


void Position::give_bish_raw_moves(int row, int column, int player, vector<Move>& moves) {
	// Up
	int current_row = row;
	int current_column = column;

	while (true) {
		current_row--;
		current_column--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;

	while (true) {
		current_row++;
		current_column--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;


	while (true) {
		current_row--;
		current_column++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;

	while (true) {
		current_row++;
		current_column++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

}


void Position::give_queen_raw_moves(int row, int column, int player, vector<Move>& moves) {
	int current_row = row;
	int current_column = column;

	while (true) {
		current_row--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;

	while (true) {
		current_row++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;

	while (true) {
		current_column--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_column = column;

	while (true) {
		current_column++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_column = column;


	while (true) {
		current_row--;
		current_column--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;

	while (true) {
		current_row++;
		current_column--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;


	while (true) {
		current_row--;
		current_column++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;

	while (true) {
		current_row++;
		current_column++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}


}


void Position::give_nite_or_king_raw_moves(char type, int row, int column, int player, vector<Move>& moves) { // sanity check moves later

	int current_row = row;
	int current_column = column;
	vector<vector<int>> possible_moves;

	switch(type) {
//		case 'R':
//				possible_moves = {{0,-4},{0,-3},{0,-2},{0,-1},{0,1},{0,2},{0,3},{0,4},
//						 {-4,0},{-3,0},{-2,0},{-1,0},{1,0},{2,0},{3,0},{4,0}};
//			break;
		case 'N':
				possible_moves = {{1,2},{1,-2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,1},{-2,-1}};
			break;
//		case 'B':
//				possible_moves = {{-4,-4},{-3,-3},{-2,-2},{-1,-1},{1,1},{2,2},{3,3},{4,4},
//						{-4,4},{-3,3},{-2,2},{-1,1},{1,-1},{2,-2},{3,-3},{4,-4}};
//
//			break;

		case 'K':
				possible_moves = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
//			break;
//		case 'Q':
//				possible_moves = {{0,-4},{0,-3},{0,-2},{0,-1},{0,1},{0,2},{0,3},{0,4},
//						 {-4,0},{-3,0},{-2,0},{-1,0},{1,0},{2,0},{3,0},{4,0},
//						 {-4,-4},{-3,-3},{-2,-2},{-1,-1},{1,1},{2,2},{3,3},{4,4},
//						 {-4,4},{-3,3},{-2,2},{-1,1},{1,-1},{2,-2},{3,-3},{4,-4}};
//			break;
		case 'P': 
				switch(_turn){ // check if the color order is correct
					case WHITE:
						possible_moves = {{0,1},{1,1},{-1,1}};
						break;
					case BLACK:
						possible_moves = {{0,-1},{-1,1},{1,-1}};
						break;
					default:
						cout << "Something went very wrong. this should not have happend." << endl;
				}
			break;
		default:
			cout << "ERROR PIECE NOT FOUND" << endl;
    }
// adding all possible raw moves to moves vector ( to NA or take piece)
	switch(type) {
		case 'P':
cout << "Moves for Pawn, its a bit complex since it depends on history and opponents piece position" << endl;
			break;
		default:
			for (auto move : possible_moves){
				current_row += move[0] ;
				current_column += move[1];
				check_and_push_move(current_row, current_column, player, moves);
				current_row = row;
				current_column = column;
			}
			
	}
}




void Position::print() const {
	Piece a;
	const string pieces[] =
			{ "R", "N", "B", "Q", "K", "P", "r", "n", "b", "q", "k", "p", " " };

	for (int row = 0; row < 8; ++row) {
		string row_str;
		for (int column = 0; column < 8; ++column) {
			row_str += (" | " + pieces[_board[row][column]]);
		}
		cout << "     +---+---+---+---+---+---+---+---+\n";
		cout << to_string(8 - row) + "   " + row_str + " |\n";
	}
	cout << "     +---+---+---+---+---+---+---+---+\n";
	cout << "\n	   A   B   C   D   E   F   G   H\n";
}

void Position::switch_turns(){

	if(_turn == WHITE) _turn = BLACK;
	else _turn = WHITE;

}

