#include <iostream>
#include <utility>
#include <vector>
#include <cstring>
#include <map>
#include <string>
#include "Game.h"

void Game::updateCastlingRights(int fromRow, int fromCol, int toRow, int toCol) {
    // Update the castling rights based on the piece's movement
    if (fromRow == WHITE_KING_START.first && fromCol == WHITE_KING_START.second) {
        whiteKingMoved = true;
    } else if (fromRow == BLACK_KING_START.first && fromCol == BLACK_KING_START.second) {
        blackKingMoved = true;
    } else if (fromRow == WHITE_ROOK_KINGSIDE_START.first && fromCol == WHITE_ROOK_KINGSIDE_START.second) {
        whiteRookKingSideMoved = true;
    } else if (fromRow == WHITE_ROOK_QUEENSIDE_START.first && fromCol == WHITE_ROOK_QUEENSIDE_START.second) {
        whiteRookQueenSideMoved = true;
    } else if (fromRow == BLACK_ROOK_KINGSIDE_START.first && fromCol == BLACK_ROOK_KINGSIDE_START.second) {
        blackRookKingSideMoved = true;
    } else if (fromRow == BLACK_ROOK_QUEENSIDE_START.first && fromCol == BLACK_ROOK_QUEENSIDE_START.second) {
        blackRookQueenSideMoved = true;
    }
}

bool Game::canCastleKingside(bool isWhite) const {
    if (isWhite) {
        if (whiteKingMoved) {
            std::cout << "White king has already moved. Castling is not allowed.\n";
        }
        if (whiteRookKingSideMoved) {
            std::cout << "White kingside rook has already moved. Castling is not allowed.\n";
        }
        return !whiteKingMoved && !whiteRookKingSideMoved;
    } else {
        if (blackKingMoved) {
            std::cout << "Black king has already moved. Castling is not allowed.\n";
        }
        else if (blackRookKingSideMoved) {
            std::cout << "Black kingside rook has already moved. Castling is not allowed.\n";
        }
        return !blackKingMoved && !blackRookKingSideMoved;
    }
}

bool Game::canCastleQueenside(bool isWhite) const {
    if (isWhite) {
        if (whiteKingMoved) {
            std::cout << "White king has already moved. Castling is not allowed.\n";
        }
        if (whiteRookQueenSideMoved) {
            std::cout << "White Queenside rook has already moved. Castling is not allowed.\n";
        }
        return !whiteKingMoved && !whiteRookQueenSideMoved;
    } else {
        if (blackKingMoved) {
            std::cout << "Black king has already moved. Castling is not allowed.\n";
        }
        if (blackRookQueenSideMoved) {
            std::cout << "Black Queenside rook has already moved. Castling is not allowed.\n";
        }

        std:: cout << "Black King Moved: " << blackKingMoved << " Black Rook Moved: " << blackRookQueenSideMoved << std::endl;
        return !blackKingMoved && !blackRookQueenSideMoved;
    }
}
// Define the static member variable 'BOARD'
char Game::BOARD[Game::BOARD_SIZE][Game::BOARD_SIZE] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, // Black's back row
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, // Black's pawns
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // Empty rows
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, // White's pawns
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}  // White's back row
};

Game::Game()
{
    initializeBoard();
}

Game::~Game()
{
}

void Game::initializeBoard()
{
    // Set all board squares to empty
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            BOARD[i][j] = ' '; // Empty square
        }
    }

    // Place pawns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        BOARD[1][i] = 'p'; // Black pawns
        BOARD[6][i] = 'P'; // White pawns
    }

    // Place other pieces
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        BOARD[0][i] = BLACK_PIECES[i]; // Black pieces
        BOARD[7][i] = WHITE_PIECES[i]; // White pieces
    }
}

void Game::displayBoard() const
{
    std::cout << "\n"; // Print a blank line for better spacing

    // Loop through each row of the board
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        std::cout << 8 - i << "  "; // Print row numbers (8 to 1)

        for (int j = 0; j < BOARD_SIZE; j++)
        {
            std::cout << BOARD[i][j] << ' '; // Display the piece or empty square
        }
        std::cout << '\n'; // Move to the next row
    }

    // Print column labels
    std::cout << std::endl
              << "   a b c d e f g h\n";
}

