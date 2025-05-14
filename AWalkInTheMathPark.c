/******************************************************************************
This is to certify that this project is my own work, based on my personal
efforts in studying and applying the concepts learned. I have constructed
the functions and their respective algorithms and corresponding code by
myself. The program was run, tested, and debugged by my own efforts. I
further certify that I have not copied in part or whole or otherwise
plagiarized the work of other students and/or persons.

<Rainer D. Gonzaga> - <124#####> - <S12A>
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

// Function prototypes
int generateMathProblem(int difficulty, int *correctAnswer); // Function to generate math problems
int handleMathProblem(int playerNumber, int playerPos, int *playerActive, int difficulty); // Function to handle math problems
int playerTurn(int playerNumber, int playerPos, int *playerActive, int difficulty, int *p1Pos, int *p2Pos, int *p3Pos, int *p4Pos); // Function to handle player turns
int homeScreen(); // Function to display the home screen
void printGameBoard(int p1Pos, int p2Pos, int p3Pos, int p4Pos); // Function to print the game board
int rollDice(); // Function to roll the dice
void clearScreen(); // Function to clear the screen
void endScreen(); // Function to display the end screen
void errorInputScreen(); // Function to display the error input screen
void instructionScreen(); // Function to display the instructions screen
void mathBoardHeader(); // Function to display the math board header
void mathParkHeader(); // Function to display the math park header
void readyHeader(); // Function to display the ready header
void startGame(); // Function to start the game
void victoryScreen(); // Function to display the victory screen
void numberOfPlayerScreen(); // Function to display the number of players screen
void difficultyScreen(); // Function to display the difficulty screen
void loserScreen(); // Function to display the loser screen
void mainMenuOptions(); // display main menu

/* 
    Clears the console screen.
    Precondition: The program is running on a Windows operating system.
    @return void
*/
void clearScreen() {
    system("cls"); // Clear screen command 
}

/* 
    Prompts the player to roll the dice and returns the dice value.
    Precondition: The player is prompted to press 'r' to roll the dice.
    @param playerNumber The number of the player who is rolling the dice.
    @return The value of the dice roll (1-6).
*/
int rollDice(int playerNumber) {
    char input;
    int diceValue;

    printf("===========================================================================================\n");
    printf("\nPlayer %d, press \033[0;33m'r'\033[m to roll the dice: ", playerNumber);
    
    while (1) {
        scanf(" %c", &input);  // The space before %c ignores any leading whitespace
        
        if (input == 'r' || input == 'R') {
            printf("\nRolling the dice"); // If r or R is inputted, it will print Rolling the dice.
            for (int i = 0; i < 3; i++) {
                printf("."); //Loading... effect
                Sleep(500);  // Sleep for 500 milliseconds (0.5 seconds)
            }
            clearScreen();
            diceValue = (rand() % 6) + 1; /// Roll dice by generating random numbers from 0-6
            printf("===========================================================================================\n");
            printf("\nPlayer %d rolled a \033[0;32m%d\033[m!\n", playerNumber, diceValue);
            return diceValue;
        } else {
            printf("\n\033[0;31mInvalid input. Player %d, please press 'r' to roll: \033[m", playerNumber);
        }
    }
}

