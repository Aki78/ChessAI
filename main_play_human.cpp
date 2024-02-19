#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "position.h"
#include "move.h"

using namespace std;

int main(){
        // Initial position.
        Position position;
	vector<Move> moves;
	moves = position.generate_legal_moves();


        while (!moves.empty()){
		string input_move_string;
		cout << "Printing out all moves: " << endl;
		for(auto m: moves) m.print_move();

                position.print();
		cout << "Input your move: ";
		cin >> input_move_string;
//		bool possible_move= true;
		Move new_move(input_move_string);

		if (!count(moves.begin(),moves.end(), new_move)) continue; // checking if moves exist

		position.make_move(new_move);
		moves.clear();
		moves = position.generate_legal_moves();



		vector<int> state_values = position.get_state_value();
		int state_value = 0;
		if(position._turn == WHITE) state_value = state_values[0] - state_values[1];
		else if(position._turn == BLACK) state_value = state_values[1] - state_values[0];
		
		cout << "values are: " << position.get_state_value()[0] << " " << position.get_state_value()[1] << endl;
		cout << "state value is: " << state_value << endl;
	}
	

        return 0;
}