bool Game::checkMovePiece(std::string from, std::string to)
{
    if (from == "0")
    {
        // std::cout << "I am hereeeeeeeeeeeeeeeee" << std::endl;

        if (isWhitesMove()) {
            if (canCastleKingside(true) && isPossibleMoveForRook(7, 7, 7, 5))
            {
                movePiece(7, 7, 7, 5, '\0');
                movePiece(7, 4, 7, 6, '\0');
                return true;
            }
        }
        else {
            if (canCastleKingside(false) && isPossibleMoveForRook(0, 7, 0, 5))
            {
                // std::cout << "I am here" << std::endl;
                movePiece(0, 7, 0, 5, '\0');
                movePiece(0, 4, 0, 6, '\0');
                return true;
            }
        }
        return false;
    }
    else if (from == "0-0") {
        if (isWhitesMove()) {
            if (canCastleQueenside(true) && isPossibleMoveForRook(7, 0, 7, 3))
            {
                movePiece(7, 0, 7, 3, '\0');
                movePiece(7, 4, 7, 2, '\0');
                return true;
            }
        }
        else {
            if (canCastleQueenside(false) && isPossibleMoveForRook(0, 0, 0, 3))
            {
                movePiece(0, 0, 0, 3, '\0');
                movePiece(0, 4, 0, 2, '\0');
                return true;
            }
        }
        return false;
    }

    // Convert chess notation (e.g., "e2") to array indices.
    int fromRow = BOARD_SIZE - (from[1] - '0'); // Convert row to array index
    int fromCol = from[0] - 'a';                // Convert column to array index
    int toRow = BOARD_SIZE - (to[1] - '0');     // Convert row to array index
    int toCol = to[0] - 'a';                    // Convert column to array index
    
    // Debug: Print the computed indices.
    std::cout << "From: (" << fromRow << ", " << fromCol << ") "
              << "To: (" << toRow << ", " << toCol << ")\n";

    bool isvalidMove = isValidMove(fromRow, fromCol, toRow, toCol);
    bool kingSafe = doesMoveKeepKingSafe(fromRow, fromCol, toRow, toCol);

    // std::cout << "Valid Move: " << isvalidMove << std::endl;
    // std::cout << "KingSafe: " << kingSafe << std::endl;

    // Ensure the move is within the chessboard's bounds.
    if (!isvalidMove || !kingSafe)
    {
        std::cout << "Invalid move!\n";
        return false;
    }

    char PieceToBe = '\0';

    // Validate the move based on the piece type.
    char piece = BOARD[fromRow][fromCol];
    // std::cout << piece << std::endl;
    bool validMove = false;

    switch (piece)
    {
    case 'p':
    case 'P': // Pawn
        validMove = isPossibleMoveForPawn(fromRow, fromCol, toRow, toCol);
        // std::cout << "Valid Move: " << validMove << std::endl;
        if (validMove && (toRow == 7 || toRow == 0))
        {
            std::cout << "Write the Figure to Be: ";
            std::cin >> PieceToBe;
            std::cout << std::endl;
        }
        break;
    case 'r':
    case 'R': // Rook
        validMove = isPossibleMoveForRook(fromRow, fromCol, toRow, toCol);
        break;
    case 'n':
    case 'N': // Knight
        validMove = isPossibleMoveForKnight(fromRow, fromCol, toRow, toCol);
        break;
    case 'b':
    case 'B': // Bishop
        validMove = isPossibleMoveForBishop(fromRow, fromCol, toRow, toCol);
        break;
    case 'q':
    case 'Q': // Queen
        validMove = isPossibleMoveForQueen(fromRow, fromCol, toRow, toCol);
        break;
    case 'k':
    case 'K': // King
        validMove = isPossibleMoveForKing(fromRow, fromCol, toRow, toCol);
        break;
    default:
        std::cout << "No valid piece at this position. Try again.\n";
        return false;
    }

    // If the move is valid, execute it.
    if (validMove)
    {
        movePiece(fromRow, fromCol, toRow, toCol, PieceToBe);
        return true;
    }

    std::cout << "Invalid move for the selected piece.\n";
    return false;
}

