#include <bits/stdc++.h>
using namespace std;

// Print the board with queens
void printSolution(vector<vector<int>>& board, int N, int solutionCount) {
    cout << "\nSolution " << solutionCount << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << (board[i][j] == 1 ? "Q " : ". ");
        cout << endl;
    }
}

// Check if placing queen is safe
bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
    for (int i = 0; i < row; i++)
        if (board[i][col] == 1) return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1) return false;

    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j] == 1) return false;

    return true;
}

// Recursive utility to solve N-Queens
void solveNQueensUtil(vector<vector<int>>& board, int row, int N, int &solutionCount) {
    if (row >= N) {
        solutionCount++;
        printSolution(board, N, solutionCount);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1;
            solveNQueensUtil(board, row + 1, N, solutionCount);
            board[row][col] = 0; // backtrack
        }
    }
}

// Solve N-Queens
void solveNQueens(int N) {
    vector<vector<int>> board(N, vector<int>(N, 0));
    int solutionCount = 0;
    solveNQueensUtil(board, 0, N, solutionCount);

    if (solutionCount == 0)
        cout << "No solutions exist for N = " << N << endl;
    else
        cout << "\n Total solutions for N = " << N << ": " << solutionCount << endl;
}

int main() {
    int N;
    cout << "Enter the size of the chessboard (N): ";
    cin >> N;

    solveNQueens(N);
    return 0;
}
