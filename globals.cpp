#include "globals.h"
#include <utility>

// Board size remains constant for a standard chessboard

// Tracks the current player's turn: true for White's turn, false for Black's turn
bool IS_WHITE_TURN = true;

// Initial positions of White's chess pieces (Rook, Knight, Bishop, Queen, King, etc.)
const char WHITE_PIECES[BOARD_SIZE] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};

// Initial positions of Black's chess pieces (Rook, Knight, Bishop, Queen, King, etc.)
const char BLACK_PIECES[BOARD_SIZE] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};

// Flag to track if a king is in check
bool IS_WHITE_IN_CHECK = false;

// Coordinates of the White and Black kings (updated as the game progresses)
std::pair<int, int> WHITE_KING_POSITION;
std::pair<int, int> BLACK_KING_POSITION;

// Position of the piece delivering a check to a king
std::pair<int, int> CHECKING_PIECE_POSITION;