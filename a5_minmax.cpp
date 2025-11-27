#include <bits/stdc++.h>
using namespace std;

const char PLAYER = 'X';
const char OPPONENT = 'O';
const char EMPTY = '_';

void printBoard(const vector<vector<char>>& board) {
    for (auto &row : board) {
        for (char c : row) cout << c << ' ';
        cout << '\n';
    }
    cout << '\n';
}

int evaluate(const vector<vector<char>>& b) {
    for (int row = 0; row < 3; ++row)
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == PLAYER) return 10;
            if (b[row][0] == OPPONENT) return -10;
        }

    for (int col = 0; col < 3; ++col)
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == PLAYER) return 10;
            if (b[0][col] == OPPONENT) return -10;
        }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == PLAYER) return 10;
        if (b[0][0] == OPPONENT) return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == PLAYER) return 10;
        if (b[0][2] == OPPONENT) return -10;
    }

    return 0;
}

bool isMovesLeft(const vector<vector<char>>& board) {
    for (auto &row : board)
        for (char c : row)
            if (c == EMPTY) return true;
    return false;
}

int minimax(vector<vector<char>>& board, int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);

    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = INT_MIN;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    int val = minimax(board, depth + 1, false, alpha, beta);
                    board[i][j] = EMPTY;
                    best = max(best, val);
                    alpha = max(alpha, best);
                    if (beta <= alpha) return best;
                }
        return best;
    }

    else {
        int best = INT_MAX;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board[i][j] == EMPTY) {
                    board[i][j] = OPPONENT;
                    int val = minimax(board, depth + 1, true, alpha, beta);
                    board[i][j] = EMPTY;
                    best = min(best, val);
                    beta = min(beta, best);
                    if (beta <= alpha) return best;
                }
        return best;
    }
}

pair<int,int> findBestMove(vector<vector<char>>& board) {
    int bestVal = INT_MIN;
    pair<int,int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER;
                int moveVal = minimax(board, 0, false, INT_MIN, INT_MAX);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMove = {i, j};
                }
            }

    return bestMove;
}

int main() {
    vector<vector<char>> board = {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

    cout << "Tic-Tac-Toe Minimax (AI = X, Human = O)\n";
    printBoard(board);

    while (true) {
        auto best = findBestMove(board);
        if (best.first == -1) {
            cout << "No moves left. It's a draw!\n";
            break;
        }

        board[best.first][best.second] = PLAYER;
        cout << "AI moves to: (" << best.first << ", " << best.second << ")\n";
        printBoard(board);

        if (evaluate(board) == 10) { cout << "AI (X) wins!\n"; break; }
        if (!isMovesLeft(board)) { cout << "Draw!\n"; break; }

        int r, c;
        cout << "Enter your move (row column): ";
        if (!(cin >> r >> c)) { cout << "Invalid input. Exiting.\n"; break; }

        if (r < 0 || r > 2 || c < 0 || c > 2 || board[r][c] != EMPTY) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[r][c] = OPPONENT;
        printBoard(board);

        if (evaluate(board) == -10) { cout << "Human (O) wins!\n"; break; }
        if (!isMovesLeft(board)) { cout << "Draw!\n"; break; }
    }

    return 0;
}
