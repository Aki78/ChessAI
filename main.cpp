#include "position.h"
#include "move.h"

int main()
{
    // Initial position
    Position position;

    // e2e4
    Move move(6, 4, 4, 4);
    position.make_move(move);

    return 0;
}
