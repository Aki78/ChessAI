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

bool check_and_push_move(int row, int column, int player, vector<Move>& moves){


	if (current_row < 0) return true; // Off the board?
	if (_board[current_row][current_column] == NA){ // Empty square?
		moves.push_back(Move(row, column, current_row, current_column));
		return false;
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
	while (true) {

		current_row--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;

	// Down
	while (true) {

		current_row++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;

	}


	// Left
	current_row = row;
	while (true) {

		current_column--;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;

	}

	current_column = column;
	//Right
	while (true) {

		current_column++;
		bool wanna_break = check_and_push_move(current_row, current_column, player, moves);
		if (wanna_break) break;

	}

}


void Position::give_nite_raw_moves(int row, int column, int player, vector<Move>& moves) const {

	int current_row = row;
	int current_column = column;
	vector<vector<int>> nite_moves = {{1,2},{1,-2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,1},{-2,-1}};

	for (auto move : nite_moves){
		current_row += move[0] ;
		current_column += move[1];
		check_and_push_move(current_row, current_column, player, moves);
		current_row = row;
		current_column = column;
	}
}



void Position::give_bish_raw_moves(int row, int column, int player, vector<Move>& moves) const {
	int current_row = row;
	int current_column = column;
	vector<vector<int>> nite_moves = {{-4,-4},{-3,-3},{-2,-2},{-1,-1},{1,1},{2,2},{3,3},{4,4},
					  {-4,4},{-3,3},{-2,2},{-1,1},{1,-1},{2,-2},{3,-3},{4,-4}}

	for (auto move : nite_moves){
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

