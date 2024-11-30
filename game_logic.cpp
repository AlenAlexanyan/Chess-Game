#include <iostream>
#include <utility>
#include <vector>
#include "game_state.h"

// Function to check if it's White's turn
// Returns true if it is White's turn to play, false otherwise.
bool isWhitesMove()
{
    // IS_WHITE_TURN is a global variable defined in globals.h
    // It indicates whether it is currently White's turn (true) or Black's turn (false).
    return IS_WHITE_TURN;
}

// Function to check if the piece at the given position is a White piece
// Parameters:
// - board: 2D array representing the chessboard
// - Row: Row index of the piece to check (0-7)
// - Col: Column index of the piece to check (0-7)
// Returns true if the piece is White (uppercase), false otherwise.
bool isWhiteFigure(char board[BOARD_SIZE][BOARD_SIZE], int Row, int Col)
{
    // Check if the character at the specified position is an uppercase letter
    if (isupper(board[Row][Col])) {
        // Uncomment for debug output
        // std::cout << "You are right again!!! White" << std::endl;
        return true; // The piece at (Row, Col) is a White piece
    }
    return false; // The piece at (Row, Col) is not a White piece
}

// Function to check if the piece at the given position is a Black piece
// Parameters:
// - board: 2D array representing the chessboard
// - Row: Row index of the piece to check (0-7)
// - Col: Column index of the piece to check (0-7)
// Returns true if the piece is Black (lowercase), false otherwise.
bool isBlackFigure(char board[BOARD_SIZE][BOARD_SIZE], int Row, int Col)
{
    // Check if the character at the specified position is a lowercase letter
    if (islower(board[Row][Col])) {
        // Uncomment for debug output
        // std::cout << "You are right again!!! Black" << std::endl;
        return true; // The piece at (Row, Col) is a Black piece
    }
    return false; // The piece at (Row, Col) is not a Black piece
}

// Function to validate the move based on the piece's color and target position
// Parameters:
// - board: 2D array representing the chessboard
// - fromRow: Row index of the piece's current position (0-7)
// - fromCol: Column index of the piece's current position (0-7)
// - toRow: Row index of the target position (0-7)
// - toCol: Column index of the target position (0-7)
// Returns true if the move is valid, false otherwise.
bool isValidMove(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol)
{
    // Check if it's White's turn
    if (isWhitesMove())
    {
        // Validate conditions for White's move
        if (!isWhiteFigure(board, fromRow, fromCol) || // Source must be a White piece
            isWhiteFigure(board, toRow, toCol) ||    // Target must not be a White piece
            fromRow < 0 || fromRow >= BOARD_SIZE ||           // Source row must be within bounds
            fromCol < 0 || fromCol >= BOARD_SIZE ||           // Source column must be within bounds
            toRow < 0 || toRow >= BOARD_SIZE ||               // Target row must be within bounds
            toCol < 0 || toCol >= BOARD_SIZE)                  // Target column must be within bounds
        {
            return false; // Move is invalid for White
        }
    }
    else // If it's Black's turn
    {
        // Validate conditions for Black's move
        if (!isBlackFigure(board, fromRow, fromCol) || // Source must be a Black piece
            isBlackFigure(board, toRow, toCol) ||     // Target must not be a Black piece
            fromRow < 0 || fromRow >= BOARD_SIZE ||            // Source row must be within bounds
            fromCol < 0 || fromCol >= BOARD_SIZE ||            // Source column must be within bounds
            toRow < 0 || toRow >= BOARD_SIZE ||                // Target row must be within bounds
            toCol < 0 || toCol >= BOARD_SIZE)                  // Target column must be within bounds
        {
            return false; // Move is invalid for Black
        }
    }
    
    return true; // Move is valid
}

// Function to switch turns between Black and White
// This function toggles the turn indicator between White and Black.
void changeMove()
{
    IS_WHITE_TURN = !IS_WHITE_TURN; // Switch the turn indicator
}

