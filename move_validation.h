#ifndef MOVE_H
#define MOVE_H

#include "game_state.h"
#include <string>

// Function to move a piece on the chessboard.
// Parameters:
// - board: 2D array representing the chessboard.
// - fromRow: Starting row of the piece.
// - fromCol: Starting column of the piece.
// - toRow: Target row of the piece.
// - toCol: Target column of the piece.
void movePiece(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol);

// Function to validate and execute a move on the chessboard.
// Parameters:
// - board: 2D array representing the chessboard.
// - from: Chess notation (e.g., "e2") for the piece's current position.
// - to: Chess notation (e.g., "e4") for the target position.
// Returns:
// - true if the move is valid and executed; false otherwise.
bool checkMovePiece(char board[BOARD_SIZE][BOARD_SIZE], std::string from, std::string to);

#endif // MOVE_H