class Piece {
public:
	Piece();
	Piece(int row, int column, char color) ;

	int get_row() const; 
	int get_column() const; 

	int power; // Like queen is 9 or 10

	char get_color() const; 

	void make_move(int target_row, int target_column);

protected:
	
	int current_row;
	int current_column;
	
	char piece_color;

	
};


