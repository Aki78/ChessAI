#pragma once

// Players.
enum { WHITE, BLACK };

// Constant values for different pieces (NA = empty square).
enum { wR, wN, wB, wQ, wK, wP, bR, bN, bB, bQ, bK, bP, NA };

// Returns the color of the given piece (WHITE, BLACK).
int piece_color(int piece);

