#include "piece.h"

Piece::Piece(){}
Piece::Piece(int row, int column, char color) : current_row(row), current_column(column), piece_color(color){};
int Piece::get_row() const { return current_row; }
int Piece::get_column() const { return current_column; }
char Piece::get_color() const { return piece_color; }
