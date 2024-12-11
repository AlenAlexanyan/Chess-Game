#include <iostream>
#include <string>
#include "Game.h" // Include the header file for the Game class

int main() {
    Game chessGame; // Create an instance of the Game class

    // Main game loop
    while (true) {
        chessGame.displayBoard(); // Display the current state of the board

        // Input the player's move
        std::cout << "Turn: " << (chessGame.getTurn() ? "White" : "Black") << std::endl;
        std::string move;
        std::cout << "Enter your move (e.g., e2 e4): ";
        std::getline(std::cin, move);

        // Split the input into "from" and "to" positions
        if (move.size() != 5 || move[2] != ' ') {
            std::cout << "Invalid input format! Use 'from to'. Try again.\n";
            continue;
        }
        std::string from = move.substr(0, 2);
        std::string to = move.substr(3, 2);

        // Validate and execute the move
        if (!chessGame.checkMovePiece(from, to)) {
            std::cout << "Invalid move! (" << from << " -> " << to << ") Try again.\n";
            continue; // Prompt for re-entry on invalid moves
        }

        // Check for endgame states
        if (chessGame.isCheck()) {
            if (chessGame.isCheckMate()) {
                chessGame.displayBoard();
                std::cout << "\nCHECKMATE!!!!!" << std::endl;
                std::cout << (chessGame.getTurn() ? "Black" : "White") << " wins.\n";
                return 0;
            }
        } else if (chessGame.isDraw()) {
            std::cout << "It's a draw!" << std::endl;
            return 0;
        }

        // Switch turn (Black or White)
        chessGame.changeMove();
    }

    return 0; // Exit the program
}