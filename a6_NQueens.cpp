#include <bits/stdc++.h>
using namespace std;

// Function to print the chessboard
void printBoard(vector<vector<int>> &board, int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << (board[i][j] == 1 ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

// Check if placing queen at (row, col) is safe
bool isSafe(vector<vector<int>> &board, int row, int col, int n) {
    // Check column above
    for(int i=0; i<row; i++) {
        if(board[i][col] == 1)
            return false;
    }

    // Check upper left diagonal
    for(int i=row-1, j=col-1; i>=0 && j>=0; i--, j--) {
        if(board[i][j] == 1)
            return false;
    }

    // Check upper right diagonal
    for(int i=row-1, j=col+1; i>=0 && j<n; i--, j++) {
        if(board[i][j] == 1)
            return false;
    }

    return true;
}

// Recursive function to solve N-Queens
void solveNQueens(vector<vector<int>> &board, int row, int n) {
    if(row == n) {
        printBoard(board, n);
        return;
    }

    for(int col=0; col<n; col++) {
        if(isSafe(board, row, col, n)) {
            board[row][col] = 1; // Place queen
            solveNQueens(board, row+1, n);
            board[row][col] = 0; // Backtrack
        }
    }
}

int main() {
    int n;
    cout << "Enter value of N: ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));

    solveNQueens(board, 0, n);

    return 0;
}
