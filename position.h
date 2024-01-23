#pragma once
#include "chess.h"
#include "move.h"

class Position
{
public:

	void clear();
	void make_move(const Move& m);

	// HOMEWORK
	// Print the board as ASCII graphics.
	void print() const;
	void give_rook_raw_moves(int row, int column, int player, vector<Move>& moves) const;

private:

	// Pieces on the board. Indexed [row][column], for example,
	//
	// [0][0] : top left corner ("a8")
	// [7][0] : bottom left corner ("a1")
	// [7][7] : bottom right corner ("h1")
	//
	int _board[8][8] = {
		{ bR, bN, bB, bQ, bK, bB, bN, bR },
		{ bP, bP, bP, bP, bP, bP, bP, bP },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ wP, wP, wP, wP, wP, wP, wP, wP },
		{ wR, wN, wB, wQ, wK, wB, wN, wR }
	};

	int _turn = WHITE;
};

