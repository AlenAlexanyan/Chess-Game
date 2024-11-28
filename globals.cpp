#include "globals.h"
#include <utility>

// Tracks the current player's turn: false for Black's move, true for White's move
bool black_or_white = true;

// Initial positions of White's chess pieces (Rook, Knight, Bishop, Queen, King, etc.)
const char whitePieces[] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};

// Initial positions of Black's chess pieces (Rook, Knight, Bishop, Queen, King, etc.)
const char blackPieces[] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};

bool whiteCheck = false;

bool blackCheck = false;

std::pair<int, int> WhiteKing;
std::pair<int, int> BlackKing;

std::pair<int, int> CheckKing;
