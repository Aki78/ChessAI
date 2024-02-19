#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "position.h"
#include "move.h"
#include <map>
#include <climits>

using namespace std;

int main(){
        // Initial position.
        Position position;
	vector<Move> moves;
	moves = position.generate_legal_moves();
	map<Move, int> action_value;
	


        while (!moves.empty()){
		string input_move_string;
		cout << "Printing out all moves: " << endl;
		for(auto m: moves) m.print_move();
		action_value.clear();

                position.print();
		cout << "Input your move: ";
		cin >> input_move_string;
//		bool possible_move= true;
		Move new_move(input_move_string);

		if (!count(moves.begin(),moves.end(), new_move)) continue; // checking if moves exist

		for(auto m: moves){ // trying out moves to get state action values
			Position test_position = position; // copying new position for test
			test_position.make_move(m);
			vector<int> state_values = test_position.get_state_value();
			int state_value = 0;
			if(position._turn == WHITE) state_value = state_values[0] - state_values[1];
			else if(position._turn == BLACK) state_value = state_values[1] - state_values[0];
			cout << "values are: " << state_values[0] << " " << state_values[1] << endl;
			cout << "action is: " << endl;
			m.print_move();
			cout << "state value is: " << state_value << endl;
			action_value[m] = state_value;
			cout << "size is: " << action_value.size();
		}

		Move maxMove(0,0,0,0);
		int maxValue = -1000; // Include <climits> for INT_MIN

		for (const auto& pair : action_value) {
			cout << pair.second << endl;
			if (pair.second > maxValue) {
				maxValue = pair.second;
				maxMove = pair.first;
				maxMove.print_move();
			}
		}

		cout << "MAX MOVE MADE:::" << endl;
		maxMove.print_move();
		position.make_move(maxMove);
		moves.clear();
		moves = position.generate_legal_moves();


		
		cout << "values are: " << position.get_state_value()[0] << " " << position.get_state_value()[1] << endl;
	}
	

        return 0;
}
