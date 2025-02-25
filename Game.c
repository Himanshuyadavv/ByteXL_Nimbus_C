#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR "cls"      // Windows
#else
    #define CLEAR "clear"    // Linux/macOS
#endif

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"

char board[3][3];  // 3x3 game board

// Function to initialize the board with empty cells
void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

// Function to display the board with colorful grid
void displayBoard() {
    printf("\n  %sTic-Tac-Toe%s\n\n", MAGENTA, RESET);
    printf("    %s1   2   3%s\n", YELLOW, RESET);
    printf("%s  -----------------\n", GREEN);

    for (int i = 0; i < 3; i++) {
        printf("%s%d %s|", YELLOW, i + 1, RESET);
        for (int j = 0; j < 3; j++) {
            char cell = board[i][j];
            if (cell == 'X')
                printf(" %s X %s|", RED, RESET);
            else if (cell == 'O')
                printf(" %s O %s|", BLUE, RESET);
            else
                printf("   |");
        }
        printf("\n%s  -----------------%s\n", GREEN, RESET);
    }
}

// Function to check if a player has won
char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];  // Row win
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];  // Column win
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    return ' ';  // No winner yet
}

// Function to check if the board is full
int isBoardFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

// Function to play the game
void playGame() {
    int row, col, turn = 1;
    char currentPlayer;

    while (1) {
        currentPlayer = (turn % 2 == 1) ? 'X' : 'O';
        displayBoard();

        printf("\n🎮 %sPlayer %c's Turn%s (Enter row and column [1-3]): ", (currentPlayer == 'X') ? RED : BLUE, currentPlayer, RESET);
        if (scanf("%d %d", &row, &col) != 2) {
            printf("\n❌ %sInvalid input! Please enter two numbers.%s\n", YELLOW, RESET);
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }

        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            printf("\n⚠️ %sInvalid move! Cell occupied or out of bounds. Try again.%s\n", CYAN, RESET);
            continue;
        }

        board[row - 1][col - 1] = currentPlayer;

        if (checkWinner() != ' ') {
            displayBoard();
            printf("\n🏆 %sCongratulations! Player %c wins! 🎉%s\n", GREEN, currentPlayer, RESET);
            break;
        }

        if (isBoardFull()) {
            displayBoard();
            printf("\n🤝 %sIt's a draw! Well played both!%s\n", CYAN, RESET);
            break;
        }

        turn++;  // Switch player
    }
}

int main() {
    char playAgain;

    do {
        system(CLEAR);  // Cross-platform clear screen
        initializeBoard();
        printf("\n🎲 %sWelcome to Colorful Tic-Tac-Toe! 🎨%s\n", CYAN, RESET);
        playGame();

        printf("\n🔁 %sDo you want to play again? (y/n): %s", YELLOW, RESET);
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\n🚀 %sThanks for playing! Goodbye! 👋%s\n", MAGENTA, RESET);
    return 0;
}
