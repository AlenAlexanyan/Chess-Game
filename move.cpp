#include "move.h"
#include "display_functions.h"
#include "logic.h"
#include "globals.h"
#include <iostream>
#include <string>

// Moves a piece on the chessboard by updating its position in the array.
void movePiece(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol) {
    // Copy the piece to the target position.
    board[toRow][toCol] = board[fromRow][fromCol];
    // Clear the original position.
    board[fromRow][fromCol] = ' ';  
}

// Validates a move based on chess rules and executes it if valid.
bool checkMovePiece(char board[BOARD_SIZE][BOARD_SIZE], std::string from, std::string to) {
    // Convert chess notation (e.g., "e2") to array indices.
    int fromRow = BOARD_SIZE - (from[1] - '0');  // Convert rank (row).
    int fromCol = from[0] - 'a';        // Convert file (column).
    int toRow = BOARD_SIZE - (to[1] - '0');
    int toCol = to[0] - 'a';

    // Debug: Print the computed indices.
    std::cout << "From: (" << fromRow << ", " << fromCol << ") "
              << "To: (" << toRow << ", " << toCol << ")\n";

    // Ensure the move is within the chessboard's bounds.
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol)) {
        std::cout << "Invalid move! The position is out of bounds.\n";
        return false;
    }

    // Validate the move based on the piece type.
    char piece = board[fromRow][fromCol];
    bool validMove = false;

    switch (piece) {
        case 'p': case 'P':  // Pawn
            validMove = isPossibleMoveForPawn(board, fromRow, fromCol, toRow, toCol);
            break;
        case 'r': case 'R':  // Rook
            validMove = isPossibleMoveForRook(board, fromRow, fromCol, toRow, toCol);
            break;
        case 'n': case 'N':  // Knight
            validMove = isPossibleMoveForKnight(board, fromRow, fromCol, toRow, toCol);
            break;
        case 'b': case 'B':  // Bishop
            validMove = isPossibleMoveForBishop(board, fromRow, fromCol, toRow, toCol);
            break;
        case 'q': case 'Q':  // Queen
            validMove = isPossibleMoveForQueen(board, fromRow, fromCol, toRow, toCol);
            break;
        case 'k': case 'K':  // King
            validMove = isPossibleMoveForKing(board, fromRow, fromCol, toRow, toCol);
            break;
        default:
            std::cout << "No valid piece at this position. Try again.\n";
            return false;
    }

    // If the move is valid, execute it.
    if (validMove) {
        movePiece(board, fromRow, fromCol, toRow, toCol);
        return true;
    }

    std::cout << "Invalid move for the selected piece.\n";
    return false;
}