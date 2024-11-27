#include <iostream>
#include <vector>
#include "globals.h"

// Function to check if it's White's turn
bool isWhitesMove()
{
    return black_or_white;
}

// Function to check if the piece at the given position is a White piece
bool isWhiteFigure(char board[8][8], int Row, int Col)
{
    if (isupper(board[Row][Col]))
    {
        std::cout << "You are right again!!!" << std::endl;
        return true;
    }
    return false;
}

// Function to check if the piece at the given position is a Black piece
bool isBlackFigure(char board[8][8], int Row, int Col)
{
    if (islower(board[Row][Col]))
    {
        std::cout << "You are right again!!!" << std::endl;
        return true;
    }
    return false;
}

// Function to validate the move based on the piece's color and target position
bool isValidMove(char board[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
    // Check for White's move and the validity of the move for White
    if (isWhitesMove())
    {
        std::cout << "I am white!" << std::endl;
        if (!isWhiteFigure(board, fromRow, fromCol) || isWhiteFigure(board, toRow, toCol) ||
            fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8)
        {
            std::cout << "I am false" << std::endl;
            return false;
        }
    }
    // Check for Black's move and the validity of the move for Black
    else if (isWhiteFigure(board, fromRow, fromCol) || isBlackFigure(board, toRow, toCol) ||
             fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
             toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8)
    {
        std::cout << "I am black!" << std::endl;
        return false;
    }
    return true;
}

// Function to switch turns between Black and White
void changeMove()
{
    black_or_white = !black_or_white;
}

// Function to check if a pawn can make a valid move
bool isPosibleMoveForPawn(char board[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
    // White pawn movement logic
    if (isWhitesMove())
    {
        if (!isWhiteFigure(board, fromRow, fromCol))
        {
            return false;
        }

        // Move one step forward or two steps from the starting row
        if ((fromCol == toCol) && (board[toRow][toCol] == ' ') &&
            ((abs(toRow - fromRow) == 1) || (fromRow == 6 && abs(toRow - fromRow) == 2)))
        {
            return true;
        }

        // Pawn capture (diagonal move to capture an enemy piece)
        if (abs(fromCol - toCol) == 1 && toRow - fromRow == 1 && !isWhiteFigure(board, toRow, toCol))
        {
            return true;
        }

        return false;
    }
    // Black pawn movement logic
    else
    {
        if (isWhiteFigure(board, fromRow, fromCol))
        {
            return false;
        }

        // Move one step forward or two steps from the starting row
        if (fromCol == toCol && board[toRow][toCol] == ' ' &&
            ((abs(fromRow - toRow) == 1) || (fromRow == 1 && abs(fromRow - toRow) == 2)))
        {
            return true;
        }

        // Pawn capture (diagonal move to capture an enemy piece)
        if (abs(fromCol - toCol) == 1 && fromRow - toRow == 1 && isWhiteFigure(board, toRow, toCol))
        {
            return true;
        }

        return false;
    }
}

// Function to check if a bishop can make a valid move
bool isPosibleMoveForBishop(char board[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol))
    {
        return false;
    }

    // Bishops move diagonally, so check if the row and column difference are equal
    if (abs(fromRow - toRow) != abs(fromCol - toCol))
        return false;

    int direction;
    if ((toRow - fromRow) > 0 && (fromCol - toCol) > 0)
        direction = 1;
    else if ((toRow - fromRow) > 0)
        direction = 2;
    else if ((toCol - fromCol) < 0)
        direction = 3;
    else
        direction = 4;

    // Check for obstruction along the diagonal path
    if (direction == 1)
    {
        for (int i = fromRow + 1, j = fromCol + 1; i < toRow && j < toCol; ++i, ++j)
        {
            if (board[i][j] != ' ')
                return false;
        }
        return true;
    }
    else if (direction == 2)
    {
        for (int i = fromRow + 1, j = fromCol - 1; i < toRow && j > toCol; ++i, --j)
        {
            if (board[i][j] != ' ')
                return false;
        }
        return true;
    }
    else if (direction == 3)
    {
        for (int i = fromRow - 1, j = fromCol - 1; i > toRow && j > toCol; --i, --j)
        {
            if (board[i][j] != ' ')
                return false;
        }
        return true;
    }
    else
    {
        for (int i = fromRow - 1, j = fromCol + 1; i > toRow && j < toCol; --i, ++j)
        {
            if (board[i][j] != ' ')
                return false;
        }
        return true;
    }
}

// Function to check if a rook can make a valid move
bool isPosibleMoveForRook(char board[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol))
    {
        return false;
    }

    int direction;
    if ((toCol - fromCol) == 0)
    {
        if ((toRow - fromRow) > 0)
            direction = 1;
        else
            direction = 3;
    }
    else
    {
        if ((toCol - fromCol) > 0)
            direction = 4;
        else
            direction = 2;
    }

    // Check for obstruction along the row or column
    if (direction == 1)
    {
        for (int i = fromRow + 1; i < toRow; ++i)
        {
            if (board[i][fromCol] != ' ')
                return false;
        }
        return true;
    }
    else if (direction == 2)
    {
        for (int j = fromCol - 1; j > toCol; --j)
        {
            if (board[fromRow][j] != ' ')
                return false;
        }
        return true;
    }
    else if (direction == 3)
    {
        for (int i = fromRow - 1; i > toCol; --i)
        {
            if (board[i][fromCol] != ' ')
                return false;
        }
        return true;
    }
    else
    {
        for (int j = fromCol + 1; j < toCol; ++j)
        {
            if (board[fromRow][j] != ' ')
                return false;
        }
        return true;
    }
}

