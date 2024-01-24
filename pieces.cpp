#include <iostream>
#include <string>
#include <vector>
#include "position.h" // Assuming "asema" translates to "station"
using namespace std;


// Generate rook's raw moves
void Piece::give_rook_raw_moves(int row, int column, int player, vector<Move>& moves) const {
	// Up
	int current_row = row;
	int current_column = column;
	while (true) {

		current_row--;

		if (current_row < 0) break; // Off the board?

		
		if (_board[current_row][current_column] == NA){ // Empty square?
			moves.push_back(Move(row, column, current_row, current_column));
			continue;
		}
		
		if (piece_color(_board[current_row][current_column]) == player) break; // Encounter own piece?
		
		moves.push_back(Move(row, column, current_row, current_column)); // Capture opponent's piece.
		break;
	}

}

