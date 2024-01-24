class Piece {
public:
	Piece(int row, int column, char color) : current_row(row), current_column(column), piece_color(color) {}

	int get_row() const { return current_row; }
	int get_column() const { return current_column; }

	int power; // Like queen is 9 or 10

	char get_color() const { return piece_color; }

	virtual void make_move(int target_row, int target_column) = 0;

protected:
	
	int current_row;
	int current_column;
	
	char piece_color;

	
};


