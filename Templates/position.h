#pragma once
#include <vector>
#include "chess.h"
#include "move.h"

class Position
{
public:
    // Clears the board.
    void clear();

    // Makes the given move on the board. Assumes that
    // the move is legal.
    void make_move(const Move& m);

    // Prints the board as ASCII graphics.
    void print() const;

    // Provides all raw moves for the position.
    void generate_all_raw_moves(int player, std::vector<Move>& moves) const;

    // Provides raw moves for the rook (ignores checks).
    void generate_rook_raw_moves(int row, int col, int player,
        std::vector<Move>& moves) const;
    void generate_bishop_raw_moves(int row, int col, int player,
        std::vector<Move>& moves) const { /* TODO */ }
    void generate_queen_raw_moves(int row, int col, int player,
        std::vector<Move>& moves) const { /* TODO */ }
    void generate_knight_raw_moves(int row, int col, int player,
        std::vector<Move>& moves) const { /* TODO */ }
    void generate_king_raw_moves(int row, int col, int player,
        std::vector<Move>& moves) const { /* TODO */ }
    void generate_pawn_raw_moves(int row, int col, int player,
        std::vector<Move>& moves) const { /* TODO */ }

    /// Provides possible raw moves of a piece in a certain direction.
    ///
    /// \param row           starting row of the piece
    /// \param col           starting column of the piece
    /// \param row_change    change in rows coordinate (e.g., -1 means "up")
    /// \param col_change    change in columns coordinate (e.g., 1 means "right")
    /// \param player        piece's color (WHITE, BLACK)
    /// \param max_steps     maximum steps in that direction
    /// \param can_capture   can the piece capture in that direction?
    /// \param must_capture  does the piece have to capture while moving in that direction?
    /// \param moves         vector of moves to be filled with possible raw moves
    ///
    void generate_raw_moves_in_direction(int row, int col, int row_change, int col_change,
        int player, int max_steps, bool can_capture, bool must_capture,
        std::vector<Move>& moves) const;

    // The pieces on the board. Indexing [row][col], e.g.,
    //
    // [0][0] : left top corner ("a8")
    // [7][0] : left bottom corner ("a1")
    // [7][7] : right bottom corner ("h1")
    //
    int _board[8][8] = {
        { BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK },
        { BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN },
        { NA, NA, NA, NA, NA, NA, NA, NA },
        { NA, NA, NA, NA, NA, NA, NA, NA },
        { NA, NA, NA, NA, NA, NA, NA, NA },
        { NA, NA, NA, NA, NA, NA, NA, NA },
        { WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN },
        { WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK }
    };

    int _turn = WHITE;
};
