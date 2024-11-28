#include <iostream>
#include <string>
#include "display_functions.h" // For displaying the chess board
#include "logic.h"             // For game logic
#include "globals.h"           // For global variables
#include "move.h"              // For move-related functions

// Main function to initialize and run the chess game
int main() {
    char board[8][8]; // 2D array to represent the chess board
    initializeBoard(board); // Initialize the chess board with default pieces

    // Main game loop
    while (true) {
        displayBoard(board); // Display the current state of the board

        // Input the player's move
        std::string from, to;
        std::cout << "Enter your move (e.g., e2 e4): ";
        std::cin >> from >> to;

        // Validate and execute the move
        if (!checkMovePiece(board, from, to)) {
            std::cout << "Invalid move! Try again.\n"; // Prompt for re-entry on invalid moves
        }

        if (isCheck(board) && isCheckMate(board)) {
            std::string mated = !whiteCheck ? "White" : "Black";
            std::cout << mated <<"`s  win." ;
            return 0;
        }
        else {
            // Switch turn (black or white)
            changeMove();
        }

    }

    return 0; // Exit the program
}