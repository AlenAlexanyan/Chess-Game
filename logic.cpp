#include <iostream>
#include "globals.h"

// Function to check if it's White's turn
bool isWhitesMove() {
    return black_or_white;
}

// Function to check if the piece at the given position is a White piece
bool isWhiteFigure(char board[8][8], int Row, int Col) {
    if (isupper(board[Row][Col])) {
        std::cout << "You are right again!!!" << std::endl;
        return true;
    }
    return false;
}

// Function to check if the piece at the given position is a Black piece
bool isBlackFigure(char board[8][8], int Row, int Col) {
    if (islower(board[Row][Col])) {
        std::cout << "You are right again!!!" << std::endl;
        return true;
    }
    return false;
}

// Function to validate the move based on the piece's color and target position
bool isValidMove(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    // Check for White's move and the validity of the move for White
    if (isWhitesMove()) {
        std::cout << "I am white!" << std::endl;
        if (!isWhiteFigure(board, fromRow, fromCol) || isWhiteFigure(board, toRow, toCol) ||
            fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
            std::cout << "I am false" << std::endl;
            return false;
        }
    }
    // Check for Black's move and the validity of the move for Black
    else if (isWhiteFigure(board, fromRow, fromCol) || isBlackFigure(board, toRow, toCol) ||
            fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        std::cout << "I am black!" << std::endl;
        return false;
    }
    return true;
}

// Function to switch turns between Black and White
void changeMove() {
    black_or_white = !black_or_white;
}

// Function to check if a pawn can make a valid move
bool isPosibleMoveForPawn(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    // White pawn movement logic
    if (isWhitesMove()) {
        if (!isWhiteFigure(board, fromRow, fromCol)) {
            return false;
        }

        // Move one step forward or two steps from the starting row
        if ((fromCol == toCol) && (board[toRow][toCol] == ' ') && 
            ((abs(toRow - fromRow) == 1) || (fromRow == 6 && abs(toRow - fromRow) == 2))) {
            return true;
        }

        // Pawn capture (diagonal move to capture an enemy piece)
        if (abs(fromCol - toCol) == 1 && toRow - fromRow == 1 && !isWhiteFigure(board, toRow, toCol)) {
            return true;
        }

        return false;
    }
    // Black pawn movement logic
    else {
        if (isWhiteFigure(board, fromRow, fromCol)) {
            return false;
        }

        // Move one step forward or two steps from the starting row
        if (fromCol == toCol && board[toRow][toCol] == ' ' && 
            ((abs(fromRow - toRow) == 1) || (fromRow == 1 && abs(fromRow - toRow) == 2))) {
            return true;
        }

        // Pawn capture (diagonal move to capture an enemy piece)
        if (abs(fromCol - toCol) == 1 && fromRow - toRow == 1 && isWhiteFigure(board, toRow, toCol)) {
            return true;
        }

        return false;
    }
}

// Function to check if a bishop can make a valid move
bool isPosibleMoveForBishop(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol)) {
        return false;
    }

    // Bishops move diagonally, so check if the row and column difference are equal
    if (abs(fromRow - toRow) != abs(fromCol - toCol)) return false;

    int direction;
    if ((toRow - fromRow) > 0 && (fromCol - toCol) > 0) direction = 1;
    else if ((toRow - fromRow) > 0) direction = 2;
    else if ((toCol - fromCol) < 0) direction = 3;
    else direction = 4;

    // Check for obstruction along the diagonal path
    if (direction == 1) {
        for (int i = fromRow + 1, j = fromCol + 1; i < toRow && j < toCol; ++i, ++j) {
            if (board[i][j] != ' ') return false;
        }
        return true;
    }
    else if (direction == 2) {
        for (int i = fromRow + 1, j = fromCol - 1; i < toRow && j > toCol; ++i, --j) {
            if (board[i][j] != ' ') return false;
        }
        return true;
    }
    else if (direction == 3) {
        for (int i = fromRow - 1, j = fromCol - 1; i > toRow && j > toCol; --i, --j) {
            if (board[i][j] != ' ') return false;
        }
        return true;
    }
    else {
        for (int i = fromRow - 1, j = fromCol + 1; i > toRow && j < toCol; --i, ++j) {
            if (board[i][j] != ' ') return false;
        }
        return true;
    }
}

// Function to check if a rook can make a valid move
bool isPosibleMoveForRook(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol)) {
        return false;
    }

    int direction;
    if ((toCol - fromCol) == 0) {
        if ((toRow - fromRow) > 0) direction = 1;
        else direction = 3;
    }
    else {
        if ((toCol - fromCol) > 0) direction = 4;
        else direction = 2;
    }

    // Check for obstruction along the row or column
    if (direction == 1) {
        for (int i = fromRow + 1; i < toRow; ++i) {
            if (board[i][fromCol] != ' ') return false;
        }
        return true;
    }
    else if (direction == 2) {
        for (int j = fromCol - 1; j > toCol; --j) {
            if (board[fromRow][j] != ' ') return false;
        }
        return true;
    }
    else if (direction == 3) {
        for (int i = fromRow - 1; i > toCol; --i) {
            if (board[i][fromCol] != ' ') return false;
        }
        return true;
    }
    else {
        for (int j = fromCol + 1; j < toCol; ++j) {
            if (board[fromRow][j] != ' ') return false;
        }
        return true;
    }
}

// Function to check if a queen can make a valid move (combining bishop and rook moves)
bool isPosibleMoveForQueen(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    return (
        isPosibleMoveForBishop(board, fromRow, fromCol, toRow, toCol) ||
        isPosibleMoveForRook(board, fromRow, fromCol, toRow, toCol)
    );
}

// Function to check if a king can make a valid move
bool isPosibleMoveForKing(char board[8][8], int fromRow, int fromCol, int toRow, int toCol) {
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol)) {
        return false;
    }

    // The king can move one square in any direction
    if (abs(fromRow - toRow) <= 1 && abs(fromCol - toCol) <= 1) {
        return true;
    }
    return false;
}