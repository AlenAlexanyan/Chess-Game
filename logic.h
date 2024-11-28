#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include <utility>

// Function to validate a move based on the current board state and piece positions
bool isValidMove(char board[8][8], int fromRow, int fromCol, int toRow, int toCol);

// Function to check if it's White's turn to move
bool isWhitesMove();

// Function to switch turns between Black and White
void changeMove();

// Function to check if the piece at a given position is a White piece
bool isWhiteFigure(char board[8][8], int Row, int Col);

// Function to check if the piece at a given position is a Black piece
bool isBlackFigure(char board[8][8], int Row, int Col);

// Function to determine if a pawn can make a valid move from its current position
bool isPosibleMoveForPawn(char board[8][8], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a bishop can make a valid move from its current position
bool isPosibleMoveForBishop(char board[8][8], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a rook can make a valid move from its current position
bool isPosibleMoveForRook(char board[8][8], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a queen can make a valid move from its current position
bool isPosibleMoveForQueen(char board[8][8], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a king can make a valid move from its current position
bool isPosibleMoveForKing(char board[8][8], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a knight can make a valid move from its current position
bool isPosibleMoveForKnight(char board[8][8], int fromRow, int fromCol, int toRow, int toCol);

bool isCheck(char board[8][8]);

bool isCheckMate(char board[8][8]);

// In a relevant header file (e.g., logic.h or globals.h)
std::vector<std::pair<int, int>> allPosibleFields(int kingRow, int kingCol, int checkRow, int checkCol);
bool isCorrectFigure(char board[8][8], int row, int col, bool white);


#endif