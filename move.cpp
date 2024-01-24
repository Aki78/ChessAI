#include "move.h"

using namespace std;

// Describes a change in position.
Move::Move(int start_row, int start_column, int end_row, int end_column) : _start_row(start_row), _start_column(start_column), _end_row(end_row), _end_column(end_column) {}

Move::Move(const string& str){

	set_move(str);
    	Move move(moveNums[0], moveNums[1], moveNums[2], moveNums[3]);
//	print_move();
		
}

int Move::char_to_int(char c) {

	if (c >= 'a' && c <= 'h') {
	return c - 'a';

	} else {
		return -1; // Returns -1 or any other sentinel value to indicate an invalid input.
	}
}

int Move::num_to_int(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0' ; // Subtract ASCII value of '0' to get the integer value
	} else {
		return -1; // Returns -1 or any other sentinel value to indicate an invalid input.
	}
}

void Move::set_move(const string& str) {
	moveChars[0] = str[0];
   	moveChars[1] = str[1];
    	moveChars[2] = str[2];
    	moveChars[3] = str[3];

    	moveNums[0] = 8 - num_to_int(moveChars[1]);
    	moveNums[1] = char_to_int(moveChars[0]);
    	moveNums[2] = 8 -  num_to_int(moveChars[3]);
    	moveNums[3] = char_to_int(moveChars[2]);

}

//void Move::print_move() {
//	for (char c : moveChars) {
//		cout << c << " " ;
//	}
//	cout << endl;
//	for (int i : moveNums) {
//		cout << i << " " ;
//	}
//}