// Function to check if a pawn can make a valid move
// Parameters:
// - board: 2D array representing the chessboard
// - fromRow: Row index of the pawn's current position (0-7)
// - fromCol: Column index of the pawn's current position (0-7)
// - toRow: Row index of the target position (0-7)
// - toCol: Column index of the target position (0-7)
// Returns true if the move is valid for a pawn, false otherwise.
bool isPossibleMoveForPawn(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol)
{  
    // White pawn movement logic
    if (isWhitesMove())
    {
        // Ensure the source piece is a White pawn
        if (!isWhiteFigure(board, fromRow, fromCol))
        {
            return false; // Invalid move if not a White piece
        }

        // Move one step forward or two steps from the starting row (6)
        if ((fromCol == toCol) && (board[toRow][toCol] == ' ') && 
            ((toRow - fromRow == -1) || (fromRow == 6 && abs(toRow - fromRow) == 2)))
        {
            return true; // Valid forward move
        }

        // Pawn capture (diagonal move to capture an enemy piece)
        if (abs(fromCol - toCol) == 1 && toRow - fromRow == -1 && isBlackFigure(board, toRow, toCol))
        {
            return true; // Valid capture move
        }

        return false; // Move is invalid for White pawn
    }
    // Black pawn movement logic
    else
    {
        // Ensure the source piece is a Black pawn
        if (isWhiteFigure(board, fromRow, fromCol))
        {
            return false; // Invalid move if not a Black piece
        }

        // Move one step forward or two steps from the starting row (1)
        if (fromCol == toCol && board[toRow][toCol] == ' ' && 
            ((abs(fromRow - toRow) == 1) || (fromRow == 1 && abs(fromRow - toRow) == 2)))
        {
            return true; // Valid forward move
        }

        // Pawn capture (diagonal move to capture an enemy piece)
        if (abs(fromCol - toCol) == 1 && fromRow - toRow == 1 && isWhiteFigure(board, toRow, toCol))
        {
            return true; // Valid capture move
        }

        return false; // Move is invalid for Black pawn
    }
}

// Function to check if a knight can make a valid move
// Parameters:
// - board: 2D array representing the chessboard
// - fromRow: Row index of the knight's current position (0-7)
// - fromCol: Column index of the knight's current position (0-7)
// - toRow: Row index of the target position (0-7)
// - toCol: Column index of the target position (0-7)
// Returns true if the move is valid for a knight, false otherwise.
bool isPossibleMoveForKnight(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol)
{    
    // First, validate that the move is within the rules of chess
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol))
    {
        return false; // Invalid move based on general movement rules
    }

    // A knight moves in an L-shape: two squares in one direction and one square perpendicular
    if (abs(toRow - fromRow) > 0 && abs(toCol - fromCol) > 0)
    {
        if (abs(toRow - fromRow) + abs(toCol - fromCol) == 3)
        {
            return true; // Valid knight move
        }
    }

    return false; // Move is invalid for knight
}

