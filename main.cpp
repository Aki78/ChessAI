#include <iostream>
#include <string>
#include <vector>
#include "position.h"
#include "move.h"
using namespace std;

int main()
{
        // Initial position.
        Position position;

        vector<Move> moves;
        position.generate_all_raw_moves(position._turn, moves);

        while (!moves.empty())
        {
                position.print();

                // Print possible moves in the form
                // e2e4
                // e2e3
                // g1f3
                // etc.
                cout << "Possible moves:\n";
                for (const auto& move : moves)
                {
                        cout << move.to_string() << endl;
                }

                // Print the number of legal moves, e.g.
                // 20
                cout << "Number of legal moves: " << moves.size() << endl;

                // Ask for player's move, e.g., "e2e4" (note: if it's a promotion move, like "a7a8Q").
                // Create the corresponding Move object (player_move).
                // Do not accept the player's move if it's not in the moves vector!
                string player_input;
                cout << "Enter your move: ";
                cin >> player_input;

                // Check if the player's move is valid.
                bool valid_move = false;
                for (const auto& move : moves)
                {
                        if (move.to_string() == player_input)
                        {
                                valid_move = true;
                                // Make the move on the board.
                                position.make_move(move);
                                break;
                        }
                }

                if (!valid_move)
                {
                        cout << "Invalid move! Please try again." << endl;
                        continue;
                }

                moves.clear();
                position.generate_all_raw_moves(position._turn, moves);
        }

        return 0;
}
