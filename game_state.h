#ifndef GLOBALS_H
#define GLOBALS_H

#include <utility>

// Board dimensions (8x8 for a standard chessboard)
inline constexpr unsigned short int BOARD_SIZE = 8;

// Global variable to track the current player's turn
// true = White's turn, false = Black's turn
extern bool IS_WHITE_TURN;

// Arrays representing the initial positions of White and Black pieces
// WHITE_PIECES: {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
// BLACK_PIECES: {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
extern const char WHITE_PIECES[BOARD_SIZE];
extern const char BLACK_PIECES[BOARD_SIZE];

// Flag to indicate if White or Black king is in check
extern bool IS_WHITE_IN_CHECK;

// Coordinates of the White and Black kings on the board
extern std::pair<int, int> WHITE_KING_POSITION;
extern std::pair<int, int> BLACK_KING_POSITION;

// Coordinates of the piece delivering a check to a king
extern std::pair<int, int> CHECKING_PIECE_POSITION;

#endif // GLOBALS_H