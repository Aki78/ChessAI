#include <iostream>
#include <string>
#include <vector>
#include "position.h"
using namespace std;


void Position::generate_all_raw_moves(int player, std::vector<Move>& moves) const
{
        for (int row = 0; row < 8; ++row)
                for (int col = 0; col < 8; ++col)
                {
                        int piece = _board[row][col];

                        // Empty square?
                        if (piece == NA)
                                continue;

                        // Opponent's piece?
                        if (piece_color(player) != player)
                                continue;

                        // Get raw moves for the piece.
                        switch (piece)
                        {
                        case WHITE_ROOK: case BLACK_ROOK:
                                generate_rook_raw_moves(row, col, player, moves);
                                break;
                        case WHITE_QUEEN: case BLACK_QUEEN:
                                generate_queen_raw_moves(row, col, player, moves);
                                break;
                        case WHITE_KNIGHT: case BLACK_KNIGHT:
                                generate_knight_raw_moves(row, col, player, moves);
                                break;
                        case WHITE_BISHOP: case BLACK_BISHOP:
                                generate_bishop_raw_moves(row, col, player, moves);
                                break;
                        case WHITE_KING: case BLACK_KING:
                                generate_king_raw_moves(row, col, player, moves);
                                break;
                        case WHITE_PAWN: case BLACK_PAWN:
                                generate_pawn_raw_moves(row, col, player, moves);
                                break;
                        }
                }
}


void Position::clear()
{
        for (int row = 0; row < 8; ++row)
                for (int col = 0; col < 8; ++col)
                        _board[row][col] = NA;
}


void Position::make_move(const Move& m)
{
        // Take the piece from the starting square.
        int piece = _board[m._start_row][m._start_col];

        // Empty the starting square.
        _board[m._start_row][m._start_col] = NA;

        // Place the original piece to the destination square.
        _board[m._dest_row][m._dest_col] = piece;

        // Switch the turn.
        _turn = opponent(_turn);
}


void Position::generate_rook_raw_moves(int row, int col, int player,
        vector<Move>& moves) const
{
        generate_raw_moves_in_direction(row, col, -1, 0, player, 7, true, false, moves);
        generate_raw_moves_in_direction(row, col, 1, 0, player, 7, true, false, moves);
        generate_raw_moves_in_direction(row, col, 0, -1, player, 7, true, false, moves);
        generate_raw_moves_in_direction(row, col, 0, 1, player, 7, true, false, moves);
}


void Position::generate_raw_moves_in_direction(int row, int col, int row_change, int col_change,
        int player, int max_steps, bool can_capture, bool must_capture, vector<Move>& moves) const
{
        int row_now = row;
        int col_now = col;
        int steps = 0;
        while (steps < max_steps)
        {
                row_now += row_change;
                col_now += col_change;

                // Out of board?
                if (row_now < 0 || row_now > 7 || col_now < 0 || col_now > 7)
                        break;

                // Empty square?
                if (_board[row_now][col_now] == NA)
                {
                        if (must_capture)
                                break;
                        moves.push_back(Move(row, col, row_now, col_now));
                        steps++;
                        continue;
                }

                // Hit own piece?
                if (piece_color(_board[row_now][col_now]) == player)
                        break;

                // Capture opponent's piece.
                if (can_capture)
                        moves.push_back(Move(row, col, row_now, col_now));
                break;
        }
}



void Position::print() const
{
        const string pieces[] =
                { "R", "N", "B", "Q", "K", "P", "r", "n", "b", "q", "k", "p", " " };

        for (int row = 0; row < 8; ++row)
        {
                string row_str;
                for (int col = 0; col < 8; ++col)
                {
                        row_str += (" | " + pieces[_board[row][col]]);
                }
                cout << "     +---+---+---+---+---+---+---+---+\n";
                cout << to_string(8 - row) + "   " + row_str + " |\n";

        }
        cout << "     +---+---+---+---+---+---+---+---+\n";
        cout << "\n       A   B   C   D   E   F   G   H\n";
}
