# SFML Tic-Tac-Toe Game with AI

A classic Tic-Tac-Toe game implementation using C++ and SFML (Simple and Fast Multimedia Library). Play against an unbeatable AI opponent that uses the Minimax algorithm for decision making.

## Features

- Graphical user interface using SFML
- Human vs AI gameplay
- Unbeatable AI using Minimax algorithm
- Visual feedback with X's and O's
- Game state detection (win, lose, draw)
- Clean and modern design

## Technologies Used

- C++
- SFML (Simple and Fast Multimedia Library)
- Minimax Algorithm for AI

## Prerequisites

To run this game, you'll need:

- C++ compiler
- SFML library installed
- CMake (recommended for building)

## Installation

1. Clone the repository:
```bash
git clone [your-repository-url]
cd [repository-name]
```

2. Install SFML:
- On Ubuntu/Debian:
  ```bash
  sudo apt-get install libsfml-dev
  ```
- On macOS:
  ```bash
  brew install sfml
  ```
- On Windows:
  Download SFML from the official website and link it to your project

3. Build the project:
```bash
mkdir build
cd build
cmake ..
make
```

## How to Play

1. Run the executable
2. Click on any empty cell to place your move (O)
3. The AI will automatically respond with its move (X)
4. Try to get three in a row horizontally, vertically, or diagonally
5. The game will announce when there's a winner or a draw

## Implementation Details

- The game uses a 3x3 grid represented by a 2D array
- Player moves are handled through mouse input
- AI moves are calculated using the Minimax algorithm
- The game features a clean visual interface with X's and O's
- Win detection checks all possible winning combinations after each move

## Code Structure

- `main()`: Game loop and window management
- `minimax()`: AI decision-making algorithm
- `find_best_move()`: Determines optimal AI move
- `draw_board()`: Renders the game board and pieces
- `is_winner()`: Checks for winning conditions
- `is_move_left()`: Validates if moves are available

## Future Improvements

- Add difficulty levels
- Include sound effects
- Add a start menu
- Implement game statistics
- Add multiplayer support

## Contributing

Feel free to fork this project and submit pull requests. You can also open issues for bugs or feature suggestions.

## Author

Elmar Ismayilov

## Acknowledgments

- SFML development team
- C++ community
- Everyone who has contributed to the project