void Game::printPieces(const std::map<std::string, std::pair<int, int>> &pieces, const std::string &player)
{
    std::cout << "Pieces for " << player << ":\n";
    for (const auto &piece : pieces)
    {
        std::cout << piece.first << " at ("
                  << piece.second.first << ", "
                  << piece.second.second << ")\n";
    }
    std::cout << std::endl;
}

bool Game::isCheck(char tempBoard[BOARD_SIZE][BOARD_SIZE])
{
    // Identify the positions of the kings
    for (size_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (size_t j = 0; j < BOARD_SIZE; ++j)
        {
            if (BOARD[i][j] == 'k')
            { // Black king
                BLACK_KING_POSITION.first = i;
                BLACK_KING_POSITION.second = j;
            }
            if (BOARD[i][j] == 'K')
            { // White king
                WHITE_KING_POSITION.first = i;
                WHITE_KING_POSITION.second = j;
            }
        }
    }

    // Check for attacks from different pieces on the board
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            char piece = BOARD[i][j]; // Current piece being checked
            std::pair<int, int> targetKing = (piece >= 'a' && piece <= 'z') ? WHITE_KING_POSITION : BLACK_KING_POSITION;

            bool isCheck = false; // Flag to indicate if the king is in check

            // Determine if the current piece can attack the target king
            switch (piece)
            {
            case 'q':
            case 'Q': // Queen
                isCheck = isPossibleMoveForQueen(i, j, targetKing.first, targetKing.second);
                break;
            case 'n':
            case 'N': // Knight
                isCheck = isPossibleMoveForKnight(i, j, targetKing.first, targetKing.second);
                break;
            case 'r':
            case 'R': // Rook
                isCheck = isPossibleMoveForRook(i, j, targetKing.first, targetKing.second);
                break;
            case 'b':
            case 'B': // Bishop
                isCheck = isPossibleMoveForBishop(i, j, targetKing.first, targetKing.second);
                break;
            case 'p':
            case 'P': // Pawn
                isCheck = isPossibleMoveForPawn(i, j, targetKing.first, targetKing.second);
                break;
            }

            // If a piece can attack the king
            if (isCheck)
            {
                CHECKING_PIECE_POSITION = {i, j}; // Store the position of the attacking piece
                IS_WHITE_IN_CHECK = (targetKing == WHITE_KING_POSITION);
                IS_BLACK_IN_CHECK = (targetKing == BLACK_KING_POSITION); // Update check status based on which king is targeted

                std::cout << "It is a check" << std::endl;
                changeMove(); // Change turn after detecting a check
                return true;  // Return true indicating that the king is in check
            }
        }
    }

    return false; // Return false indicating that the king is not in check
}

