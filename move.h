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
	Move(int start_row, int start_column, int end_row, int end_column) ;

	// HOMEWORK
	// Create a constructor that initializes a move object
	// from a given string, e.g., "e2e4" or "g8f6".
	Move(const string& str);
private:

	vector<char> moveChars = {'\0','\0','\0','\0'}; // for splitting the movement chars
	vector<char> moveNums = {0,0,0,0}; // for splitting the movement chars

	friend class Position;

	int char_to_int(char c); 
	int num_to_int(char c); 

	void set_move(const string& str); 
	void print_move(); 
};