/* 
    Prints the game board with the current positions of all players.
    Precondition: The positions of all players are provided.
    @param p1Pos The position of player 1.
    @param p2Pos The position of player 2.
    @param p3Pos The position of player 3.
    @param p4Pos The position of player 4.
    @return void
*/
void printGameBoard(int p1Pos, int p2Pos, int p3Pos, int p4Pos) {
    int num = 41;  // Start with 41 at top row

    mathBoardHeader();
    printf("===========================================================================================    The Player Positions\n");
    printf("+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+   +--------------------+\n");
    for (int i = 4; i >= 0; i--) {  // Start from top row (i = 4) down to bottom (i=0)
        for (int j = 0; j < 10; j++) {
            int pos;
            if (i % 2 == 0) {
                // Even rows: left to right (41-50, 21-30, 01-10)
                pos = num + j;
            } else {
                // Odd rows: right to left (40-31, 20-11)
                pos = num + 9 - j;
            }

            // Print player positions
            if (pos == p1Pos) {
                printf("|   \033[1;31mP1\033[0m   ");
            } else if (pos == p2Pos) {
                printf("|   \033[1;34mP2\033[0m   ");
            } else if (pos == p3Pos) {
                printf("|   \033[1;33mP3\033[0m   ");
            } else if (pos == p4Pos) {
                printf("|   \033[1;35mP4\033[0m   ");
            } else {
                printf("|   %02d   ", pos);
            }
        }
        // Print player positions beside the table
        if (i == 4) { // Check if it's the row for Player 1
            if (p1Pos <= 0) { // Check if Player 1 is eliminated
                printf("|   |     \033[1;31mEliminated\033[m     |\n"); // Print "Eliminated" in red
            } else {
                printf("|   |  \033[1;31mP1\033[0m is in tile \033[1;32m%02d\033[m  |\n", p1Pos); // Print Player 1's position in green
            }
        } else if (i == 3) { 
            if (p2Pos <= 0) {
                printf("|   |     \033[1;31mEliminated\033[m     |\n"); 
            } else {
                printf("|   |  \033[1;34mP2\033[0m is in tile \033[1;32m%02d\033[m  |\n", p2Pos); // Print Player 2's position in green
            }
        } else if (i == 2) { 
            if (p3Pos <= 0) { 
                printf("|   |     \033[1;31mEliminated\033[m     |\n"); 
            } else {
                printf("|   |  \033[1;33mP3\033[0m is in tile \033[1;32m%02d\033[m  |\n", p3Pos); // Print Player 3's position in green
            }
        } else if (i == 1) { 
            if (p4Pos <= 0) { 
                printf("|   |     \033[1;31mEliminated\033[m     |\n"); 
            } else {
                printf("|   |  \033[1;35mP4\033[0m is in tile \033[1;32m%02d\033[m  |\n", p4Pos); // Print Player 4's position in green
            }
        } else {
            printf("|\n");
        }
        if (i != 0) {
            printf("+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+   +--------------------+\n");
        }
        num -= 10;
    }
    printf("+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+\n");
}

