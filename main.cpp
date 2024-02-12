#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "position.h"
#include "move.h"
using namespace std;

int main()
{
        // Initial position.
        Position position;

        vector<Move> moves;
        position.generate_all_raw_moves(position._turn, moves);
	string input_move_string;

	Move new_move(input_move_string);

        while (!moves.empty()){
                position.print();
		cout << "Input your move: ";
		cin >> input_move_string;
//		bool possible_move= true;

		if (!count(moves.begin(),moves.end(), new_move)) continue;
//		while (possible_move) {
//			for (auto& m: moves)
//				if(m.get_moves() == input_move_string) {
//					possible_move = false;
//					break;		
//				}
//			if (possible_move) { // NO MORE MOVES!!!
//				cout << "Not a possible move. " << endl;
//			}
//		}
		position.make_move(new_move);
		moves.clear();
		moves = position.generate_legal_moves();
	}
	

        return 0;
}
