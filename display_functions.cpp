#include <iostream>
#include "globals.h"           // For global variables like blackPieces and whitePieces
#include "display_functions.h" // Function declarations for initializing and displaying the board

// Function to initialize the chessboard with default piece positions
void initializeBoard(char board[8][8]) {
    // Set all board squares to empty
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = ' '; // Empty square
        }
    }

    // Place pawns
    for (int i = 0; i < 8; i++) {
        board[1][i] = 'p'; // Black pawns
        board[6][i] = 'P'; // White pawns
    }

    // Place other pieces
    for (int i = 0; i < 8; i++) {
        board[0][i] = blackPieces[i]; // Black pieces (row 0)
        board[7][i] = whitePieces[i]; // White pieces (row 7)
    }
}

// Function to display the chessboard
void displayBoard(char board[8][8]) {
    std::cout << "\n"; // Print a blank line for better spacing
    for (int i = 0; i < 8; i++) {
        // Print row number
        std::cout << 8 - i << " ";
        
        // Print all squares in the row
        for (int j = 0; j < 8; j++) {
            std::cout << board[i][j] << ' '; // Print the piece or empty square
        }
        std::cout << '\n'; // Move to the next row
    }
    
    // Print column labels
    std::cout << "  a b c d e f g h\n";
}