/* 
    Handles a player's turn, including rolling the dice, moving the player, and handling math problems.
    Precondition: The player is active and it's their turn.
    @param playerNumber The number of the player whose turn it is.
    @param playerPos The current position of the player.
    @param playerActive Pointer to the player's active status.
    @param difficulty The difficulty level of the math problems.
    @param p1Pos Pointer to the position of player 1.
    @param p2Pos Pointer to the position of player 2.
    @param p3Pos Pointer to the position of player 3.
    @param p4Pos Pointer to the position of player 4.
    @return The updated position of the player after their turn.
*/
int playerTurn(int playerNumber, int playerPos, int *playerActive, int difficulty, int *p1Pos, int *p2Pos, int *p3Pos, int *p4Pos) {
    int keepTurn = 1; // Flag to determine if the player gets another turn

    while (keepTurn && *playerActive) {

        // Roll the dice and move the player
        int diceRoll = rollDice(playerNumber);

        playerPos += diceRoll;
        printf("Player %d moved to tile \033[0;32m%d\033[m.\n", playerNumber, playerPos);

        // Bounce back if overshooting
        if (playerPos > 50) {
            int excess = playerPos - 50;
            playerPos = 50 - excess;
            printf("Player %d bounced back to tile %d.\n", playerNumber, playerPos);
        }

        // Update player positions
        if (playerNumber == 1) *p1Pos = playerPos;
        if (playerNumber == 2) *p2Pos = playerPos;
        if (playerNumber == 3) *p3Pos = playerPos;
        if (playerNumber == 4) *p4Pos = playerPos;

        // Print the game board with updated positions
        printGameBoard(*p1Pos, *p2Pos, *p3Pos, *p4Pos);

        // Check for winning condition
        if (playerPos == 50) {
            return 50;
        }

        // Handle math problem and penalties
        int correctAnswer;
        if (!generateMathProblem(difficulty, &correctAnswer)) {
            int penalty = (rand() % 3) + 1;
            playerPos -= penalty;
            printf("===========================================================================================\n");
            printf("\nPlayer \033[0;33m%d\033[m answered\033[0;31m incorrectly\033[m. The correct answer was \033[0;32m%d\033[m. Moved back \033[0;31m%d\033[m tile(s) to tile \033[0;32m%d\033[m.\n", playerNumber, correctAnswer, penalty, playerPos);

            if (playerPos <= 0) {
                *playerActive = 0;
                printf("\nPlayer \033[0;31m%d\033[m has been\033[0;31m eliminated\033[m!\n", playerNumber);
                // Update player positions
                if (playerNumber == 1) *p1Pos = playerPos;
                if (playerNumber == 2) *p2Pos = playerPos;
                if (playerNumber == 3) *p3Pos = playerPos;
                if (playerNumber == 4) *p4Pos = playerPos;
                // Print the game board with updated positions
                printGameBoard(*p1Pos, *p2Pos, *p3Pos, *p4Pos);
                return playerPos;
            }
        } else {
            printf("===========================================================================================\n");
            printf("\nPlayer \033[0;33m%d\033[m answered\033[0;32m correctly\033[m and stays on tile \033[0;32m%d\033[m.\n", playerNumber, playerPos);
        }

        // Update player positions
        if (playerNumber == 1) *p1Pos = playerPos;
        if (playerNumber == 2) *p2Pos = playerPos;
        if (playerNumber == 3) *p3Pos = playerPos;
        if (playerNumber == 4) *p4Pos = playerPos;

        // Print the game board with updated positions
        printGameBoard(*p1Pos, *p2Pos, *p3Pos, *p4Pos);

        // Check if player rolled a 6 for another turn
        keepTurn = (diceRoll == 6);
        if (keepTurn) {
            printf("===========================================================================================\n");
            printf("\nPlayer %d rolled a \033[0;33m6\033[m! Get another turn!\n\n", playerNumber);
        }
    }
    return playerPos;
}

