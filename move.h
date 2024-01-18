#pragma once
#include <string>

// Describes a change in position.
class Move
{
public:
    Move(int start_row, int start_column, int end_row, int end_column) :
        _start_row(start_row), _start_column(start_column), _end_row(end_row), _end_column(end_column)
    {}

    // HOMEWORK
    // Create a constructor that initializes a move object
    // from a given string, e.g., "e2e4" or "g8f6".
    Move(const std::string& s);

private:

    int _start_row; // starting row of the move
    int _start_column; // starting column (i.e., file) of the move

    int _end_row; // ending row of the move
    int _end_column; // ending column of the move

    friend class Position;
};

