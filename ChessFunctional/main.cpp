#include <iostream>
#include <string>
#include "board_display.h"          // For displaying the chess board
#include "game_logic.h"             // For game logic
#include "game_state.h"             // For global variables
#include "move_validation.h"        // For move-related functions

// Main function to initialize and run the chess game
int main() {
    char board[8][8]; // 2D array to represent the chess board
    initializeBoard(board); // Initialize the chess board with default pieces

    // Main game loop
    while (true) {
        displayBoard(board); // Display the current state of the board

        // Input the player's move
        std::cout << "Turn: " << IS_WHITE_TURN << std::endl;
        std::string move;
        std::cout << "Enter your move (e.g., e2 e4): ";
        std::getline(std::cin, move);

        // Split the input into from and to positions
        if (move.size() != 5 || move[2] != ' ') {
            std::cout << "Invalid input format! Use 'from to'. Try again.\n";
            continue;
        }
        std::string from = move.substr(0, 2);
        std::string to = move.substr(3, 2);

        // Validate and execute the move
        if (!checkMovePiece(board, from, to)) {
            std::cout << "Invalid move! (" << from << " -> " << to << ") Try again.\n";
            continue; // Prompt for re-entry on invalid moves
        }

        if (isCheck(board) && isCheckMate(board)) {
            std::string mated = !IS_WHITE_IN_CHECK ? "White" : "Black";
            displayBoard(board);
            std::cout << std::endl << "CHECKMATE!!!!!" << std::endl << mated << "`s  win.";
            return 0;
        }
        else if (isDraw(board)) {
            std::cout << "It's a draw!" << std::endl;
            return 0;
        } else {
            // Switch turn (black or white)
            changeMove();
        }
    }

    return 0; // Exit the program
}
