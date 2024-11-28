# Chess Game

A simple console-based Chess game implemented in C++ that allows two players to play the game. The game supports standard Chess rules and displays the board in the terminal.

## Files

- **main.cpp**: The entry point of the game. Contains the main game loop and initialization.
- **board_display.cpp**: Handles the display of the chessboard on the console. Provides functions to print the board.
- **game_state.cpp**: Contains global variables that track the state of the game, such as the board layout, the current player, and game status.
- **game_logic.cpp**: Contains the core game logic, including move validation and turn management.
- **move_validation.cpp**: Handles the validation of moves according to Chess rules, ensuring that moves are legal.

## Compilation

To compile and run the Chess game, follow these steps:

1. **Compile the code**:
   ```bash
   g++ main.cpp board_display.cpp game_state.cpp game_logic.cpp move_validation.cpp -o chess

2. **Run the game**:
   ```bash
   ./chess

# How to Play

1. Players will take turns to make moves.
2. The game will prompt for a move in standard chess notation (e.g., e2 to e4).
3. The game will check if the move is valid according to Chess rules.
4. The board will be displayed after each move, showing the updated positions of all pieces.
5. The game will continue until one player wins, or a draw is declared.

# Features

- Supports all standard Chess pieces: King, Queen, Rook, Bishop, Knight, Pawn.
- Move validation based on Chess rules.
- Displays the board after each move in a text-based format.
- Detects check and checkmate situations.
- Basic game loop for two players.

