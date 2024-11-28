#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include "globals.h"

// Function to switch turns between Black and White
void changeMove();

// Function to check if it's White's turn to move
bool isWhitesMove();

// Function to check if the piece at a given position is a White piece
bool isWhiteFigure(char board[BOARD_SIZE][BOARD_SIZE], int Row, int Col);

// Function to check if the piece at a given position is a Black piece
bool isBlackFigure(char board[BOARD_SIZE][BOARD_SIZE], int Row, int Col);

// Function to validate a move based on the current board state and piece positions
bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a pawn can make a valid move from its current position
bool isPossibleMoveForPawn(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a knight can make a valid move from its current position
bool isPossibleMoveForKnight(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a bishop can make a valid move from its current position
bool isPossibleMoveForBishop(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a rook can make a valid move from its current position
bool isPossibleMoveForRook(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a queen can make a valid move from its current position
bool isPossibleMoveForQueen(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol);

// Function to determine if a king can make a valid move from its current position
bool isPossibleMoveForKing(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol);

// Function to check if a piece can make a valid move based on its type
bool isPossibleMove(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol);

// Helper function to check if the figure matches the color (true for white, false for black)
bool isCorrectFigure(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, bool isWhite);

// Function that returns all possible fields between two positions on diagonal or straight lines.
std::vector<std::pair<int, int>> allPossibleFields(int checkRow, int checkCol, int kingRow, int kingCol);

// Function that checks whether any pieces are attacking their respective kings.
bool isCheck(char board[BOARD_SIZE][BOARD_SIZE]);

// Function that checks whether any player’s king has no legal moves left.
bool isCheckMate(char board[BOARD_SIZE][BOARD_SIZE]);

#endif // LOGIC_H