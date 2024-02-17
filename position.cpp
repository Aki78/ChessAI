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

void Position::set_cowerdice(int row, int column) {
	cowerdice_coord[0] = row;
	cowerdice_coord[1] = column;
}

void Position::unset_cowerdice() {
	cowerdice_coord[0] = -100;
	cowerdice_coord[1] = -100;
}



void Position::generate_all_raw_moves(int player, vector<Move>& moves) {
		for (int row = 0; row < 8; ++row)
			for (int col = 0; col < 8; ++col){
						int piece = _board[row][col];

						// Empty square?
						if (piece == NA) continue;

						// Opponent's piece?
						if (piece_color(piece) != player) continue;

						// Get raw moves for the piece.
						switch (piece){
						case wR: case bR:
								give_rook_raw_moves(row, col, player, moves);
								break;
						case wQ: case bQ:
								give_queen_raw_moves(row, col, player, moves);
								break;
						case wN: case bN:
								give_nite_or_king_raw_moves('N', row, col, player, moves);
								break;
						case wB: case bB:
								give_bish_raw_moves(row, col, player, moves);
								break;
						case wK: case bK:
								give_nite_or_king_raw_moves('K', row, col, player, moves);
								break;
						case wP: case bP:
								check_pawn_and_push_move(row, col, player, moves);
								break;
						}
				}
}

bool can_turn_into_queen(int piece, int destination_row) {
	return (piece == wP && destination_row == 0) || (piece == bP && destination_row == 7);
}

void switch_to_queen(int& piece){
	if(piece == wP) piece = wQ;
	else piece = bQ;

}


// Execute a move (updating the board)
void Position::make_move(const Move& m) {
//	cout << "New move is: " << m._start_row << " " << m._start_column << " " <<m._end_row << " "  <<m._end_column << endl;
	
	int piece = _board[m._start_row][m._start_column]; // Store the piece in the starting square.
	_board[m._start_row][m._start_column] = NA; // Clear the starting square

//	int player = piece_color(piece);
	if (can_turn_into_queen(piece, m._end_row)) switch_to_queen(piece);	

	_board[m._end_row][m._end_column] = piece; // Place the original piece in the destination square

	if((piece == wP || piece == bP) && abs(m._end_row - m._start_row) == 2){ //set en passantable piece
		set_cowerdice(m._end_row, m._end_column);
	}

	if(piece == bP && m._start_row == cowerdice_coord[0] && ( m._start_column + 1 == cowerdice_coord[1] || m._start_column - 1 == cowerdice_coord[1])) //erase pawn from enpassant
		if(m._end_row - 1 == cowerdice_coord[0] && m._end_column == cowerdice_coord[1])
			_board[cowerdice_coord[0]][cowerdice_coord[1]] = NA; //clear cowerdice piece 
	if(piece == wP && m._start_row == cowerdice_coord[0] && ( m._start_column + 1 == cowerdice_coord[1] || m._start_column - 1 == cowerdice_coord[1])) //erase pawn from enpassant
		if(m._end_row + 1 == cowerdice_coord[0] && m._end_column == cowerdice_coord[1])
			_board[cowerdice_coord[0]][cowerdice_coord[1]] = NA; //clear cowerdice piece 

	switch_turns();
}

bool Position::check_and_push_move(int row, int column, int row_current, int column_current, int player, vector<Move>& moves){ // woudl this logic really work?
//	moves.push_back(Move(1,2,3,4));
// moving!
	if (row_current < 0 || row_current > 7 || column_current < 0 || column_current > 7) return true; // Off the board?
	if (_board[row_current][column_current] == NA){ // Empty square?
		moves.push_back(Move(row, column, row_current, column_current));
		return false; // false in thise case meens success and continue
	}
	if (piece_color(_board[row_current][column_current]) == player){ return true;} // Encounter own piece?
	moves.push_back(Move(row, column, row_current, column_current)); // Capture opponent's piece.
	return true;

}