bool Game::isCheckMate()
{
    // Determine which king is in check
    std::pair<int, int> checkKing = (IS_WHITE_IN_CHECK) ? WHITE_KING_POSITION : BLACK_KING_POSITION;

    // Get the positions of fields that could block the check
    std::vector<std::pair<int, int>> closingFields = allPossibleFields(CHECKING_PIECE_POSITION.first, CHECKING_PIECE_POSITION.second, checkKing.first, checkKing.second);
    closingFields.emplace_back(CHECKING_PIECE_POSITION.first, CHECKING_PIECE_POSITION.second); // Include the position of the checking piece

    // Check if the king can escape from check by moving to adjacent squares
    for (int row = checkKing.first - 1; row <= checkKing.first + 1; ++row)
    {
        for (int col = checkKing.second - 1; col <= checkKing.second + 1; ++col)
        {
            // Ensure we stay within bounds and not stay in the same position
            if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && (row != checkKing.first || col != checkKing.second))
            {
                bool canEscape = true; // Assume escape is possible until proven otherwise

                // Check all pieces of the opponent to see if they can attack this escape square
                for (int i = 0; i < BOARD_SIZE && canEscape; ++i)
                {
                    for (int j = 0; j < BOARD_SIZE && canEscape; ++j)
                    {
                        // If there's an opponent's piece that can attack this square
                        if (isCorrectFigure(i, j, !IS_WHITE_IN_CHECK) && !isPossibleMove(i, j, row, col))
                        {
                            canEscape = false; // This square is not safe for escape
                        }
                    }
                }

                // If there's a valid escape move for the king
                if (canEscape)
                {
                    return false; // King can escape from check
                }
            }
        }
    }

    // Try to block the check by moving pieces
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            // Check if the piece belongs to the current player
            if (isCorrectFigure(row, col, IS_WHITE_IN_CHECK))
            {
                for (auto &field : closingFields)
                {
                    // Check if this piece can move to a position that blocks the check
                    if (BOARD[row][col] != 'k' && BOARD[row][col] != 'K' && isPossibleMove(row, col, field.first, field.second))
                    {
                        changeMove(); // Change turn after finding a valid move
                        return false; // Found a valid move to block the check
                    }
                }
            }
        }
    }

    return true; // No valid moves to escape or block; it's checkmate
}

bool Game::isStaleMate()
{
    // Iterate through all pieces of the current player
    auto &playerPieces = isWhitesMove() ? ALL_WHITE_PIECES : ALL_BLACK_PIECES;
    std::string player = isWhitesMove() ? "White" : "Black";

    // std::cout << "Move: " << isWhitesMove() << std::endl;

    printPieces(playerPieces, player);

    for (const auto &piece : playerPieces)
    {
        int currentRow = piece.second.first;
        int currentCol = piece.second.second;

        // Iterate over all possible moves for the piece
        for (int row = 0; row < BOARD_SIZE; ++row)
        {
            for (int col = 0; col < BOARD_SIZE; ++col)
            {
                if (isPossibleMove(currentRow, currentCol, row, col))
                {
                    return false;
                }
            }
        }
    }

    // If no legal moves exist, check if the king is in check
    return true;
}

bool Game::doesMoveKeepKingSafe(int fromRow, int fromCol, int toRow, int toCol)
{
    // Create a copy of the board to simulate the move.
    char copy[BOARD_SIZE][BOARD_SIZE];
    std::memcpy(copy, BOARD, sizeof(char) * BOARD_SIZE * BOARD_SIZE);

    // Simulate the move by updating the copied board.
    copy[toRow][toCol] = copy[fromRow][fromCol];
    copy[fromRow][fromCol] = ' ';

    bool check = isCheck(copy);

    if (isWhitesMove())
    {
        // std::cout << "hahahaha" << std::endl;
        // std::cout << "check: " << check << " Is_White_In_Check: " << IS_WHITE_IN_CHECK << std::endl;
        bool retrn = !IS_BLACK_IN_CHECK;
        // std::cout << "Return: " << retrn << std::endl;
        return retrn;
    }
    else
    {
        // Check if the king is in check on the simulated board.
        bool retrn = !IS_WHITE_IN_CHECK;
        // std::cout << "Return: " << retrn << std::endl;
        return retrn;
    }
}

