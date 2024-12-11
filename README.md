# Chess Game

A simple console-based Chess game implemented in C++ that allows two players to play the game. The game supports standard Chess rules and displays the board in the terminal.

## Files

### ChessFunctional
- **board_display.cpp**: Handles the display of the chessboard on the console and provides functions to print the board.
- **board_display.h**: Header file for board_display.cpp, contains declarations for the board display functions.
- **game_logic.cpp**: Contains the core game logic, including move validation and turn management.
- **game_logic.h**: Header file for game_logic.cpp, contains declarations for game logic functions.
- **game_state.cpp**: Contains global variables that track the state of the game, such as the board layout, the current player, and the game status.
- **game_state.h**: Header file for game_state.cpp, contains declarations for game state-related functions.
- **main.cpp**: The entry point of the game. Contains the main game loop and initialization.
- **move_validation.cpp**: Handles the validation of moves according to Chess rules, ensuring that moves are legal.
- **move_validation.h**: Header file for move_validation.cpp, contains declarations for move validation functions.

### ChessOOP
- **chess.exe**: The executable for the OOP version of the game.
- **Game.cpp**: Contains the implementation of the game class for the OOP version.
- **Game.h**: Header file for Game.cpp, contains the class definition and method declarations.
- **main.cpp**: The entry point of the game for the OOP version. Contains the main game loop and initialization.

## Compilation

To compile and run the Chess game, follow these steps:

### To run the Functional version:

1. **Navigate to the directory**:
   ```bash
   cd ./ChessFunctional

2. **Compile the code**:
   ```bash
   g++ main.cpp board_display.cpp game_state.cpp game_logic.cpp move_validation.cpp -o chess

3. **Run the game**:
   ```bash
   ./chess

### To run the OOP version:

1. **Navigate to the directory**:
   ```bash
   cd ./ChessOOP

2. **Compile the code**:
   ```bash
   g++ main.cpp Game.cpp -o chess

3. **Run the game**:
   ```bash
   ./chess

# How to Play

1. Players will take turns to make moves.
2. The game will prompt for a move in standard chess notation (e.g., e2 e4).
3. The game will check if the move is valid according to Chess rules.
4. The board will be displayed after each move, showing the updated positions of all pieces.
5. The game will continue until one player wins, or a draw is declared.

# Features

- Supports all standard Chess pieces: King, Queen, Rook, Bishop, Knight, Pawn.
- Move validation based on Chess rules.
- Displays the board after each move in a text-based format.
- Detects check and checkmate situations.
- Basic game loop for two players.

# License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