bool Position::is_enemy_of_white(int p) {
	if(p == bR  || p == bN || p == bB || p == bQ || p == bK || p == bP) return true;
	else return false;
}	

bool Position::is_enemy_of_black(int p) {
	if(p == wR  || p == wN || p == wB || p == wQ || p == wK || p == wP) return true;
	else return false;
}	


//int Position::piece_color(int p) {
//	if(p == wR  || p == wN || p == wB || p == wQ || p == wK || p == wP) return WHITE;
//	else if(p == bR  || p == bN || p == bB || p == bQ || p == bK || p == bP) return BLACK;
//	
//	return -999; // Not white nor black
//}	

void Position::check_pawn_and_push_move(int row, int column, int player, vector<Move>& moves){ // woudl this logic really work?
// add promotion, en passande,  taking pieces
	int current_row = row;
	int current_column = column;

//	if (row_current < 0 || row_current > 7) return true; // Off the board? // OK
	if (_turn==WHITE){

		int enpassantable_column = current_column + 1; 	
		if(_board[current_row][enpassantable_column] == bP && cowerdice_coord[0] == current_row && cowerdice_coord[1] == enpassantable_column){
			moves.push_back(Move(row, column, row - 1, enpassantable_column));}

		enpassantable_column = current_column - 1; 	
		if(_board[current_row][enpassantable_column] == bP && cowerdice_coord[0] == current_row && cowerdice_coord[1] == enpassantable_column){
			moves.push_back(Move(row, column, row - 1, enpassantable_column));}



		current_row--; 
		if (_board[current_row][current_column] == NA){ // Empty square? OK
			moves.push_back(Move(row, column, current_row, current_column));
			if(current_row==5){
				current_row--;	// another step if it is at starting point
				if (_board[current_row][current_column] == NA){ // Empty square? OK
//					set_cowerdice(current_row, current_column);
					moves.push_back(Move(row, column, current_row, current_column));
				}
			}
		}
		current_row = row; // resetting position

		// if enemy on sides
		if (is_enemy_of_white(_board[current_row-1][current_column-1])){ 
			moves.push_back(Move(row, column, current_row-1, current_column-1));
		}
		if (is_enemy_of_white(_board[current_row-1][current_column+1])){ 
			moves.push_back(Move(row, column, current_row-1, current_column+1));
		}

	}
	else if (_turn==BLACK){
		int enpassantable_column = current_column + 1; 	
		if(_board[current_row][enpassantable_column] == wP && cowerdice_coord[0] == current_row && cowerdice_coord[1] == enpassantable_column){
			moves.push_back(Move(row, column, row + 1, enpassantable_column));}

		enpassantable_column = current_column - 1; 	
		if(_board[current_row][enpassantable_column] == wP && cowerdice_coord[0] == current_row && cowerdice_coord[1] == enpassantable_column){
			moves.push_back(Move(row, column, row + 1, enpassantable_column));}





		current_row++; // could be opposite
		if (_board[current_row][current_column] == NA){ // Empty square? OK
			moves.push_back(Move(row, column, current_row, current_column));
			if(current_row==2){
				current_row++;	// another step if it is at starting point
				if (_board[current_row][current_column] == NA){ // Empty square? OK
//					set_cowerdice(current_row, current_column);
					moves.push_back(Move(row, column, current_row, current_column));
				}
			}
		}
		current_row = row; // resetting position

		// if enemy on sides
		if (is_enemy_of_black(_board[current_row+1][current_column-1])){ 
			moves.push_back(Move(row, column, current_row+1, current_column-1));
		}
		if (is_enemy_of_black(_board[current_row+1][current_column+1])){ 
			moves.push_back(Move(row, column, current_row+1, current_column+1));
		}
	}

}

