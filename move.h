#ifndef MOVE_H
#define MOVE_H

#include <string>

// Function to move a piece on the board
void movePiece(char board[8][8], int fromRow, int fromCol, int toRow, int toCol);

// Function to check if a move is valid and execute it
bool checkMovePiece(char board[8][8], std::string from, std::string to);

#endif