/* 
    Initializes and starts the game, setting up players and handling the game loop.
    Precondition: The game is ready to start, and the user has selected the number of players and difficulty level.
    @return void
*/
void startGame() {
    int difficulty;
    int playerCount = 0;
    int p1Pos = 1, p1Active = 1; // Player 1 starts at position 1 and is active
    int p2Pos = 0, p2Active = 0; // 0 = Inactive
    int p3Pos = 0, p3Active = 0;
    int p4Pos = 0, p4Active = 0;
    int currentPlayer = 1, winner = 0; // Track the current player and winner
    int gameActive = 1; // Flag to indicate if the game is active
    srand(time(0)); // seed the rng

    // Get number of users
    mathParkHeader();
    numberOfPlayerScreen();
    do {   
        printf("Enter your option: ");
        if (scanf("%d", &playerCount) != 1 || playerCount < 1 || playerCount > 4) {
            // Clear the input buffer
            while (getchar() != '\n');
            mathParkHeader();
            numberOfPlayerScreen();
            printf("\033[0;31mInvalid input, please try again.\033[m\n\n");
        }
    } while (playerCount < 1 || playerCount > 4);
    
    // Activate additional players based on the count
    if (playerCount >= 2) {
        p2Pos = 1;
        p2Active = 1;
    }
    if (playerCount >= 3) {
        p3Pos = 1;
        p3Active = 1;
    }
    if (playerCount == 4) {
        p4Pos = 1;
        p4Active = 1;
    }

    // Get the difficulty
    mathParkHeader();
    difficultyScreen();
    do {   
        printf("Enter your difficulty: ");
        if (scanf("%d", &difficulty) != 1 || difficulty < 1 || difficulty > 3) {
            // Clear the input buffer
            while (getchar() != '\n');
            mathParkHeader();
            difficultyScreen();
            printf("\033[0;31mInvalid input, please try again.\033[m\n\n");
        }
    } while (difficulty < 1 || difficulty > 3);

    clearScreen();
    if (playerCount == 1){
        readyHeader();
        printf("\033[0;32m                                   Game setup complete!\n");
        printf("\033[m\033[0;33m                         %d\033[m player will play on difficulty level \033[0;33m%d\033[m.\n", playerCount, difficulty);
    } else {
        readyHeader();
        printf("\033[0;32m                                   Game setup complete!\n");
        printf("\033[m\033[0;33m                         %d\033[m players will play on difficulty level \033[0;33m%d\033[m.\n", playerCount, difficulty);
    }
    printf("\n                              Press \033[0;33m\"Enter\"\033[m to start the game.");
    getchar(); 
    getchar(); // Wait for user to press Enter
    clearScreen();

    // This will loop the game until someone wins or all players are eliminated
    while (winner == 0 && gameActive) {
        // Handle Player 1
        if (currentPlayer == 1 && p1Active) {
            p1Pos = playerTurn(1, p1Pos, &p1Active, difficulty, &p1Pos, &p2Pos, &p3Pos, &p4Pos);
            if (p1Pos == 50) winner = 1;
        }

        // Handle Player 2
        if (currentPlayer == 2 && p2Active) {
            p2Pos = playerTurn(2, p2Pos, &p2Active, difficulty, &p1Pos, &p2Pos, &p3Pos, &p4Pos);
            if (p2Pos == 50) winner = 2;
        }

        // Handle Player 3
        if (currentPlayer == 3 && p3Active) {
            p3Pos = playerTurn(3, p3Pos, &p3Active, difficulty, &p1Pos, &p2Pos, &p3Pos, &p4Pos);
            if (p3Pos == 50) winner = 3;
        }

        // Handle Player 4
        if (currentPlayer == 4 && p4Active) {
            p4Pos = playerTurn(4, p4Pos, &p4Active, difficulty, &p1Pos, &p2Pos, &p3Pos, &p4Pos);
            if (p4Pos == 50) winner = 4;
        }

        // Check if all players are eliminated
        if (!p1Active && !p2Active && !p3Active && !p4Active) {
            loserScreen();
            printf("\nAll players have been\033[0;31m eliminated\033[m.\033[0;31m You lost\033[m.\n");
            gameActive = 0; // Set the flag to indicate the game is over
        }

        // Advance to the next player
        currentPlayer++;
        if (currentPlayer > playerCount) currentPlayer = 1;
    }

    // Announce Winner
    if (winner != 0) {
        victoryScreen();
        printf("                       Player \033[0;33m%d\033[m wins the game! Congratulations!\n", 1);
        printf("                      See you on the next adventure at Math Park!\n");
    }
    printf("\nPress \"Enter\" to return to the main menu...");
    getchar();
    getchar();
}

/* 
    Generates a math problem based on the difficulty level and checks the user's answer.
    Precondition: The difficulty level is provided.
    @param difficulty The difficulty level of the math problem (1 = Easy, 2 = Medium, 3 = Hard).
    @param correctAnswer Pointer to store the correct answer of the generated math problem.
    @return 1 if the user's answer is correct, 0 otherwise.
*/
int generateMathProblem(int difficulty, int *correctAnswer) {
    int num1, num2, result, userAnswer;
    char operator;
    int operatorChoice = rand() % 5 + 1; // Random operator (1-5)

    // Generate numbers based on difficulty
    if (difficulty == 1) {
        num1 = rand() % 21 - 10; // -10 to 10
        num2 = rand() % 21 - 10;
    } else if (difficulty == 2) {
        num1 = rand() % 201 - 100; // -100 to 100
        num2 = rand() % 201 - 100;
    } else {
        num1 = rand() % 2001 - 1000; // -1000 to 1000
        num2 = rand() % 2001 - 1000;
    }

    // Avoid division by zero
    if ((operatorChoice == 4 || operatorChoice == 5) && num2 == 0) num2 = 1;

    // Determine the operator and calculate result
    if (operatorChoice == 1) {
        operator = '+';
        result = num1 + num2;
    } else if (operatorChoice == 2) {
        operator = '-';
        result = num1 - num2;
    } else if (operatorChoice == 3) {
        operator = '*';
        result = num1 * num2;
    } else if (operatorChoice == 4) {
        operator = '/';
        result = num1 / num2;
    } else {
        operator = '%';
        result = num1 % num2;
    }

   // Store the correct answer
    *correctAnswer = result;

    // Prompt the user for an answer
    printf("===========================================================================================\n");
    printf("\nSolve the following: %d %c %d = ", num1, operator, num2);

    // Validate user input
    while (scanf("%d", &userAnswer) != 1) {
        // Clear the input buffer
        while (getchar() != '\n');
        printf("\033[0;31mInvalid input. Please enter a number: \033[m");
    }
    clearScreen();

    // Check if the answer is correct
    return userAnswer == result;
}

