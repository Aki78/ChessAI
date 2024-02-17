#pragma once
#include <string>
#include <vector>
#include<iostream>

using namespace std;

// Describes a change in position.
class Move{


public:
	int _start_row; // starting row of the move
	int _start_column; // starting column (i.e., file) of the move

	int _end_row; // ending row of the move
	int _end_column; // ending column of the move
//	string move_string;


	Move(int start_row, int start_column, int end_row, int end_column) ;

	Move(const string& str);
	bool operator==(const Move& other) const {
		return _start_row==other._start_row && _start_column==other._start_column &&  _end_row==other._end_row &&  _end_column==other._end_column ;
	} 
	void print_move(); 
private:

	vector<char> moveChars = {'\0','\0','\0','\0'}; // for splitting the movement chars
	vector<char> moveNums = {0,0,0,0}; // for splitting the movement chars

	friend class Position;

	int char_to_int(char c); 
	int num_to_int(char c); 
	string get_string();

	int set_move(const string& str); 
};

