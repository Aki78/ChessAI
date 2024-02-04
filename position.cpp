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

bool check_and_push_move(int row, int column, int player, vector<Move>& moves){ // woudl this logic really work?
// bool depricated, it used to be used for breaking while loops

	if (current_row < 0) return true; // Off the board?
	if (_board[current_row][current_column] == NA){ // Empty square?
		moves.push_back(Move(row, column, current_row, current_column));
		return false; // false in thise case meens success and continue
	}
	if (piece_color(_board[current_row][current_column]) == player) return true; // Encounter own piece?
	
	moves.push_back(Move(row, column, current_row, current_column)); // Capture opponent's piece.
	return true;

}

// Generate rook's raw moves
void Position::give_rook_raw_moves(int row, int column, int player, vector<Move>& moves) const {
	// Up
	int current_row = row;
	int current_column = column;
//	while (true) {
//
//		current_row--;
//		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
//		if (wanna_break) break;
//	}

//	current_row = row;

	vector<vector<int>> possible_moves = {{0,-4},{0,-3},{0,-2},{0,-1},{0,1},{0,2},{0,3},{0,4},
					  {0,4},{0,3},{0,2},{0,1},{0,-1},{0,-2},{0,-3},{0,-4}};

	for (auto move : possible_moves){
		current_row += move[0] ;
		current_column += move[1];
		while(true){
			check_and_push_move(current_row, current_column, player, moves);
		}
		current_row = row;
		current_column = column;
	}

}
`
void Position::give_raw_moves(char type, int row, int column, int player, vector<Move>& moves) const { // sanity check moves later

	int current_row = row;
	int current_column = column;
	vector<vector<int>> possible_moves;
	switch(type)

	switch(ch) {
		case 'R':
				possible_moves = {{0,-4},{0,-3},{0,-2},{0,-1},{0,1},{0,2},{0,3},{0,4},
						{0,4},{0,3},{0,2},{0,1},{0,-1},{0,-2},{0,-3},{0,-4}};
			break;
		case 'N':
				possible_moves = {{1,2},{1,-2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,1},{-2,-1}};
			break;
		case 'B':
				possible_moves = {{-4,-4},{-3,-3},{-2,-2},{-1,-1},{1,1},{2,2},{3,3},{4,4},
						{-4,4},{-3,3},{-2,2},{-1,1},{1,-1},{2,-2},{3,-3},{4,-4}};

				possible_moves =  {{1,2},{1,-2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,1},{-2,-1}};
			break;
		case 'K':
				possible_moves = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
			break;
		case 'Q':
				possible_moves = {{0,-4},{0,-3},{0,-2},{0,-1},{0,1},{0,2},{0,3},{0,4},
						 {0,4},{0,3},{0,2},{0,1},{0,-1},{0,-2},{0,-3},{0,-4}},
						 {-4,-4},{-3,-3},{-2,-2},{-1,-1},{1,1},{2,2},{3,3},{4,4},
						 {-4,4},{-3,3},{-2,2},{-1,1},{1,-1},{2,-2},{3,-3},{4,-4}};
			break;
		default:
			std::cout << "ERROR PIECE NOT FOUND" << std::endl;
    }

	for (auto move : possible_moves){
		current_row += move[0] ;
		current_column += move[1];
		check_and_push_move(current_row, current_column, player, moves);
		current_row = row;
		current_column = column;
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