/* 
    Displays the Math Park header.
    Precondition: None.
    @return void
*/
void mathParkHeader() {
    clearScreen();
    printf("================================================================\n");
    printf("\n--------------------------- \033[0;33mWelcome To\033[m -------------------------\n");
    printf("\033[0;33m       _   __        __    _ _      _         _   _            \n");
    printf("      / \\  \\ \\      / /_ _| | | __ (_)_ __   | |_| |__   ___\n");
    printf("     / _ \\  \\ \\ /\\ / / _` | | |/ / | | '_ \\  | __| '_ \\ / _ \\ \n");
    printf("    / ___ \\  \\ V  V / (_| | |   <  | | | | | | |_| | | |  __/ \n");
    printf("   /_/   \\_\\  \\_/\\_/ \\__,_|_|_|\\_\\ |_|_| |_|  \\__|_| |_|\\___|\n");
    printf("          __  __       _   _       ____            _    \n");
    printf("         |  \\/  | __ _| |_| |__   |  _ \\ __ _ _ __| | __\n");
    printf("         | |\\/| |/ _` | __| '_ \\  | |_) / _` | '__| |/ /\n");
    printf("         | |  | | (_| | |_| | | | |  __/ (_| | |  |   <\n");
    printf("         |_|  |_|\\__,_|\\__|_| |_| |_|   \\__,_|_|  |_|\\_\\ \033[m\n\n");  
    printf("================================================================\n\n");
}

/* 
    Displays the screen to select the number of players.
    Precondition: None.
    @return void
*/
void numberOfPlayerScreen(){
    printf("                 |  Enter number of players: |                \n");
    printf("                 |      [1] 1 Player         |                \n");
    printf("                 |      [2] 2 Players        |                \n");
    printf("                 |      [3] 3 Players        |                \n");  
    printf("                 |      [4] 4 Players        |                \n\n");  
    printf("================================================================\n\n");
}

/* 
    Displays the screen to select the difficulty level.
    Precondition: None.
    @return void
*/
void difficultyScreen(){
    printf("                 |     Enter difficulty:     |                \n");
    printf("                 |  [1] Easy (-10 to 10)     |                \n");
    printf("                 |  [2] Medium (-100 to 100) |                \n");
    printf("                 |  [3] Hard (-1000 to 1000) |                \n\n");  
    printf("================================================================\n\n");
}

/* 
    Displays the ready header.
    Precondition: None.
    @return void
*/
void readyHeader() {
    clearScreen();
    printf("\n===========================================================================================\n");
    printf("\033[0;32m           _    ____  _____  __   _____  _   _   ____  _____    _    ______   _____ \n");
    printf("          / \\  |  _ \\| ____| \\ \\ / / _ \\| | | | |  _ \\| ____|  / \\  |  _ \\ \\ / /__ \\\n");
    printf("         / _ \\ | |_) |  _|    \\ V / | | | | | | | |_) |  _|   / _ \\ | | | \\ V /  / /\n");
    printf("        / ___ \\|  _ <| |___    | || |_| | |_| | |  _ <| |___ / ___ \\| |_| || |  |_| \n");
    printf("       /_/   \\_\\_| \\_\\_____|   |_| \\___/ \\___/  |_| \\_\\_____/_/   \\_\\____/ |_|  (_) \033[m\n\n");
    printf("===========================================================================================\n\n");
}