void Game::movePiece(int fromRow, int fromCol, int toRow, int toCol, char piece)
{
    char currentPosition = BOARD[fromRow][fromCol];
    char destination = BOARD[toRow][toCol];

    // Determine if the piece is white or black
    bool isWhitePiece = (currentPosition >= 'A' && currentPosition <= 'Z');
    bool isBlackPiece = (currentPosition >= 'a' && currentPosition <= 'z');

    char column = 'a' + fromCol; // Convert column index to letter
    std::string currentKey = std::string(1, currentPosition) + column + std::to_string(BOARD_SIZE - fromRow);

    bool isDelete = destination != ' ';

    // Handle pawn promotion
    if (piece != '\0')
    {
        // Validate the promotion piece
        if ((isWhitePiece && piece >= 'A' && piece <= 'Z') || (isBlackPiece && piece >= 'a' && piece <= 'z'))
        {
            BOARD[fromRow][fromCol] = ' ';
            BOARD[toRow][toCol] = piece;

            // Update global maps with the promoted piece
            if (isWhitePiece)
            {
                ALL_WHITE_PIECES.erase(currentKey);                                              // Remove the old pawn entry
                std::string newKey = std::string(1, piece) + std::to_string(BOARD_SIZE - toRow); // e.g., "Qa8"
                ALL_WHITE_PIECES[newKey] = {toRow, toCol};
            }
            else if (isBlackPiece)
            {
                ALL_BLACK_PIECES.erase(currentKey);
                std::string newKey = std::string(1, piece) + std::to_string(BOARD_SIZE - toRow); // e.g., "qa1"
                ALL_BLACK_PIECES[newKey] = {toRow, toCol};
            }
        }
        else
        {
            std::cerr << "Invalid promotion piece!" << std::endl;
            return; // Exit function if promotion piece is invalid
        }
    }
    else
    {
        std::cout << "Moving piece from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ")\n";
        // Normal piece movement
        BOARD[toRow][toCol] = BOARD[fromRow][fromCol];
        BOARD[fromRow][fromCol] = ' ';
    }

    // Update castling rights after the move
    updateCastlingRights(fromRow, fromCol, toRow, toCol);

    // std::cout << "Current Key: " << currentKey << std::endl;

    // Update global maps for normal moves
    if (isWhitePiece)
    {
        if (ALL_WHITE_PIECES.find(currentKey) != ALL_WHITE_PIECES.end())
        {
            ALL_WHITE_PIECES[currentKey] = {toRow, toCol}; // Update position without changing the key
            if (isDelete)
            {
                ALL_WHITE_PIECES.erase(std::string(1, destination) + std::to_string(BOARD_SIZE - toRow));
            }
        }
    }
    else if (isBlackPiece)
    {
        if (ALL_BLACK_PIECES.find(currentKey) != ALL_BLACK_PIECES.end())
        {
            ALL_BLACK_PIECES[currentKey] = {toRow, toCol}; // Update position without changing the key
            if (isDelete)
            {
                ALL_BLACK_PIECES.erase(std::string(1, destination) + std::to_string(BOARD_SIZE - toRow));
            }
        }
    }
}

void Game::undoMove()
{
    std::string from = lastMove.substr(0, 2);
    std::string to = lastMove.substr(3, 2);

    // Convert chess notation (e.g., "e2") to array indices.
    int fromRow = BOARD_SIZE - (to[1] - '0'); // Convert rank (row).
    int fromCol = to[0] - 'a';                // Convert file (column).
    int toRow = BOARD_SIZE - (from[1] - '0');
    int toCol = from[0] - 'a';

    char temp = BOARD[fromRow][fromCol];
    BOARD[fromRow][fromCol] = ' ';
    BOARD[toRow][toCol] = temp;
}

bool Game::isDraw()
{
    // A draw is declared if there is exactly 1 white piece and 1 black piece left on the board.
    // This is an oversimplified condition for a draw, as in actual chess, the draw condition involves
    // other complex scenarios like stalemate, insufficient material, or a draw by repetition?????.
    bool size = (ALL_WHITE_PIECES.size() == 1 && ALL_BLACK_PIECES.size() == 1);
    bool staleMate = isStaleMate();

    // std::cout << "size: " << size << std::endl;
    // std::cout << "StaleMate: " << staleMate << std::endl;

    return size || staleMate;
}

bool Game::isWhiteFigure(int Row, int Col) const
{
    // Check if the character at the specified position is an uppercase letter
    if (isupper(BOARD[Row][Col]))
    {
        // Uncomment for debug output
        // std::cout << "You are right again!!! White" << std::endl;
        return true; // The piece at (Row, Col) is a White piece
    }
    return false; // The piece at (Row, Col) is not a White piece}
}

