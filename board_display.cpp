#include <iostream>
#include "game_state.h"

// Function to initialize the chessboard with default piece positions
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Set all board squares to empty
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' '; // Empty square
        }
    }

    // Place pawns
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = 'p'; // Black pawns
        board[6][i] = 'P'; // White pawns
    }

    // Place other pieces
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[0][i] = BLACK_PIECES[i]; // Black pieces
        board[7][i] = WHITE_PIECES[i]; // White pieces
    }
}

// Function to display the chessboard
void displayBoard(const char board[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << "\n"; // Print a blank line for better spacing

    // Loop through each row of the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << 8 - i << "  "; // Print row numbers (8 to 1)

        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j] << ' '; // Display the piece or empty square
        }
        std::cout << '\n'; // Move to the next row
    }

    // Print column labels
    std::cout << std::endl << "   a b c d e f g h\n";
}