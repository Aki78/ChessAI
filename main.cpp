#include "position.h"
#include "move.h"
#include "chess.h"

int main()
{
	// Initial position
	Position position;


	// e2e4
	Move move(6, 4, 4, 4);
	Move move2("e2e4");
	position.make_move(move);

	position.print();

	return 0;
}
