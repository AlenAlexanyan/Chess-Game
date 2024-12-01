#include "board_display.h"
#include "game_logic.h"
#include "game_state.h"
#include <iostream>
#include <string>

// Moves a piece on the chessboard by updating its position in the array.
void movePiece(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol, char piece) {

    char currentPosition = board[fromRow][fromCol];
    char destination = board[toRow][toCol];

    // Determine if the piece is white or black
    bool isWhitePiece = (currentPosition >= 'A' && currentPosition <= 'Z');
    bool isBlackPiece = (currentPosition >= 'a' && currentPosition <= 'z');

    char column = 'a' + fromCol; // Convert column index to letter
    std::string currentKey = std::string(1, currentPosition) + column + std::to_string(BOARD_SIZE - fromRow);

    bool isDelete = destination != ' ';

    // Handle pawn promotion
    if (piece != '\0') {
        // Validate the promotion piece
        if ((isWhitePiece && piece >= 'A' && piece <= 'Z') || (isBlackPiece && piece >= 'a' && piece <= 'z')) {
            board[fromRow][fromCol] = ' ';
            board[toRow][toCol] = piece;

            // Update global maps with the promoted piece
            if (isWhitePiece) {
                ALL_WHITE_PIECES.erase(currentKey); // Remove the old pawn entry
                std::string newKey = std::string(1, piece) + std::to_string(BOARD_SIZE - toRow); // e.g., "Qa8"
                ALL_WHITE_PIECES[newKey] = {toRow, toCol};
            } else if (isBlackPiece) {
                ALL_BLACK_PIECES.erase(currentKey);
                std::string newKey = std::string(1, piece) + std::to_string(BOARD_SIZE - toRow); // e.g., "qa1"
                ALL_BLACK_PIECES[newKey] = {toRow, toCol};
            }
        } else {
            std::cerr << "Invalid promotion piece!" << std::endl;
            return; // Exit function if promotion piece is invalid
        }
    } else {
        // Normal piece movement
        board[toRow][toCol] = board[fromRow][fromCol];
        board[fromRow][fromCol] = ' ';
    }

    // std::cout << "Current Key: " << currentKey << std::endl;

    // Update global maps for normal moves
    if (isWhitePiece) {
        if (ALL_WHITE_PIECES.find(currentKey) != ALL_WHITE_PIECES.end()) {
            ALL_WHITE_PIECES[currentKey] = {toRow, toCol}; // Update position without changing the key
            if (isDelete) {
                ALL_WHITE_PIECES.erase(std::string(1, destination) + std::to_string(BOARD_SIZE - toRow));
            }
        }
    } else if (isBlackPiece) {
        if (ALL_BLACK_PIECES.find(currentKey) != ALL_BLACK_PIECES.end()) {
            ALL_BLACK_PIECES[currentKey] = {toRow, toCol}; // Update position without changing the key
            if (isDelete) {
                ALL_BLACK_PIECES.erase(std::string(1, destination) + std::to_string(BOARD_SIZE - toRow));
            }
        }
    }
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
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol) || !doesMoveKeepKingSafe(board, fromRow, fromCol, toRow, toCol)) {
        std::cout << "Invalid move!\n";
        return false; 
    }

    char PieceToBe = '\0';

    // Validate the move based on the piece type.
    char piece = board[fromRow][fromCol];
    bool validMove = false;

    switch (piece) {
        case 'p': case 'P':  // Pawn
            validMove = isPossibleMoveForPawn(board, fromRow, fromCol, toRow, toCol);
            std::cout << "Valid Move: " <<validMove << std::endl;
            if (validMove && (toRow == 7 || toRow == 0)) {
                std::cout << "Write the Figure to Be: ";
                std::cin >> PieceToBe;
                std::cout << std::endl;
            }
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
        movePiece(board, fromRow, fromCol, toRow, toCol, PieceToBe);
        return true;
    }

    std::cout << "Invalid move for the selected piece.\n";
    return false;
}