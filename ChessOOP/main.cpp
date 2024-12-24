/**
 * @file main.cpp
 * @brief Main entry point for the Chess game application.
 * 
 * This file contains the main function which initializes the game and handles the main game loop.
 * The game loop processes player moves, checks for game states (check, checkmate, draw), and switches turns.
 * Special moves like castling and draw offers are also handled here.
 */

#include <iostream>
#include <string>
#include "Game.h" // Include the header file for the Game class

int main()
{
    Game chessGame; // Create an instance of the Game class

    // Main game loop
    while (true)
    {
        chessGame.displayBoard(); // Display the current state of the board

        // Input the player's move
        std::cout << "Turn: " << (chessGame.getTurn() ? "White" : "Black") << std::endl;
        std::string move;
        std::cout << "Enter your move (e.g., e2 e4): ";
        std::getline(std::cin, move);
        // std::cout << "Move: " << move << std::endl;

        if (move == "Draw?")
        {
            std::cout << "Do the other player agree with Draw? Write 'Yes' or 'No': ";
            std::string answer;             // Variable to store the response
            std::getline(std::cin, answer); // Read the user's response into 'answer'

            if (answer == "Yes")
            {
                std::cout << "It`s Draw." << std::endl;
                return 0; // End the game with a draw
            }
            else if (answer == "No")
            {
                std::cout << "Not this time." << std::endl;
                continue;
            }
            else
            {
                std::cout << "Invalid response. Please write 'Yes' or 'No'." << std::endl;
            }
        }

        // std::cout << "is 0-0: " << (move == "0-0") << std::endl;
        
        if (move == "0-0")
        {
            // Handle kingside castling
            std::string from = move.substr(0, 1);
            std::string to = move.substr(2, 1);

            // std::cout << from << std::endl;
            // std::cout << to << std::endl;

            // Validate and execute the move
            if (!chessGame.checkMovePiece(from, to))
            {
                std::cout << "Invalid move! (" << from << " -> " << to << ") Try again.\n";
                continue; // Prompt for re-entry on invalid moves
            }

            // Switch turn (Black or White)
            chessGame.changeMove();
            continue;
        }
        else if (move == "0-0-0")
        {
            // Handle queenside castling
            std::string from = move.substr(0, 3);
            std::string to = move.substr(4, 1);

            // Validate and execute the move
            if (!chessGame.checkMovePiece(from, to))
            {
                std::cout << "Invalid move! (" << from << " -> " << to << ") Try again.\n";
                continue; // Prompt for re-entry on invalid moves
            }

            // Switch turn (Black or White)
            chessGame.changeMove();
            continue;
        }

        // Split the input into "from" and "to" positions
        if (move.size() != 5 || move[2] != ' ')
        {
            std::cout << "Invalid input format! Use 'from to'. Try again.\n";
            continue;
        }
        std::string from = move.substr(0, 2);
        std::string to = move.substr(3, 2);

        // Validate and execute the move
        if (!chessGame.checkMovePiece(from, to))
        {
            std::cout << "Invalid move! (" << from << " -> " << to << ") Try again.\n";
            continue; // Prompt for re-entry on invalid moves
        }

        // Check for endgame states
        if (chessGame.isCheck())
        {
            if (chessGame.isCheckMate())
            { 
                chessGame.displayBoard();
                std::cout << "\nCHECKMATE!!!!!" << std::endl;
                std::cout << (chessGame.getTurn() ? "Black" : "White") << " wins.\n";
                return 0;
            }
        }
        else if (chessGame.isDraw())
        {
            std::cout << "It's a draw!" << std::endl;
            return 0;
        }

        // Switch turn (Black or White)
        chessGame.changeMove();
    }

    return 0; // Exit the program
}