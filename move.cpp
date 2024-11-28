#include <iostream>
#include <string>
#include "display_functions.h"
#include "logic.h"
#include "globals.h"

// Function to move a piece on the board
void movePiece(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    // Move the piece to the new position
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = ' ';  // Clear the original position
}

// Function to check if a move is valid and execute it
bool checkMovePiece(char board[8][8], std::string from, std::string to) {
    // Convert board coordinates from chess notation (e.g., "a2") to array indices
    int fromRow = 8 - (from[1] - '0'); 
    int fromCol = from[0] - 'a';       

    int toRow = 8 - (to[1] - '0');
    int toCol = to[0] - 'a';

    // Debugging: print the indices
    std::cout << fromRow << ' ' << fromCol << ' ' << toRow << ' ' << toCol << std::endl;

    // Validate the move (check if it is within bounds and allowed for the piece)
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol)) {
        std::cout << "Invalid move! Out of bounds.\n";
        return false;
    }

    // Determine the piece type and check if the move is valid for that piece
    switch (board[fromRow][fromCol]) {
        case 'p':  // Pawn
        case 'P':
            if (isPosibleMoveForPawn(board, fromRow, fromCol, toRow, toCol)) {
                std::cout << " Its posible move for pawn" << std::endl;
                movePiece(board, fromRow, fromCol, toRow, toCol);
                return true;
            }
            break;
        case 'r':  // Rook
        case 'R':
            if (isPosibleMoveForRook(board, fromRow, fromCol, toRow, toCol)) {
                movePiece(board, fromRow, fromCol, toRow, toCol);
                return true;
            }
            break;
        case 'n':  // Knight
        case 'N':
            // Add knight move logic here
            break;
        case 'b':  // Bishop
        case 'B':
            if (isPosibleMoveForBishop(board, fromRow, fromCol, toRow, toCol)) {
                movePiece(board, fromRow, fromCol, toRow, toCol);
                return true;
            }
            break;
        case 'q':  // Queen
        case 'Q':
            if (isPosibleMoveForQueen(board, fromRow, fromCol, toRow, toCol)) {
                movePiece(board, fromRow, fromCol, toRow, toCol);
                return true;
            }
            break;
        case 'k':  // King
        case 'K':
            if (isPosibleMoveForKing(board, fromRow, fromCol, toRow, toCol)) {
                movePiece(board, fromRow, fromCol, toRow, toCol);
                return true;
            }
            break;
        default:
            std::cout << "No valid figure at this position. Try again.\n";
            return false;
    }

    // If no valid move was found
    return false;
}