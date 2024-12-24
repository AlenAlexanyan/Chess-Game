#pragma once

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
#include <map>
#include <string>

class Game
{
private:
    // Constants
    static const unsigned short int BOARD_SIZE = 8; // Size of the chessboard
    static char BOARD[BOARD_SIZE][BOARD_SIZE];
    // Game state
    bool TURN = true;               // Current turn: true for White, false for Black
    bool IS_WHITE_IN_CHECK = false; // Is White in check?
    bool IS_BLACK_IN_CHECK = false; // Is Black in check?

    // King positions
    std::pair<int, int> WHITE_KING_POSITION = {3, 7}; // White King's position
    std::pair<int, int> BLACK_KING_POSITION = {3, 0}; // Black King's position

    // Position of the checking piece (if any)
    std::pair<int, int> CHECKING_PIECE_POSITION;

    // Initial positions for pieces
    const char WHITE_PIECES[BOARD_SIZE] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    const char BLACK_PIECES[BOARD_SIZE] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};

    // Define the initial positions of the rooks and kings for castling checks
    const std::pair<int, int> WHITE_KING_START = {7, 4};
    const std::pair<int, int> BLACK_KING_START = {0, 4};
    const std::pair<int, int> WHITE_ROOK_KINGSIDE_START = {7, 7};
    const std::pair<int, int> WHITE_ROOK_QUEENSIDE_START = {7, 0};
    const std::pair<int, int> BLACK_ROOK_KINGSIDE_START = {0, 7};
    const std::pair<int, int> BLACK_ROOK_QUEENSIDE_START = {0, 0};

    // Track if the rooks and kings have moved
    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookKingSideMoved = false;
    bool whiteRookQueenSideMoved = false;
    bool blackRookKingSideMoved = false;
    bool blackRookQueenSideMoved = false;

    // The last move
    std::string lastMove;

    // Figures current positions for White pieces
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
        {"Nb1", {7, 1}}, // White knight at a1 (row 7, column 1)
        {"Ng1", {7, 6}}, // White knight at h1 (row 7, column 6)
        {"Bc1", {7, 2}}, // White bishop at a1 (row 7, column 2)
        {"Bf1", {7, 5}}, // White bishop at h1 (row 7, column 5)
        {"Qd1", {7, 3}}, // White queen at d1 (row 7, column 3)
        {"Ke1", {7, 4}}  // White king at e1 (row 7, column 4)
    };

    // Figures current positions for Black pieces
    std::map<std::string, std::pair<int, int>> ALL_BLACK_PIECES = {
        {"pa7", {1, 0}}, // Black pawn at a7 (row 1, column 0)
        {"pb7", {1, 1}}, // Black pawn at b7 (row 1, column 1)
        {"pc7", {1, 2}}, // Black pawn at c7 (row 1, column 2)
        {"pd7", {1, 3}}, // Black pawn at d7 (row 1, column 3)
        {"pe7", {1, 4}}, // Black pawn at e7 (row 1, column 4)
        {"pf7", {1, 5}}, // Black pawn at f7 (row 1, column 5)
        {"pg7", {1, 6}}, // Black pawn at g7 (row 1, column 6)
        {"ph7", {1, 7}}, // Black pawn at h7 (row 1, column 7)
        {"ra8", {0, 0}}, // Black rook at a8 (row 0, column 0)
        {"rh8", {0, 7}}, // Black rook at h8 (row 0, column 7)
        {"nb8", {0, 1}}, // Black knight at a8 (row 0, column 1)
        {"ng8", {0, 6}}, // Black knight at h8 (row 0, column 6)
        {"bc8", {0, 2}}, // Black bishop at a8 (row 0, column 2)
        {"bf8", {0, 5}}, // Black bishop at h8 (row 0, column 5)
        {"qd8", {0, 3}}, // Black queen at d8 (row 0, column 3)
        {"ke8", {0, 4}}  // Black king at e8 (row 0, column 4)
    };

    // Initialize the chessboard with default positions
    void initializeBoard();

    // Check if it is White's turn
    bool isWhitesMove() const { return TURN; }

    // Movement Validation
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);          // General move validation
    bool doesMoveKeepKingSafe(int fromRow, int fromCol, int toRow, int toCol); // Ensure the king is safe after a move

    // Piece-specific Move Validation
    bool isPossibleMoveForPawn(int fromRow, int fromCol, int toRow, int toCol);
    bool isPossibleMoveForKnight(int fromRow, int fromCol, int toRow, int toCol);
    bool isPossibleMoveForBishop(int fromRow, int fromCol, int toRow, int toCol);
    bool isPossibleMoveForRook(int fromRow, int fromCol, int toRow, int toCol);
    bool isPossibleMoveForQueen(int fromRow, int fromCol, int toRow, int toCol);
    bool isPossibleMoveForKing(int fromRow, int fromCol, int toRow, int toCol);
    bool isPossibleMove(int fromRow, int fromCol, int toRow, int toCol); // Check move validity based on piece type

    // Piece Identification
    bool isWhiteFigure(int row, int col) const;                 // Check if a piece is White
    bool isBlackFigure(int row, int col) const;                 // Check if a piece is Black
    bool isCorrectFigure(int row, int col, bool isWhite) const; // Validate the piece color

    // Movement Execution
    void movePiece(int fromRow, int fromCol, int toRow, int toCol, char piece);
    void undoMove(); // Move a piece

    // Utility Functions
    std::vector<std::pair<int, int>> allPossibleFields(int checkRow, int checkCol, int kingRow, int kingCol); // Fields between a piece and the king
    void printPieces(const std::map<std::string, std::pair<int, int>> &pieces, const std::string &player);    // Print all pieces for a player

    void updateCastlingRights(int fromRow, int fromCol, int toRow, int toCol);
    bool canCastleKingside(bool isWhite) const;
    bool canCastleQueenside(bool isWhite) const;

