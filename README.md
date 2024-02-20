# ChessAI: Minimax with Alpha-Beta Pruning in C++ (Metropolia Project)

This is a data structure and algorithm project for Metropolia University of Applied Science. A chess engine was built in c++ and the minimax algorithm with alpha-beta pruning was used.


## Getting Started

### Prerequisites

- C++ Compiler 

### Installation and Running

1. Clone the repository:

```
git clone https://github.com/yourusername/chessai.git
```


2. Go to the repository and make executable by running:

```
make
```

 an executable chess will then be created.

3. Run the executable

```
./chess
```


## Game Play

Three selections will be displayed. If you choose 1 and hit enter, AI will play against AI.
If you choose 2 you will play against the AI as white and if you choose 3, vice versa.

### Playing against the AI

At every turn, a list of possible moves will be displayed
```
Printing out all moves: 
S:c4c5
S:c4c6
S:c4c7
S:c4c3
S:c4b4
S:c4a4
S:c4d4
S:c4e4
...
```
the notation is 4 letters, the first 2 letters are the starting position of the piece you want to move, and the last 2 letters are the position you want to move to the square, for example if you type in:
```
c4c5
```
the piece on row 4 at column c will move up to row 5.

The game will automatically end, when either your king or the AI king has no where else to go.

## AI implementation
Minimax with alpha-beta pruning was used. The evaluation of the state-value is by simply counting the pieces (weighted with pawn:1, knite: 3, bishop: 3, rook: 5, queen:9 and king: 20), and taking the difference between black and white. 
