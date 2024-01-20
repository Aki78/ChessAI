#pragma once
#include <string>
#include <vector>
#include<iostream>

using namespace std;

// Describes a change in position.
class Move
{
public:
	Move(int start_row, int start_column, int end_row, int end_column) :
		_start_row(start_row), _start_column(start_column), _end_row(end_row), _end_column(end_column)
	{}

	// HOMEWORK
	// Create a constructor that initializes a move object
	// from a given string, e.g., "e2e4" or "g8f6".
	Move(const string& str){
		setMove(str);
    // e2e4
    		Move move(moveNums[0], moveNums[1], moveNums[2], moveNums[3]);



		
	}

private:

	int _start_row; // starting row of the move
	int _start_column; // starting column (i.e., file) of the move

	int _end_row; // ending row of the move
	int _end_column; // ending column of the move
	vector<char> moveChars = {'\0','\0','\0','\0'}; // for splitting the movement chars
	vector<char> moveNums = {0,0,0,0}; // for splitting the movement chars

	friend class Position;

	int charToInt(char c) {
		if (c >= 'a' && c <= 'h') {
		return c - 'a';
		} else {
			return -1; // Returns -1 or any other sentinel value to indicate an invalid input.
		}
	}

	int numToInt(char c) {
		if (c >= '0' && c <= '9') {
			return c - '0'; // Subtract ASCII value of '0' to get the integer value
		} else {
			return -1; // Returns -1 or any other sentinel value to indicate an invalid input.
		}
	}

	void setMove(const string& str) {
    		moveChars[0] = str[0];
    		moveChars[1] = str[1];
    		moveChars[2] = str[2];
    		moveChars[3] = str[3];

    		moveNums[0] = charToInt(moveChars[0]);
    		moveNums[1] = numToInt(moveChars[1]);
    		moveNums[2] = charToInt(moveChars[2]);
    		moveNums[3] = numToInt(moveChars[3]);

	}
};