// Function to check if a queen can make a valid move (combining bishop and rook moves)
bool isPosibleMoveForQueen(char board[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
    return (
        isPosibleMoveForBishop(board, fromRow, fromCol, toRow, toCol) ||
        isPosibleMoveForRook(board, fromRow, fromCol, toRow, toCol));
}

// Function to check if a king can make a valid move
bool isPosibleMoveForKing(char board[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol))
    {
        return false;
    }

    // The king can move one square in any direction
    if (abs(fromRow - toRow) <= 1 && abs(fromCol - toCol) <= 1)
    {
        return true;
    }
    return false;
}

bool isPosibleMoveForKnight(char board[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol))
    {
        return false;
    }

    if (abs(toRow - fromRow) > 0 && abs(toCol - fromCol) > 0)
    {
        if (abs(toRow - fromRow) + abs(toCol - fromCol) == 3)
        {
            return true;
        }
    }

    return false;
}

bool isPosibleMove(char board[8][8],  int fromRow, int fromCol, int toRow, int toCol) {
    return isPosibleMoveForPawn(board, fromRow, fromCol, toRow, toCol) ||
            isPosibleMoveForKnight(board, fromRow, fromCol, toRow, toCol) ||
            isPosibleMoveForBishop(board, fromRow, fromCol, toRow, toCol) ||
            isPosibleMoveForKing(board, fromRow, fromCol, toRow, toCol);
}

// Function to check if any piece is attacking the king (check condition)
bool IsCheck(char board[8][8])
{
    std::pair<int, int> WhiteKingCoordinates;
    std::pair<int, int> BlackKingCoordinates;

    // Identify the positions of the kings
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; ++j) {
            if (board[i][j] == 'k') {
                BlackKingCoordinates.first = i;
                BlackKingCoordinates.second = j;
            }
            if (board[i][j] == 'K') {
                WhiteKingCoordinates.first = i;
                WhiteKingCoordinates.second = j;
            }
        }
    }

    WhiteKing = WhiteKingCoordinates;
    BlackKing = BlackKingCoordinates;

    // Check for attacks from different pieces
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            char piece = board[i][j];
            std::pair<int, int> targetKing = (piece >= 'a' && piece <= 'z') ? WhiteKing : BlackKing;
            bool isCheck = false;

            switch (piece) {
                case 'q': case 'Q':
                    isCheck = isPosibleMoveForQueen(board, i, j, targetKing.first, targetKing.second);
                    break;
                case 'n': case 'N':
                    isCheck = isPosibleMoveForKnight(board, i, j, targetKing.first, targetKing.second);
                    break;
                case 'r': case 'R':
                    isCheck = isPosibleMoveForRook(board, i, j, targetKing.first, targetKing.second);
                    break;
                case 'b': case 'B':
                    isCheck = isPosibleMoveForBishop(board, i, j, targetKing.first, targetKing.second);
                    break;
                case 'p': case 'P':
                    isCheck = isPosibleMoveForPawn(board, i, j, targetKing.first, targetKing.second);
                    break;
            }

            if (isCheck) {
                CheckKing = {i, j};
                return true;
            }
        }
    }

    return false;
}