bool Game::isBlackFigure(int Row, int Col) const
{
    // Check if the character at the specified position is a lowercase letter
    if (islower(BOARD[Row][Col]))
    {
        // Uncomment for debug output
        // std::cout << "You are right again!!! Black" << std::endl;
        return true; // The piece at (Row, Col) is a Black piece
    }
    return false; // The piece at (Row, Col) is not a Black piece
}

bool Game::isValidMove(int fromRow, int fromCol, int toRow, int toCol)
{
    // Check if it's White's turn
    if (isWhitesMove())
    {
        // Validate conditions for White's move
        if (!isWhiteFigure(fromRow, fromCol) ||     // Source must be a White piece
            isWhiteFigure(toRow, toCol) ||          // Target must not be a White piece
            fromRow < 0 || fromRow >= BOARD_SIZE || // Source row must be within bounds
            fromCol < 0 || fromCol >= BOARD_SIZE || // Source column must be within bounds
            toRow < 0 || toRow >= BOARD_SIZE ||     // Target row must be within bounds
            toCol < 0 || toCol >= BOARD_SIZE)       // Target column must be within bounds
        {
            std::cout << "It is false" << std::endl;
            return false; // Move is invalid for White
        }
    }
    else // If it's Black's turn
    {
        // Validate conditions for Black's move
        if (!isBlackFigure(fromRow, fromCol) ||     // Source must be a Black piece
            isBlackFigure(toRow, toCol) ||          // Target must not be a Black piece
            fromRow < 0 || fromRow >= BOARD_SIZE || // Source row must be within bounds
            fromCol < 0 || fromCol >= BOARD_SIZE || // Source column must be within bounds
            toRow < 0 || toRow >= BOARD_SIZE ||     // Target row must be within bounds
            toCol < 0 || toCol >= BOARD_SIZE)       // Target column must be within bounds
        {
            return false; // Move is invalid for Black
        }
    }

    // std::cout << "It is True" << std::endl;

    return true; // Move is valid
}

bool Game::isPossibleMoveForPawn(int fromRow, int fromCol, int toRow, int toCol)
{
    // White pawn movement logic
    if (isWhitesMove())
    {
        // Ensure the source piece is a White pawn
        if (!isWhiteFigure(fromRow, fromCol))
        {
            return false; // Invalid move if not a White piece
        }

        // Move one step forward or two steps from the starting row (6)
        if ((fromCol == toCol) && (BOARD[toRow][toCol] == ' ') &&
            ((toRow - fromRow == -1) || (fromRow == 6 && abs(toRow - fromRow) == 2)))
        {
            return true; // Valid forward move
        }

        // Pawn capture (diagonal move to capture an enemy piece)
        if (abs(fromCol - toCol) == 1 && abs(toRow - fromRow) == 1 && isBlackFigure(toRow, toCol))
        {
            return true; // Valid capture move
        }

        return false; // Move is invalid for White pawn
    }
    // Black pawn movement logic
    else
    {
        // Ensure the source piece is a Black pawn
        if (isWhiteFigure(fromRow, fromCol))
        {
            return false; // Invalid move if not a Black piece
        }

        // Move one step forward or two steps from the starting row (1)
        if (fromCol == toCol && BOARD[toRow][toCol] == ' ' &&
            ((abs(fromRow - toRow) == 1) || (fromRow == 1 && abs(fromRow - toRow) == 2)))
        {
            return true; // Valid forward move
        }

        // Pawn capture (diagonal move to capture an enemy piece)
        if (abs(fromCol - toCol) == 1 && abs(fromRow - toRow) == 1 && isWhiteFigure(toRow, toCol))
        {
            return true; // Valid capture move
        }

        return false; // Move is invalid for Black pawn
    }
}

