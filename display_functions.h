#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H

#include "globals.h"

// Function to initialize the chessboard with starting positions
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]);

// Function to display the current state of the chessboard
void displayBoard(const char board[BOARD_SIZE][BOARD_SIZE]);

#endif // DISPLAY_FUNCTIONS_H