// Function to check if the current player is in checkmate
bool IsCheckMate(char board[8][8])
{
    // Determine which king is in check and get the closing positions
    std::pair<int, int> checkKing = (whiteCheck) ? WhiteKing : BlackKing;
    std::vector<std::pair<int, int>> closingFields = allPosibleFields(CheckKing.first, CheckKing.second, checkKing.first, checkKing.second);
    closingFields.emplace_back(CheckKing.first, CheckKing.second);

    // Try to block the check by moving pieces
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (isCorrectFigure(board, row, col, whiteCheck)) {
                for (auto &field : closingFields) {
                    if (isPosibleMove(board, row, col, field.first, field.second)) {
                        return false; // Found a valid move to block check
                    }
                }
            }
        }
    }

    // Check if the king can escape from check by moving to adjacent squares
    for (int row = checkKing.first - 1; row <= checkKing.first + 1; ++row) {
        for (int col = checkKing.second - 1; col <= checkKing.second + 1; ++col) {
            if (row >= 0 && row < 8 && col >= 0 && col < 8 && (row != checkKing.first || col != checkKing.second)) {
                bool canEscape = true;
                for (int i = 0; i < 8 && canEscape; ++i) {
                    for (int j = 0; j < 8 && canEscape; ++j) {
                        if (isCorrectFigure(board, i, j, !whiteCheck) && !isPosibleMove(board, i, j, row, col)) {
                            canEscape = false;
                        }
                    }
                }
                if (canEscape) {
                    return false; // King can escape from check
                }
            }
        }
    }

    return true; // No valid moves to escape or block, it's checkmate
}

// Helper function to check if the figure matches the color (true for white, false for black)
bool isCorrectFigure(char board[8][8], int row, int col, bool isWhite) {
    char piece = board[row][col];
    return (isWhite && piece >= 'A' && piece <= 'Z') || (!isWhite && piece >= 'a' && piece <= 'z');
}

std::vector<std::pair<int, int>> allPosibleFields(int checkRow, int checkCol, int kingRow, int kingCol)
{
    int direction;
    if (checkRow == kingRow) direction = 1;
    else if (checkCol == kingCol) direction = 2;
    else direction = 3;

    std::vector<std::pair<int, int>> positions;

    if (direction == 1) {
        int startCol = std::min(checkCol, kingCol);
        int endCol = std::max(checkCol, kingCol);
        for (int col = startCol + 1; col < endCol; ++col) {
            positions.emplace_back(checkRow, col);
        }
    }
    else if (direction == 2) {
        int startRow = std::min(checkRow, kingRow);
        int endRow = std::max(checkRow, kingRow);
        for (int row = startRow + 1; row < endRow; ++row) {
            positions.emplace_back(row, checkCol);
        }
    }
    else if (direction == 3) {
        int rowStep = (kingRow > checkRow) ? 1 : -1;
        int colStep = (kingCol > checkCol) ? 1 : -1;
        int row = checkRow + rowStep, col = checkCol + colStep;
        while (row != kingRow && col != kingCol) {
            positions.emplace_back(row, col);
            row += rowStep;
            col += colStep;
        }
    }

    return positions;
}