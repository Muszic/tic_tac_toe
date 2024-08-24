#include <iostream>
using namespace std;

bool checkRowWin(char board[3][3]) {
    // Checks Horizontal Win
    for (int row = 0; row < 3; row++) {
        if (board[row][0] != '*' && board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            return true;
        }
    }
    return false;
}

bool checkColumnWin(char board[3][3]) {
    // Checks Vertical Win
    for (int col = 0; col < 3; col++) {
        if (board[0][col] != '*' && board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            return true;
        }
    }
    return false;
}

bool checkDiagonalWin1(char board[3][3]) {
    // Checks First Diagonal Win (Top-left to Bottom-right)
    return board[0][0] != '*' && board[0][0] == board[1][1] && board[1][1] == board[2][2];
}

bool checkDiagonalWin2(char board[3][3]) {
    // Checks Second Diagonal Win (Top-right to Bottom-left)
    return board[0][2] != '*' && board[0][2] == board[1][1] && board[1][1] == board[2][0];
}

void printBoard(char board[3][3]) {
    // Displays the complete board
    cout << "\n";
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            cout << board[row][col];
            if (col < 2) cout << " | ";
        }
        cout << "\n";
        if (row < 2) cout << "---------\n";
    }
}

bool isBoardFull(char board[3][3]) {
    // Checks if the board is completely filled
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == '*') {
                return false;
            }
        }
    }
    return true;
}

void placeMove(char board[3][3], int row, int col, int currentPlayer) {
    // Updates the board with the player's move
    board[row][col] = (currentPlayer == 0) ? 'O' : 'X';
}

bool isPositionFilled(char board[3][3], int row, int col) {
    // Check if the position is already occupied
    return (board[row][col] == 'X' || board[row][col] == 'O');
}

int main() {
    while (true) {
        char board[3][3] = { {'*', '*', '*'}, {'*', '*', '*'}, {'*', '*', '*'} };
        int currentPlayer = 1;
        string inputTurn;
        
        cout << "Player-1 will play with 'X' \n";
        cout << "Player-2 will play with 'O' \n\n";

        while (true) {
            cout << "Which player will start first (1 or 2): ";
            getline(cin, inputTurn);

            if (inputTurn == "1") {
                currentPlayer = 1;
                break;
            } else if (inputTurn == "2") {
                currentPlayer = 0;
                break;
            } else {
                cout << "Invalid Input! Please try again.\n\n";
            }
        }

        int row, col;
        while (true) {
            while (true) { // Checking whether the place is already filled or not
                cout << "\nEnter row number (1, 2, or 3): ";
                cin >> row;
                cout << "Enter column number (1, 2, or 3): ";
                cin >> col;
                if (row <= 0 || row >= 4) {
                    cout << "Invalid Row Number! Please try again.\n";
                } else if (col <= 0 || col >= 4) {
                    cout << "Invalid Column Number! Please try again.\n";
                } else if (isPositionFilled(board, row - 1, col - 1)) {
                    cout << "Position already filled! Please try again.\n";
                } else {
                    break;
                }
            }
            placeMove(board, row - 1, col - 1, currentPlayer); // Place player's move on the board
            printBoard(board); // Display the board

            if (checkColumnWin(board) || checkRowWin(board) || checkDiagonalWin1(board) || checkDiagonalWin2(board)) {
                cout << (currentPlayer == 0 ? "Player-2 wins!\n" : "Player-1 wins!\n");
                break;
            }
            if (isBoardFull(board)) {
                cout << "\n**** It's a tie! ****\n";
                cout << "The board is completely filled.\n";
                break;
            }
            currentPlayer = (currentPlayer + 1) % 2;
        }

        cin.ignore(); // To clear the newline character from the input buffer
        string playAgain;
        cout << "\n\nDo you want to play again? (y/n): ";
        getline(cin, playAgain);
        if (playAgain != "y" && playAgain != "Y") {
            break;
        }
        cout << endl;
    }
}