/* 
    Displays the instructions screen.
    Precondition: User selects the instructions menu option.
    @return void
*/
void instructionScreen() {
    clearScreen();
    printf("\n================================================================\n");
    printf("\033[0;33m   ____                        __  __                         _ \n");
    printf("  / ___| __ _ _ __ ___   ___  |  \\/  | __ _ _ __  _   _  __ _| |\n");
    printf(" | |  _ / _` | '_ ` _ \\ / _ \\ | |\\/| |/ _` | '_ \\| | | |/ _` | |\n");
    printf(" | |_| | (_| | | | | | |  __/ | |  | | (_| | | | | |_| | (_| | |\n");
    printf("  \\____|\\__,_|_| |_| |_|\\___| |_|  |_|\\__,_|_| |_|\\__,_|\\__,_|_|\033[m\n\n");
    printf("================================================================\n");
    printf("\n1. The objective is to reach tile 50 by solving math problems.\n");
    printf("2. Roll the dice to move along the game board.\n");
    printf("3. Solve the math equation displayed when you land on a tile.\n");
    printf("     - \033[0;32mWrong\033[m: Stay on the tile.\n");
    printf("     - \033[0;31mCorrect\033[m: Move back 1 to 3 tiles.\n");
    printf("4. If a player roll a 6, they will take another turn.\n");
    printf("5. If a player went over tile 50, they will bounce back.\n");
    printf("6. First player to reach tile 50 or last player standing wins.\n");
    printf("\n================================================================\n");
    printf("\nPress \"Enter\" to go back ");
    getchar(); 
    getchar();
}

/* 
    Displays the end screen.
    Precondition: User selects 3 in the main menu.
    @return void
*/
void endScreen() {
    clearScreen();
    printf("\n================================================================\n");
    printf("\033[0;31m           ____  ___   ___  ____  ______   _______   _ \n");
    printf("          / ___|/ _ \\ / _ \\|  _ \\| __ ) \\ / / ____| | |\n");
    printf("         | |  _| | | | | | | | | |  _ \\\\ V /|  _|   | |\n");
    printf("         | |_| | |_| | |_| | |_| | |_) || | | |___  |_|\n");
    printf("          \\____|\\___/ \\___/|____/|____/ |_| |_____| (_)\033[m\n\n");
    printf("================================================================\n");
    printf("\n          |    Math park will await your return!    |    \n");
    printf("\n================================================================\n");
    printf("\n                      Exiting the game");
    for (int i = 0; i < 3; i++) {
                    printf("."); //Loading... effect
                    Sleep(500);  // Sleep for 500 milliseconds (0.5 seconds)
                }
                printf("\n");

}

/* 
    Displays the math board header.
    Precondition: None.
    @return void
*/
void mathBoardHeader() {
    printf("\n===========================================================================================\n");
    printf("\033[0;36m                  __  __    _  _____ _   _   ____   ___    _    ____  ____  \n");
    printf("                 |  \\/  |  / \\|_   _| | | | | __ ) / _ \\  / \\  |  _ \\|  _ \\ \n");
    printf("                 | |\\/| | / _ \\ | | | |_| | |  _ \\| | | |/ _ \\ | |_) | | | |\n");
    printf("                 | |  | |/ ___ \\| | |  _  | | |_) | |_| / ___ \\|  _ <| |_| |\n");
    printf("                 |_|  |_/_/   \\_\\_| |_| |_| |____/ \\___/_/   \\_\\_| \\_\\____/ \033[m\n\n");
}

