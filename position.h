#pragma once
#include "chess.h"
#include "move.h"

class Position {
public:
	int temp_row;
	int temp_column;
	void clear();
	void print() const;
	void make_move(const Move& m);
	void give_rook_raw_moves(int row, int column, int player, vector<Move>& moves);
	void give_nite_or_king_raw_moves(char a, int row, int column, int player, vector<Move>& moves);
	bool check_and_push_move(int row, int column, int row_current, int column_current, int player, vector<Move>& moves);
	void give_bish_raw_moves(int row, int column, int player, vector<Move>& moves);
	void give_queen_raw_moves(int row, int column, int player, vector<Move>& moves);
	void generate_all_raw_moves(int player, vector<Move>& moves);
	vector<Move> generate_legal_moves() ;
	bool is_king_threatened(vector<int> pos, int enemy);
	vector<int> get_chess_piece(int chess_piece) const ;
	void check_pawn_and_push_move(int row, int column,  int player, vector<Move>& moves);
	void set_cowerdice(int i, int j);
	void unset_cowerdice();

	int _turn = WHITE;


private:

	// Pieces on the board. Indexed [row][column], for example,
	//
	// [0][0] : top left corner ("a8")
	// [7][0] : bottom left corner ("a1")
	// [7][7] : bottom right corner ("h1")
	//
//	int _board[8][8] = { // en passant test
//		{ NA, NA, NA, NA, NA, NA, NA, NA },
//		{ bP, NA, NA, NA, NA, wP, NA, NA },
//		{ NA, NA, NA, NA, NA, NA, NA, NA },
//		{ NA, wP, NA, NA, NA, NA, NA, NA },
//		{ bP, NA, NA, NA, NA, NA, NA, NA },
//		{ NA, NA, NA, NA, NA, NA, NA, NA },
//		{ NA, wP, bP, NA, NA, NA, NA, NA },
//		{ NA, NA, NA, NA, NA, NA, NA, NA }
//	};


	int _board[8][8] = {
		{ bR, NA, NA, NA, bK, NA, NA, bR },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, wP, NA, NA, NA, NA, NA, NA },
		{ NA, NA, bP, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ NA, NA, NA, NA, NA, NA, NA, NA },
		{ wR, NA, NA, NA, wK, NA, NA, wR }
	};

//	int _board[8][8] = {
//		{ bR, bN, bB, bQ, NA, bB, bN, bR },
//		{ bP, bP, bP, bP, bP, bP, bP, bP },
//		{ NA, NA, NA, NA, NA, NA, NA, NA },
//		{ NA, NA, NA, NA, NA, NA, NA, NA },
//		{ NA, NA, bP, NA, NA, NA, NA, NA },
//		{ NA, NA, NA, NA, NA, NA, NA, NA },
//		{ wP, wP, wP, wP, wP, wP, wP, wP },
//		{ wR, wN, wB, wQ, NA, wB, wN, wR }
//	};

	void switch_turns();
	bool is_enemy_of_white(int);
	bool is_enemy_of_black(int);
	vector<int> cowerdice_coord = {-100,-100}; // set this (i,j) when en passant is possible where the pawn is, otherwise, reset it to a big negative number;

};

