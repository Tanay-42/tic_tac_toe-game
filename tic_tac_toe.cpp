#include <iostream>
#include <cstdlib>
using namespace std;

char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
int currentPlayer = 1;
char mark;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayBoard() {
    clearScreen();
    cout << "\n  Tic-Tac-Toe Game\n";
    cout << "Player 1 (X)  -  Player 2 (O)\n\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << " ";
            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) cout << "-----------\n";
    }
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    return false;
}

bool isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void resetBoard() {
    char boardReset[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
    copy(&boardReset[0][0], &boardReset[0][0] + 9, &board[0][0]);
}

void playerMove() {
    int choice;
    bool validMove = false;
    while (!validMove) {
        cout << "\nPlayer " << currentPlayer << "'s turn. Enter a position (1-9): ";
        cin >> choice;

        if (choice < 1 || choice > 9) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Position already taken! Try again.\n";
        } else {
            board[row][col] = mark;
            validMove = true;
        }
    }
}

int main() {
    char playAgain;
    do {
        resetBoard();
        currentPlayer = 1;
        
        while (true) {
            displayBoard();
            mark = (currentPlayer == 1) ? 'X' : 'O';
            playerMove();
            if (checkWin()) {
                displayBoard();
                cout << "\nPlayer " << currentPlayer << " wins!\n";
                break;
            }
            if (isDraw()) {
                displayBoard();
                cout << "\nIt's a draw!\n";
                break;
            }
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
        
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    
    return 0;
}