/* 
    Displays the error input screen.
    Precondition: User provides any integer input other than 1, 2, or 3.
    @return void
*/
void errorInputScreen() {
    printf("\n================================================================\n");
    printf("\033[0;31m                _____ ____  ____   ___  ____    _\n");
    printf("               | ____|  _ \\|  _ \\ / _ \\|  _ \\  | |\n");
    printf("               |  _| | |_) | |_) | | | | |_) | | |\n");
    printf("               | |___|  _ <|  _ <| |_| |  _ <  |_|\n");
    printf("               |_____|_| \\_\\_| \\_\\\\___/|_| \\_\\ (_)\033[m\n\n");
    printf("================================================================\n\n");
    printf("          |\033[0;31m      Invalid input, please try again.     \033[m|         \n\n");
    printf("================================================================\n\n");
}

/* 
    Displays the victory screen.
    Precondition: None.
    @return void
*/
void victoryScreen() {
    printf("===========================================================================================\n");
    printf("\033[0;33m                         __     _____ ____ _____ ___  ______   __\n");
    printf("                         \\ \\   / /_ _/ ___|_   _/ _ \\|  _ \\ \\ / /\n");
    printf("                          \\ \\ / / | | |     | || | | | |_) \\ V / \n");
    printf("                           \\ V /  | | |___  | || |_| |  _ < | |\n");
    printf("                            \\_/  |___\\____| |_| \\___/|_| \\_\\|_|\033[m\n\n");
    printf("===========================================================================================\n\n");
}

/* 
    Displays the loser screen.
    Precondition: None.
    @return void
*/
void loserScreen() {
    printf("\n===========================================================================================\n");
    printf("\033[0;31m                  ____    _    __  __ _____    _____     _______ ____    _ \n");
    printf("                 / ___|  / \\  |  \\/  | ____|  / _ \\ \\   / / ____|  _ \\  | |\n");
    printf("                | |  _  / _ \\ | |\\/| |  _|   | | | \\ \\ / /|  _| | |_) | | |\n");
    printf("                | |_| |/ ___ \\| |  | | |___  | |_| |\\ V / | |___|  _ <  |_|\n");
    printf("                 \\____/_/   \\_\\_|  |_|_____|  \\___/  \\_/  |_____|_| \\_\\ (_)\033[m\n\n");
    printf("===========================================================================================\n");
}

/* 
    Displays the main menu options.
    Precondition: None.
    @return void
*/
void mainMenuOptions() {
    printf("                 |\033[0;32m     [1] Play Game          \033[m|                \n");
    printf("                 |\033[0;36m     [2] Instructions       \033[m|                \n");
    printf("                 |\033[0;31m     [3] Exit               \033[m|                \n\n");  
    printf("================================================================\n\n");
}

/* 
    Displays the home screen and returns the user's menu choice.
    Precondition: User provides input between 1 and 3.
    @return The menu option chosen by the user.
*/
int homeScreen() {
    int menuInput;
    mathParkHeader();
    mainMenuOptions();

    do {   
        printf("Enter your option: ");
        if (scanf("%d", &menuInput) != 1 || menuInput < 1 || menuInput > 3) {
            // Clear the input buffer
            while (getchar() != '\n');
            mathParkHeader();
            mainMenuOptions();
            printf("\033[0;31mInvalid input, please try again.\033[m\n\n");
        }
    } while (menuInput < 1 || menuInput > 3);

    return menuInput;
}

/* 
    Main function to run the game.
    Precondition: None.
    @return 0 on successful execution.
*/
int main() {
    int mainMenu;

    while (1) {
        mainMenu = homeScreen(); // Display the main menu and get user input

        switch (mainMenu) {
            case 1:
                printf("\nGame will start\n");
                startGame(); // Starts the game
                break;
            case 2:
                instructionScreen(); // Show instructions screen
                break; // Return to the loop to redisplay the menu
            case 3:
                endScreen(); //shows the good bye screen and exits the game
                return 0;
            default:
                clearScreen();
                errorInputScreen();
                printf("\nPress \"Enter\" to go back ");
                getchar(); 
                getchar(); // press enter to continue
                break;
        }
    }
    return 0;
}