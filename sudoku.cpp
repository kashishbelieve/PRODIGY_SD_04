#include <iostream>
using namespace std;

#define N 9

// Function to check if placing num in board[row][col] is safe
bool isSafe(int board[N][N], int row, int col, int num) {
    // Check if the number is already in the row
    for (int x = 0; x < N; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    // Check if the number is already in the column
    for (int x = 0; x < N; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    // Check if the number is in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int board[N][N]) {
    int row, col;
    bool isEmpty = false;

    // Find an empty space (denoted by 0)
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // If there are no empty spaces, the puzzle is solved
    if (!isEmpty) {
        return true;
    }

    // Try placing digits 1-9 in the empty space
    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            // Place the number
            board[row][col] = num;

            // Recursively try to solve the rest of the board
            if (solveSudoku(board)) {
                return true;
            }

            // If the solution is not valid, reset the cell and backtrack
            board[row][col] = 0;
        }
    }

    // If no valid number is found, return false
    return false;
}

// Function to print the Sudoku grid
void printSudoku(int board[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Example input: Unsolved Sudoku puzzle
    int sudokuGrid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Sudoku puzzle to solve:" << endl;
    printSudoku(sudokuGrid);
    cout << "\nSolving...\n" << endl;

    if (solveSudoku(sudokuGrid)) {
        cout << "Sudoku puzzle solved:" << endl;
        printSudoku(sudokuGrid);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}

