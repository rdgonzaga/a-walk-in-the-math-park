
# A Walk In The Math Park 🏞️

## 📍Description
A turn based game that would aid in teaching Mathematics to kids by doing mental math. The objective of the game is for players to reach the last tile (i.e., tile 50) by answering simple math problems for every tile the player lands.

## 🕹️ Installation

### Prerequisites

- Ensure you have [GCC](https://gcc.gnu.org) installed.

### Build from source

**1. Clone the repository**

```bash
git clone https://github.com/reniar-g/A-Walk-In-The-Math-Park.git
```

**2. Navigate to the project directory**

```bash
cd A-Walk-In-The-Math-Park
```

**3. Compile the program**

```bash
gcc -Wall -std=c99 -o MathPark AWalkInTheMathPark.c
```

**4. Run the .exe file**

```bash
./MathPark
```
    
## 🎮 How to Play

- The objective is to reach tile 50 by solving math problems.
- Roll the dice to move along the game board.
- Solve the math equation displayed when you land on a tile.
     - Wrong: Stay on the tile.
     - Correct: Move back 1 to 3 tiles.
- If a player roll a 6, they will take another turn.
- If a player went over tile 50, they will bounce back.
- First player to reach tile 50 or last player standing wins.


## 📖 Acknowledgements

1. Code used for generating random numbers

https://www.geeksforgeeks.org/generating-random-number-range-c/

2. ANSI escape sequences chart referred to for coloring texts and clearing the screen

https://www.theurbanpenguin.com/4184-2/

3. Website used for converting a text to ASCII Art

https://www.asciiart.eu/text-to-ascii-art

## 🧑🏽‍💻 Author

- Developed by [Rainer D. Gonzaga](https://www.github.com/octokatherine)

