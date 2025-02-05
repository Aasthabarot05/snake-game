# snake-game
# Snake Game - README

## Introduction
This is a simple Snake game implemented in C++ for the console. The game features a snake that moves around the screen, consuming fruit to grow in size. The game ends when the snake collides with the wall or itself. The game also includes sound effects for interactions and a pause function.

## Features
- Classic Snake game mechanics.
- Console-based graphics.
- Sound effects for key interactions.
- Start screen and game-over screen.
- Score tracking.

## Controls
- `W` - Move Up
- `A` - Move Left
- `S` - Move Down
- `D` - Move Right
- `X` - Exit the game

## How to Play
1. Run the program in a Windows console.
2. Press `ENTER` on the start screen to begin.
3. Use the `W`, `A`, `S`, and `D` keys to move the snake.
4. Collect the fruit (`F`) to grow and increase your score.
5. Avoid colliding with the walls and yourself.
6. When the game ends, press `R` to restart or `Q` to quit.

## Requirements
- Windows OS (due to `windows.h` and `Beep()` function usage).
- C++ compiler that supports `conio.h` and `windows.h`.

## Installation & Compilation
1. Save the `snake_game.cpp` file.
2. Open a terminal and navigate to the file's location.
3. Compile the code using a C++ compiler:
   ```sh
   g++ snake_game.cpp -o snake_game.exe
   ```
4. Run the game:
   ```sh
   snake_game.exe
   ```

## Future Improvements
- Implementing levels with increasing difficulty.
- Adding a high-score system.
- Enhancing visuals with better rendering techniques.
- Making it cross-platform by removing Windows-specific dependencies.

## Author
This Snake game was developed as a console-based project for learning and entertainment purposes.

