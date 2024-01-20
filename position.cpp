#include "position.h"

// Clears the board.
void Position::clear()
{
    for (int row = 0; row < 8; ++row)
        for (int column = 0; column < 8; ++column)
            _board[row][column] = NA;
}


// Executes the given move on the board. It can be assumed
// that the move is legal.
void Position::make_move(const Move& m)
{
    // Store the piece in the starting square.
    int piece = _board[m._start_row][m._start_column];

    // Clear the starting square.
    _board[m._start_row][m._start_column] = NA;

    // Place the original piece in the ending square.
    _board[m._end_row][m._end_column] = piece;
}

