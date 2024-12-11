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
        std::string from, to;
        std::cout << "Enter your move (e.g., e2 e4): ";
        std::cin >> from >> to;

        // Validate and execute the move
        if (!checkMovePiece(board, from, to)) {
            std::cout << "Invalid move! (" << from << " -> " << to << ") " << "Try again.\n";
            continue; // Prompt for re-entry on invalid moves
        }

        if (isCheck(board) && isCheckMate(board)) {
            std::string mated = !IS_WHITE_IN_CHECK ? "White" : "Black";
            displayBoard(board);
            std::cout << std::endl << "CHECKMATE!!!!!" << std::endl << mated <<"`s  win." ;
            return 0;
        }
        //TODO Check isDraw()
        else if (isDraw(board)){
            std::cout << "It`s draw!" << std::endl;
            return 0;
        }
        
        else {
            // Switch turn (black or white)
            changeMove();
        }

    }

    return 0; // Exit the program
}