bool Game::isPossibleMoveForKnight(int fromRow, int fromCol, int toRow, int toCol)
{
    // First, validate that the move is within the rules of chess
    if (!isValidMove(fromRow, fromCol, toRow, toCol))
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

bool Game::isPossibleMoveForBishop(int fromRow, int fromCol, int toRow, int toCol)
{
    // std::cout << "----" << std::endl;
    // std::cout << "From: (" << fromRow << ", " << fromCol << ") "
    //   << "To: (" << toRow << ", " << toCol << ")\n";
    // First, validate that the move is within the rules of chess
    if (!isValidMove(fromRow, fromCol, toRow, toCol))
    {
        return false; // Invalid move based on general movement rules
    }

    // Bishops move diagonally; check if the absolute differences in rows and columns are equal
    if (abs(fromRow - toRow) != abs(fromCol - toCol))
    {
        return false; // Move is not diagonal
    }

    // // Debug: Print the computed indices.
    // std::cout << "From: (" << fromRow << ", " << fromCol << ") "
    //           << "To: (" << toRow << ", " << toCol << ")\n";

    // Determine the direction of movement for obstruction checking
    int direction;
    if ((toRow - fromRow) > 0 && (fromCol - toCol) < 0)
        direction = 1; // Moving down-right
    else if ((toRow - fromRow) > 0)
        direction = 2; // Moving down-left
    else if ((toCol - fromCol) < 0)
        direction = 3; // Moving up-left
    else
        direction = 4; // Moving up-right

    // std::cout << "Direction: " << direction << std::endl;

    // Check for obstruction along the diagonal path based on direction
    if (direction == 1) // Down-right
    {
        for (int i = fromRow + 1, j = fromCol + 1; i < toRow && j < toCol; ++i, ++j)
        {
            if (BOARD[i][j] != ' ') // If there's any piece in the way
            {
                return false; // Move is obstructed
            }
        }

        return true; // Valid move with no obstructions
    }
    else if (direction == 2) // Down-left
    {
        for (int i = fromRow + 1, j = fromCol - 1; i < toRow && j > toCol; ++i, --j)
        {
            if (BOARD[i][j] != ' ') // If there's any piece in the way
            {
                return false; // Move is obstructed
            }
        }
        return true; // Valid move with no obstructions
    }
    else if (direction == 3) // Up-left
    {
        for (int i = fromRow - 1, j = fromCol - 1; i > toRow && j > toCol; --i, --j)
        {
            if (BOARD[i][j] != ' ') // If there's any piece in the way
            {
                return false; // Move is obstructed
            }
        }
        return true; // Valid move with no obstructions
    }
    else // Up-right
    {
        for (int i = fromRow - 1, j = fromCol + 1; i > toRow && j < toCol; --i, ++j)
        {
            if (BOARD[i][j] != ' ') // If there's any piece in the way
            {
                return false; // Move is obstructed
            }
        }
        return true; // Valid move with no obstructions
    }
}

bool Game::isPossibleMoveForRook(int fromRow, int fromCol, int toRow, int toCol)
{
    // First, validate that the move is within the rules of chess
    if (!isValidMove(fromRow, fromCol, toRow, toCol))
    {
        // Uncomment for debug output
        // std::cout << "It is not a valid move for Rook" << std::endl;
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
    std::cout << "Rook Direction: " << direction << std::endl;

    // Check for obstruction along the row or column based on direction
    if (direction == 1) // Down
    {
        for (int i = fromRow + 1; i < toRow; ++i)
        {
            if (BOARD[i][fromCol] != ' ') // If there's any piece in the way
                return false;             // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
    else if (direction == 2) // Left
    {
        for (int j = fromCol - 1; j > toCol; --j)
        {
            if (BOARD[fromRow][j] != ' ') // If there's any piece in the way
                return false;             // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
    else if (direction == 3) // Up
    {
        for (int i = fromRow - 1; i > toRow; --i)
        {
            if (BOARD[i][fromCol] != ' ') // If there's any piece in the way
                return false;             // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
    else // Right
    {
        for (int j = fromCol + 1; j < toCol; ++j)
        {
            if (BOARD[fromRow][j] != ' ') // If there's any piece in the way
                return false;             // Move is obstructed
        }
        return true; // Valid move with no obstructions
    }
}

bool Game::isPossibleMoveForQueen(int fromRow, int fromCol, int toRow, int toCol)
{
    // Check if the move is valid as either a bishop or a rook move
    //  // Debug: Print the computed indices.
    // std::cout << "From: (" << fromRow << ", " << fromCol << ") "
    //           << "To: (" << toRow << ", " << toCol << ")\n";

    bool bishopMove = isPossibleMoveForBishop(fromRow, fromCol, toRow, toCol);
    bool rookMove = isPossibleMoveForRook(fromRow, fromCol, toRow, toCol);

    // Uncomment for debug output
    // std::cout << "Bishop Move: " << bishopMove << std::endl;
    // std::cout << "Rook Move: " << rookMove << std::endl;

    // A queen can move like either a bishop or a rook
    bool retrn = (bishopMove || rookMove);
    // std::cout << "Bishop: " << bishopMove << ' ' << "Rook: " << rookMove << ' ' << "Return: " << retrn << std::endl;
    return retrn;
}

bool Game::isPossibleMoveForKing(int fromRow, int fromCol, int toRow, int toCol)
{
    // First, validate that the move is within the rules of chess
    if (!isValidMove(fromRow, fromCol, toRow, toCol))
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

bool Game::isPossibleMove(int fromRow, int fromCol, int toRow, int toCol)
{
    switch (BOARD[fromRow][fromCol])
    {
    case 'p':
    case 'P': // Pawn
        return isPossibleMoveForPawn(fromRow, fromCol, toRow, toCol);
    case 'b':
    case 'B': // Bishop
        return isPossibleMoveForBishop(fromRow, fromCol, toRow, toCol);
    case 'n':
    case 'N': // Knight
        return isPossibleMoveForKnight(fromRow, fromCol, toRow, toCol);
    case 'q':
    case 'Q': // Queen
        return isPossibleMoveForQueen(fromRow, fromCol, toRow, toCol);
    case 'k':
    case 'K': // King
        return isPossibleMoveForKing(fromRow, fromCol, toRow, toCol);
    default: // Invalid piece
        return false;
    }
}

bool Game::isCorrectFigure(int row, int col, bool isWhite) const
{
    char piece = BOARD[row][col];
    // Check if the piece matches the color based on ASCII values
    bool val = (isWhite && piece >= 'A' && piece <= 'Z') ||
               (!isWhite && piece >= 'a' && piece <= 'z');

    // Uncomment for debug output
    // std::cout << "IsWhite: " << isWhite << std::endl;
    // std::cout << "Piece: " << piece << " Color Match: " << val << std::endl;

    return val; // Return whether the color matches
}

std::vector<std::pair<int, int>> Game::allPossibleFields(int checkRow, int checkCol, int kingRow, int kingCol)
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
    if (direction == 1)
    {
        int startCol = std::min(checkCol, kingCol);
        int endCol = std::max(checkCol, kingCol);
        for (int col = startCol + 1; col < endCol; ++col)
        {
            positions.emplace_back(checkRow, col); // Add positions in between
        }
    }
    // Handle vertical movement
    else if (direction == 2)
    {
        int startRow = std::min(checkRow, kingRow);
        int endRow = std::max(checkRow, kingRow);
        for (int row = startRow + 1; row < endRow; ++row)
        {
            positions.emplace_back(row, checkCol); // Add positions in between
        }
    }
    // Handle diagonal movement
    else if (direction == 3)
    {
        int rowStep = (kingRow > checkRow) ? 1 : -1; // Determine step direction for rows
        int colStep = (kingCol > checkCol) ? 1 : -1; // Determine step direction for columns
        int row = checkRow + rowStep;
        int col = checkCol + colStep;

        // Loop until reaching the king's position
        while (row != kingRow && col != kingCol)
        {
            positions.emplace_back(row, col); // Add diagonal positions in between
            row += rowStep;                   // Move to next row
            col += colStep;                   // Move to next column
        }
    }

    return positions; // Return all possible fields between the piece and the king
}