// Function to check if a bishop can make a valid move
// Parameters:
// - board: 2D array representing the chessboard
// - fromRow: Row index of the bishop's current position (0-7)
// - fromCol: Column index of the bishop's current position (0-7)
// - toRow: Row index of the target position (0-7)
// - toCol: Column index of the target position (0-7)
// Returns true if the move is valid for a bishop, false otherwise.
bool isPossibleMoveForBishop(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol)
{
    // First, validate that the move is within the rules of chess
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol))
    {
        return false; // Invalid move based on general movement rules
    }

    // Bishops move diagonally; check if the absolute differences in rows and columns are equal
    if (abs(fromRow - toRow) != abs(fromCol - toCol))
    {
        return false; // Move is not diagonal
    }

    // Determine the direction of movement for obstruction checking
    int direction;
    if ((toRow - fromRow) > 0 && (fromCol - toCol) > 0)
        direction = 1; // Moving down-right
    else if ((toRow - fromRow) > 0)
        direction = 2; // Moving down-left
    else if ((toCol - fromCol) < 0)
        direction = 3; // Moving up-left
    else
        direction = 4; // Moving up-right

    // Check for obstruction along the diagonal path based on direction
    if (direction == 1) // Down-right
    {
        for (int i = fromRow + 1, j = fromCol + 1; i < toRow && j < toCol; ++i, ++j)
        {
            if (board[i][j] != ' ') // If there's any piece in the way
                return false; // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
    else if (direction == 2) // Down-left
    {
        for (int i = fromRow + 1, j = fromCol - 1; i < toRow && j > toCol; ++i, --j)
        {
            if (board[i][j] != ' ') // If there's any piece in the way
                return false; // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
    else if (direction == 3) // Up-left
    {
        for (int i = fromRow - 1, j = fromCol - 1; i > toRow && j > toCol; --i, --j)
        {
            if (board[i][j] != ' ') // If there's any piece in the way
                return false; // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
    else // Up-right
    {
        for (int i = fromRow - 1, j = fromCol + 1; i > toRow && j < toCol; --i, ++j)
        {
            if (board[i][j] != ' ') // If there's any piece in the way
                return false; // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
}

// Function to check if a rook can make a valid move
// Parameters:
// - board: 2D array representing the chessboard
// - fromRow: Row index of the rook's current position (0-7)
// - fromCol: Column index of the rook's current position (0-7)
// - toRow: Row index of the target position (0-7)
// - toCol: Column index of the target position (0-7)
// Returns true if the move is valid for a rook, false otherwise.
bool isPossibleMoveForRook(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol)
{
    // First, validate that the move is within the rules of chess
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol))
    {
        // Uncomment for debug output
        // std::cout << "It is not a valid move" << std::endl;
        return false; // Invalid move based on general movement rules
    }

    int direction;

    // Determine movement direction based on whether the rook moves vertically or horizontally
    if ((toCol - fromCol) == 0) // Vertical movement
    {
        direction = (toRow - fromRow) > 0 ? 1 : 3; // Down or Up
    }
    else if ((toRow - fromRow) == 0) // Horizontal movement
    {
        direction = (toCol - fromCol) > 0 ? 4 : 2; // Right or Left
    }
    else 
    {
        return false; // Invalid move if not in a straight line
    }

    // Uncomment for debug output
    // std::cout << "Rook Direction: " << direction << std::endl;

    // Check for obstruction along the row or column based on direction
    if (direction == 1) // Down
    {
        for (int i = fromRow + 1; i < toRow; ++i)
        {
            if (board[i][fromCol] != ' ') // If there's any piece in the way
                return false; // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
    else if (direction == 2) // Left
    {
        for (int j = fromCol - 1; j > toCol; --j)
        {
            if (board[fromRow][j] != ' ') // If there's any piece in the way
                return false; // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
    else if (direction == 3) // Up
    {
        for (int i = fromRow - 1; i > toRow; --i)
        {
            if (board[i][fromCol] != ' ') // If there's any piece in the way
                return false; // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
    else // Right
    {
        for (int j = fromCol + 1; j < toCol; ++j)
        {
            if (board[fromRow][j] != ' ') // If there's any piece in the way
                return false; // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
}

// Function to check if a queen can make a valid move (combining bishop and rook moves)
// Parameters:
// - board: 2D array representing the chessboard
// - fromRow: Row index of the queen's current position (0-7)
// - fromCol: Column index of the queen's current position (0-7)
// - toRow: Row index of the target position (0-7)
// - toCol: Column index of the target position (0-7)
// Returns true if the move is valid for a queen, false otherwise.
bool isPossibleMoveForQueen(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol)
{   
    // Check if the move is valid as either a bishop or a rook move
    bool bishopMove = isPossibleMoveForBishop(board, fromRow, fromCol, toRow, toCol);
    bool rookMove = isPossibleMoveForRook(board, fromRow, fromCol, toRow, toCol);

    // Uncomment for debug output
    // std::cout << "Bishop Move: " << bishopMove << std::endl;
    // std::cout << "Rook Move: " << rookMove << std::endl;

    // A queen can move like either a bishop or a rook
    return (bishopMove || rookMove);
}

// Function to check if a king can make a valid move
// Parameters:
// - board: 2D array representing the chessboard
// - fromRow: Row index of the king's current position (0-7)
// - fromCol: Column index of the king's current position (0-7)
// - toRow: Row index of the target position (0-7)
// - toCol: Column index of the target position (0-7)
// Returns true if the move is valid for a king, false otherwise.
bool isPossibleMoveForKing(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol)
{
    // First, validate that the move is within the rules of chess
    if (!isValidMove(board, fromRow, fromCol, toRow, toCol))
    {
        return false; // Invalid move based on general movement rules
    }

    // The king can move one square in any direction
    if (abs(fromRow - toRow) <= 1 && abs(fromCol - toCol) <= 1)
    {
        return true; // Valid king move
    }
    
    return false; // Move is invalid for king
}

// Function to check if a piece can make a valid move based on its type
// Parameters:
// - board: 2D array representing the chessboard
// - fromRow: Row index of the piece's current position (0-7)
// - fromCol: Column index of the piece's current position (0-7)
// - toRow: Row index of the target position (0-7)
// - toCol: Column index of the target position (0-7)
// Returns true if the move is valid for the piece at (fromRow, fromCol), false otherwise.
bool isPossibleMove(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol) 
{
    switch (board[fromRow][fromCol]) {
        case 'p': case 'P': // Pawn
            return isPossibleMoveForPawn(board, fromRow, fromCol, toRow, toCol);
        case 'b': case 'B': // Bishop
            return isPossibleMoveForBishop(board, fromRow, fromCol, toRow, toCol);
        case 'n': case 'N': // Knight
            return isPossibleMoveForKnight(board, fromRow, fromCol, toRow, toCol);
        case 'q': case 'Q': // Queen
            return isPossibleMoveForQueen(board, fromRow, fromCol, toRow, toCol);
        case 'k': case 'K': // King
            return isPossibleMoveForKing(board, fromRow, fromCol, toRow, toCol);
        default: // Invalid piece
            return false;
    }
}

// Helper function to check if the figure matches the color (true for white, false for black)
// Parameters:
// - board: 2D array representing the chessboard
// - row: Row index of the piece to check (0-7)
// - col: Column index of the piece to check (0-7)
// - isWhite: Boolean indicating whether we are checking for a white piece
// Returns true if the piece matches the specified color, false otherwise.
bool isCorrectFigure(char board[BOARD_SIZE][BOARD_SIZE], int row, int col, bool isWhite) 
{
    char piece = board[row][col];
    // Check if the piece matches the color based on ASCII values
    bool val = (isWhite && piece >= 'A' && piece <= 'Z') || 
               (!isWhite && piece >= 'a' && piece <= 'z');

    // Uncomment for debug output
    // std::cout << "IsWhite: " << isWhite << std::endl;
    // std::cout << "Piece: " << piece << " Color Match: " << val << std::endl;

    return val; // Return whether the color matches
}

// Function to determine all possible fields between a piece and the king
// Parameters:
// - checkRow: Row index of the piece being checked (0-7)
// - checkCol: Column index of the piece being checked (0-7)
// - kingRow: Row index of the king's position (0-7)
// - kingCol: Column index of the king's position (0-7)
// Returns a vector of pairs representing the positions (row, column) that are between the piece and the king.
std::vector<std::pair<int, int>> allPossibleFields(int checkRow, int checkCol, int kingRow, int kingCol)
{
    int direction;

    // Determine the direction of movement: horizontal, vertical, or diagonal
    if (checkRow == kingRow) 
        direction = 1; // Horizontal movement
    else if (checkCol == kingCol) 
        direction = 2; // Vertical movement
    else 
        direction = 3; // Diagonal movement

    std::vector<std::pair<int, int>> positions; // Vector to store positions between the piece and the king

    // Uncomment for debug output
    // std::cout << "CheckRow: " << checkRow << ' ' << "CheckCol: " << checkCol << std::endl;
    // std::cout << "KingRow: " << kingRow << ' ' << "KingCol: " << kingCol << std::endl;

    // Handle horizontal movement
    if (direction == 1) {
        int startCol = std::min(checkCol, kingCol);
        int endCol = std::max(checkCol, kingCol);
        for (int col = startCol + 1; col < endCol; ++col) {
            positions.emplace_back(checkRow, col); // Add positions in between
        }
    }
    // Handle vertical movement
    else if (direction == 2) {
        int startRow = std::min(checkRow, kingRow);
        int endRow = std::max(checkRow, kingRow);
        for (int row = startRow + 1; row < endRow; ++row) {
            positions.emplace_back(row, checkCol); // Add positions in between
        }
    }
    // Handle diagonal movement
    else if (direction == 3) {
        int rowStep = (kingRow > checkRow) ? 1 : -1; // Determine step direction for rows
        int colStep = (kingCol > checkCol) ? 1 : -1; // Determine step direction for columns
        int row = checkRow + rowStep;
        int col = checkCol + colStep;
        
        // Loop until reaching the king's position
        while (row != kingRow && col != kingCol) {
            positions.emplace_back(row, col); // Add diagonal positions in between
            row += rowStep; // Move to next row
            col += colStep; // Move to next column
        }
    }

    return positions; // Return all possible fields between the piece and the king
}

// Function to check if any piece is attacking the king (check condition)
// Parameters:
// - board: 2D array representing the chessboard
// Returns true if the king is in check, false otherwise.
bool isCheck(char board[BOARD_SIZE][BOARD_SIZE])
{
    std::pair<int, int> WhiteKingCoordinates;
    std::pair<int, int> BlackKingCoordinates;

    // Identify the positions of the kings
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        for (size_t j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 'k') { // Black king
                BlackKingCoordinates.first = i;
                BlackKingCoordinates.second = j;
            }
            if (board[i][j] == 'K') { // White king
                WhiteKingCoordinates.first = i;
                WhiteKingCoordinates.second = j;
            }
        }
    }

    // Store the positions of the kings in global variables
    WHITE_KING_POSITION = WhiteKingCoordinates;
    BLACK_KING_POSITION = BlackKingCoordinates;

    // Check for attacks from different pieces on the board
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            char piece = board[i][j]; // Current piece being checked
            std::pair<int, int> targetKing = (piece >= 'a' && piece <= 'z') ? WHITE_KING_POSITION : BLACK_KING_POSITION;

            bool isCheck = false; // Flag to indicate if the king is in check

            // Determine if the current piece can attack the target king
            switch (piece) {
                case 'q': case 'Q': // Queen
                    isCheck = isPossibleMoveForQueen(board, i, j, targetKing.first, targetKing.second);
                    break;
                case 'n': case 'N': // Knight
                    isCheck = isPossibleMoveForKnight(board, i, j, targetKing.first, targetKing.second);
                    break;
                case 'r': case 'R': // Rook
                    isCheck = isPossibleMoveForRook(board, i, j, targetKing.first, targetKing.second);
                    break;
                case 'b': case 'B': // Bishop
                    isCheck = isPossibleMoveForBishop(board, i, j, targetKing.first, targetKing.second);
                    break;
                case 'p': case 'P': // Pawn
                    isCheck = isPossibleMoveForPawn(board, i, j, targetKing.first, targetKing.second);
                    break;
            }

            // If a piece can attack the king
            if (isCheck) {
                CHECKING_PIECE_POSITION = {i, j}; // Store the position of the attacking piece
                IS_WHITE_IN_CHECK = (targetKing == WHITE_KING_POSITION);
                IS_BLACK_IN_CHECK = (targetKing == BLACK_KING_POSITION); // Update check status based on which king is targeted

                std::cout << "It is a check";
                changeMove(); // Change turn after detecting a check
                return true; // Return true indicating that the king is in check
            }
        }
    }

    return false; // Return false indicating that the king is not in check
}

// Function to check if the current player is in checkmate
// Parameters:
// - board: 2D array representing the chessboard
// Returns true if the player is in checkmate, false otherwise.
bool isCheckMate(char board[BOARD_SIZE][BOARD_SIZE])
{
    // Determine which king is in check
    std::pair<int, int> checkKing = (IS_WHITE_IN_CHECK) ? WHITE_KING_POSITION : BLACK_KING_POSITION;

    // Get the positions of fields that could block the check
    std::vector<std::pair<int, int>> closingFields = allPossibleFields(CHECKING_PIECE_POSITION.first, CHECKING_PIECE_POSITION.second, checkKing.first, checkKing.second);
    closingFields.emplace_back(CHECKING_PIECE_POSITION.first, CHECKING_PIECE_POSITION.second); // Include the position of the checking piece

    // Check if the king can escape from check by moving to adjacent squares
    for (int row = checkKing.first - 1; row <= checkKing.first + 1; ++row) {
        for (int col = checkKing.second - 1; col <= checkKing.second + 1; ++col) {
            // Ensure we stay within bounds and not stay in the same position
            if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && (row != checkKing.first || col != checkKing.second)) {
                bool canEscape = true; // Assume escape is possible until proven otherwise

                // Check all pieces of the opponent to see if they can attack this escape square
                for (int i = 0; i < BOARD_SIZE && canEscape; ++i) {
                    for (int j = 0; j < BOARD_SIZE && canEscape; ++j) {
                        // If there's an opponent's piece that can attack this square
                        if (isCorrectFigure(board, i, j, !IS_WHITE_IN_CHECK) && !isPossibleMove(board, i, j, row, col)) {
                            canEscape = false; // This square is not safe for escape
                        }
                    }
                }

                // If there's a valid escape move for the king
                if (canEscape) {
                    return false; // King can escape from check
                }
            }
        }
    }

    // Try to block the check by moving pieces
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            // Check if the piece belongs to the current player
            if (isCorrectFigure(board, row, col, IS_WHITE_IN_CHECK)) {
                for (auto &field : closingFields) {
                    // Check if this piece can move to a position that blocks the check
                    if (board[row][col] != 'k' && board[row][col] != 'K' && isPossibleMove(board, row, col, field.first, field.second)) {
                        changeMove(); // Change turn after finding a valid move
                        return false; // Found a valid move to block the check
                    }
                }
            }
        }
    }

    return true; // No valid moves to escape or block; it's checkmate
}

void printPieces(const std::map<std::string, std::pair<int, int>>& pieces, const std::string& player) {
    std::cout << "Pieces for " << player << ":\n";
    for (const auto& piece : pieces) {
        std::cout << piece.first << " at (" 
                  << piece.second.first << ", " 
                  << piece.second.second << ")\n";
    }
    std::cout << std::endl;
}


//TODO Does not work properly
bool isStaleMate(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Iterate through all pieces of the current player
    auto& playerPieces = !isWhitesMove ? ALL_WHITE_PIECES : ALL_BLACK_PIECES;

    printPieces(playerPieces, "white");

    for (const auto& piece : playerPieces) {
        int currentRow = piece.second.first;
        int currentCol = piece.second.second;

        // Iterate over all possible moves for the piece
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                if (isPossibleMove(board, currentRow, currentCol, row, col)) {
                    return false;
                }
            }
        }
    }

    // If no legal moves exist, check if the king is in check
    return true;
}

// Function to check if the game is a draw
bool isDraw(char board[BOARD_SIZE][BOARD_SIZE]) {
    // A draw is declared if there is exactly 1 white piece and 1 black piece left on the board.
    // This is an oversimplified condition for a draw, as in actual chess, the draw condition involves 
     // other complex scenarios like stalemate, insufficient material, or a draw by repetition?????.
    bool size = (ALL_WHITE_PIECES.size() == 1 && ALL_BLACK_PIECES.size() == 1);
    bool stalemate = isStaleMate(board);

    std::cout << "size: " << size << std::endl;
    std::cout << "StaleMae: " << stalemate << std::endl;

    return (ALL_WHITE_PIECES.size() == 1 && ALL_BLACK_PIECES.size() == 1) || isStaleMate(board);
}

// Function to create a copy of the chessboard.
// Parameters:
// - original: 2D array representing the original chessboard.
// - copy: 2D array where the copied board will be stored.
// Copies the content of the original chessboard into the provided copy array.
void copyBoard(const char original[BOARD_SIZE][BOARD_SIZE], char copy[BOARD_SIZE][BOARD_SIZE]) {
    // Iterate through each cell in the board.
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            // Copy the content of each cell from the original board to the copy.
            copy[i][j] = original[i][j];
        }
    }
}

// Function to check if a move keeps the king safe from being in check.
// Parameters:
// - board: 2D array representing the chessboard.
// - fromRow: Row index of the piece to move (0-based).
// - fromCol: Column index of the piece to move (0-based).
// - toRow: Row index of the target position (0-based).
// - toCol: Column index of the target position (0-based).
// Returns true if the move keeps the king safe, false otherwise.
bool doesMoveKeepKingSafe(char board[BOARD_SIZE][BOARD_SIZE], int fromRow, int fromCol, int toRow, int toCol) {

    // Create a copy of the board to simulate the move.
    char copy[BOARD_SIZE][BOARD_SIZE];
    copyBoard(board, copy);

    // Simulate the move by updating the copied board.
    copy[toRow][toCol] = copy[fromRow][fromCol];
    copy[fromRow][fromCol] = ' ';

    // Check if the king is in check on the simulated board.
    return !isCheck(copy);
}