// Generate rook's raw moves
void Position::give_rook_raw_moves(int row, int column, int player, vector<Move>& moves) {
	// Up
	int current_row = row;
	int current_column = column;

	while (true) {
		current_row--;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;

	while (true) {
		current_row++;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;

	while (true) {
		current_column--;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_column = column;

	while (true) {
		current_column++;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
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
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;

	while (true) {
		current_row++;
		current_column--;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;


	while (true) {
		current_row--;
		current_column++;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;

	while (true) {
		current_row++;
		current_column++;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

}


void Position::give_queen_raw_moves(int row, int column, int player, vector<Move>& moves) {
	int current_row = row;
	int current_column = column;

	while (true) {
		current_row--;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;

	while (true) {
		current_row++;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;

	while (true) {
		current_column--;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_column = column;

	while (true) {
		current_column++;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_column = column;


	while (true) {
		current_row--;
		current_column--;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;

	while (true) {
		current_row++;
		current_column--;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;


	while (true) {
		current_row--;
		current_column++;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}

	current_row = row;
	current_column = column;

	while (true) {
		current_row++;
		current_column++;
		bool wanna_break = check_and_push_move(row, column, current_row, current_column, player, moves);
		if (wanna_break) break;
	}


}


void Position::give_nite_or_king_raw_moves(char type, int row, int column, int player, vector<Move>& moves) { // sanity check moves later

	int current_row = row;
	int current_column = column;
	vector<vector<int>> possible_moves;

	switch(type) {
// R, B and Q doesn't work's well with tables, so the idea is discarded
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
			break;
//		case 'Q':
//				possible_moves = {{0,-4},{0,-3},{0,-2},{0,-1},{0,1},{0,2},{0,3},{0,4},
//						 {-4,0},{-3,0},{-2,0},{-1,0},{1,0},{2,0},{3,0},{4,0},
//						 {-4,-4},{-3,-3},{-2,-2},{-1,-1},{1,1},{2,2},{3,3},{4,4},
//						 {-4,4},{-3,3},{-2,2},{-1,1},{1,-1},{2,-2},{3,-3},{4,-4}};
//			break;
//		case 'P': 
//				switch(_turn){ // check if the color order is correct
//					case WHITE:
//						possible_moves = {{0,1},{1,1},{-1,1},{0,2}};
//						break;
//					case BLACK:
//						possible_moves = {{0,-1},{-1,1},{1,-1},{0,-2}};
//						break;
				//	default:
				//		cout << "Something went very wrong. this should not have happend." << endl;
				//}
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
				check_and_push_move(row, column, current_row, current_column, player, moves);
				current_row = row;
				current_column = column;
			}
			
	}
}

vector<int> Position::get_chess_piece(int chess_piece) const {
	vector<int> piece_pos= {-1,-1};
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (chess_piece == _board[i][j]) {
				piece_pos[0] = i; piece_pos[1] = j;
				return piece_pos;
			}
		}
	}

}


bool Position::is_king_threatened(vector<int> pos, int enemy) {
	vector<Move> all_raw_moves; 
	generate_all_raw_moves(enemy, all_raw_moves);
	for (Move& move: all_raw_moves) {
		move.print_move();
//			cout <<  pos[0] << " " << pos[1] << endl;
		if (move._end_row == pos[0] && move._end_column == pos[1]){
			cout << "HIT: " << pos[0] << " " << pos[1] << endl;
			return true;
		}
	}		
	return false;
}


vector<Move> Position::generate_legal_moves() {

	int my_king = bK;
	int enemy = WHITE;
	int player = _turn;

	if(player == WHITE) my_king = wK;
	if(player == WHITE) enemy = BLACK;

	vector<Move> raw_moves;

	generate_all_raw_moves(player, raw_moves);

	vector<Move> legal_moves;

	for(const Move& m: raw_moves) {
		Position test_pos = *this;

		test_pos.make_move(m);

		vector<int> king_piece_pos =  test_pos.get_chess_piece(my_king);
		if (!test_pos.is_king_threatened(king_piece_pos, enemy)) 
			legal_moves.push_back(m);
	}

	return legal_moves;
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
	cout << "       A   B   C   D   E   F   G   H\n";
}

void Position::switch_turns(){

	if(_turn == WHITE) _turn = BLACK;
	else _turn = WHITE;

}