public:
    // Constructor and Destructor
    Game();
    ~Game();

    // Getters
    bool getTurn() const { return TURN; }
    bool getIsWhiteInCheck() const { return IS_WHITE_IN_CHECK; }
    bool getIsBlackInCheck() const { return IS_BLACK_IN_CHECK; }
    std::pair<int, int> getWhiteKingPosition() const { return WHITE_KING_POSITION; }
    std::pair<int, int> getBlackKingPosition() const { return BLACK_KING_POSITION; }
    std::pair<int, int> getCheckingPiecePosition() const { return CHECKING_PIECE_POSITION; }
    const std::map<std::string, std::pair<int, int>> &getAllWhitePieces() const { return ALL_WHITE_PIECES; }
    const std::map<std::string, std::pair<int, int>> &getAllBlackPieces() const { return ALL_BLACK_PIECES; }
    unsigned short int getBoardSize() const { return BOARD_SIZE; }
    const char *getWhitePieces() const { return WHITE_PIECES; }
    const char *getBlackPieces() const { return BLACK_PIECES; }

    // Setters
    void setTurn(bool newTurn) { TURN = newTurn; }
    void setIsWhiteInCheck(bool isInCheck) { IS_WHITE_IN_CHECK = isInCheck; }
    void setIsBlackInCheck(bool isInCheck) { IS_BLACK_IN_CHECK = isInCheck; }
    void setWhiteKingPosition(const std::pair<int, int> &position) { WHITE_KING_POSITION = position; }
    void setBlackKingPosition(const std::pair<int, int> &position) { BLACK_KING_POSITION = position; }
    void setCheckingPiecePosition(const std::pair<int, int> &position) { CHECKING_PIECE_POSITION = position; }
    void setAllWhitePieces(const std::map<std::string, std::pair<int, int>> &whitePieces) { ALL_WHITE_PIECES = whitePieces; }
    void setAllBlackPieces(const std::map<std::string, std::pair<int, int>> &blackPieces) { ALL_BLACK_PIECES = blackPieces; }

    // Display the chessboard
    void displayBoard() const;

    // Validate and execute a move
    bool checkMovePiece(std::string from, std::string to);
    // Turn Management
    inline void changeMove() { TURN = !TURN; } // Switch turns between players

    // Game State Checkers
    bool isCheck(char tempBoard[BOARD_SIZE][BOARD_SIZE] = BOARD); // Check if a player is in check
    bool isCheckMate();                                           // Check if a player is in checkmate
    bool isStaleMate();                                           // Check if the game is in stalemate
    bool isDraw();                                                // Check if the game is a draw
};

#endif