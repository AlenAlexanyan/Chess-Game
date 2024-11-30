#include "game_state.h"
#include <utility>
#include <map>
#include <string>

// Board size remains constant for a standard chessboard

// Tracks the current player's turn: true for White's turn, false for Black's turn
bool IS_WHITE_TURN = true;

// Initial positions of White's chess pieces (Rook, Knight, Bishop, Queen, King, etc.)
const char WHITE_PIECES[BOARD_SIZE] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};

// Initial positions of Black's chess pieces (Rook, Knight, Bishop, Queen, King, etc.)
const char BLACK_PIECES[BOARD_SIZE] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};

// Flag to track if a king is in check
bool IS_WHITE_IN_CHECK = false;
bool IS_BLACK_IN_CHECK = false;

// Coordinates of the White and Black kings (updated as the game progresses)
std::pair<int, int> WHITE_KING_POSITION;
std::pair<int, int> BLACK_KING_POSITION;

// Position of the piece delivering a check to a king
std::pair<int, int> CHECKING_PIECE_POSITION;

// Figures current positions
std::map<std::string, std::pair<int, int>> ALL_WHITE_PIECES = {
    {"Pa2", {6, 0}}, // White pawn at a2 (row 6, column 0)
    {"Pb2", {6, 1}}, // White pawn at b2 (row 6, column 1)
    {"Pc2", {6, 2}}, // White pawn at c2 (row 6, column 2)
    {"Pd2", {6, 3}}, // White pawn at d2 (row 6, column 3)
    {"Pe2", {6, 4}}, // White pawn at e2 (row 6, column 4)
    {"Pf2", {6, 5}}, // White pawn at f2 (row 6, column 5)
    {"Pg2", {6, 6}}, // White pawn at g2 (row 6, column 6)
    {"Ph2", {6, 7}}, // White pawn at h2 (row 6, column 7)
    {"Ra1", {7, 0}}, // White rook at a1 (row 7, column 0)
    {"Rh1", {7, 7}}, // White rook at h1 (row 7, column 7)
    {"Na1", {7, 1}}, // White knight at a1 (row 7, column 1)
    {"Nh1", {7, 6}}, // White knight at h1 (row 7, column 6)
    {"Ba1", {7, 2}}, // White bishop at a1 (row 7, column 2)
    {"Bh1", {7, 5}}, // White bishop at h1 (row 7, column 5)
    {"Qd1", {7, 3}}, // White queen at d1 (row 7, column 3)
    {"Ke1", {7, 4}}  // White king at e1 (row 7, column 4)
};

std::map<std::string, std::pair<int, int>> ALL_BLACK_PIECES = {
    {"Pa7", {1, 0}}, // Black pawn at a7 (row 1, column 0)
    {"Pb7", {1, 1}}, // Black pawn at b7 (row 1, column 1)
    {"Pc7", {1, 2}}, // Black pawn at c7 (row 1, column 2)
    {"Pd7", {1, 3}}, // Black pawn at d7 (row 1, column 3)
    {"Pe7", {1, 4}}, // Black pawn at e7 (row 1, column 4)
    {"Pf7", {1, 5}}, // Black pawn at f7 (row 1, column 5)
    {"Pg7", {1, 6}}, // Black pawn at g7 (row 1, column 6)
    {"Ph7", {1, 7}}, // Black pawn at h7 (row 1, column 7)
    {"Ra8", {0, 0}}, // Black rook at a8 (row 0, column 0)
    {"Rh8", {0, 7}}, // Black rook at h8 (row 0, column 7)
    {"Na8", {0, 1}}, // Black knight at a8 (row 0, column 1)
    {"Nh8", {0, 6}}, // Black knight at h8 (row 0, column 6)
    {"Ba8", {0, 2}}, // Black bishop at a8 (row 0, column 2)
    {"Bh8", {0, 5}}, // Black bishop at h8 (row 0, column 5)
    {"Qd8", {0, 3}}, // Black queen at d8 (row 0, column 3)
    {"Ke8", {0, 4}}  // Black king at e8 (row 0, column 4)
};