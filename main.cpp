#include <iostream>
#include <string>
#include <vector>
#include "position.h"
#include "move.h"
using namespace std;

int main()
{
        // Initial position.
        Position position;

        vector<Move> moves;
        position.generate_all_raw_moves(position._turn, moves);

        while (!moves.empty()){
                position.print();
		cout << "Input your move: ";
		cin << input_move_string;
		bool possible_move= true;
		while (possible_move) {
			for (auto& m: moves)
				if(m.get_moves() == input_move_string) {
					possible_move = false;
					break;		
				}
			if (no_more_moves) {
				cout << "Not a possible move. " << endl;
			}
		}
		position.move(Move(input_move_string));
		moves.clear();
		moves = position.generate_legal_moves();
	}
	

        return 0;
}
