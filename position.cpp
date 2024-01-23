#include <iostream>
#include <string>
#include <vector>
#include "position.h" // Assuming "asema" translates to "station"
using namespace std;

// Clears the board
void Position::clear() {
	for (int row = 0; row < 8; ++row)
		for (int column = 0; column < 8; ++column)
			_board[row][column] = NA;
}

// Execute a move
void Position::make_move(const Move& m) {
	// Store the piece in the starting square.
	int piece = _board[m._start_row][m._start_column];

	// Clear the starting square.
	_board[m._start_row][m._start_column] = NA;

	// Place the original piece in the destination square.
	_board[m._end_row][m._end_column] = piece;

	// TODO
	// change the turn
}

// Generate rook's raw moves
void Position::give_rook_raw_moves(int row, int column, int player, vector<Move>& moves) const {
	// Up
	int current_row = row;
	int current_column = column;
	while (true)
	{
		current_row--;

		// Off the board?
		if (current_row < 0)
			break;

		// Empty square?
		if (_board[current_row][current_column] == NA)
		{
			moves.push_back(Move(row, column, current_row, current_column));
			continue;
		}

		// Encounter own piece?
		if (piece_color(_board[current_row][current_column]) == player)
			break;

		// Capture opponent's piece.
		moves.push_back(Move(row, column, current_row, current_column));
		break;
	}

	// ... presumably, there are more directions to check for the rook.
}

// Print the board
void Position::print() const {
	const string pieces[] =
			{ "R", "N", "B", "Q", "K", "P", "r", "n", "b", "q", "k", "p", " " };

	for (int row = 0; row < 8; ++row)
	{
		string row_str;
		for (int column = 0; column < 8; ++column)
		{
			row_str += (" | " + pieces[_board[row][column]]);
		}
		cout << "	 +---+---+---+---+---+---+---+---+\n";
		cout << to_string(8 - row) + "   " + row_str + " |\n";
	}
	cout << "	 +---+---+---+---+---+---+---+---+\n";
	cout << "\n	   A   B   C   D   E   F   G   H\n";
}

