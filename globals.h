#ifndef GLOBALS_H
#define GLOBALS_H

// Global variable to track the current turn: false for Black, true for White
extern bool black_or_white;

// Arrays representing the initial positions of White and Black pieces
extern const char whitePieces[8];
extern const char blackPieces[8];

extern bool whiteCheck;
extern bool blackCheck;

extern std::pair<int, int> WhiteKing;
extern std::pair<int, int> BlackKing;

extern std::pair<int, int> CheckKing;

#endif // GLOBALS_H