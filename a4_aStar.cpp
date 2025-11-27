#include <bits/stdc++.h>
using namespace std;

const int ROW = 9;
const int COL = 10;

// Check valid cell
bool isValid(int r, int c) {
    return (r >= 0 && r < ROW && c >= 0 && c < COL);
}

// Check if cell is not blocked
bool isFree(vector<vector<int>>& grid, int r, int c) {
    return grid[r][c] == 1;
}

// Heuristic (Manhattan distance) – easy to explain
int h(int r, int c, int dr, int dc) {
    return abs(r - dr) + abs(c - dc);
}

// To print path
void printPath(map<pair<int,int>, pair<int,int>>& parent, pair<int,int> dest) {
    vector<pair<int,int>> path;
    auto cur = dest;

    while (parent[cur] != cur) {
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back(cur);
    reverse(path.begin(), path.end());

    cout << "\nPath found:\n";
    for (auto &p : path)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << "\n";
}

void aStar(vector<vector<int>>& grid, pair<int,int> src, pair<int,int> dest) {

    // Priority queue: (f-score, (row, col))
    priority_queue<
        pair<int, pair<int,int>>,
        vector<pair<int, pair<int,int>>>,
        greater<pair<int, pair<int,int>>>
    > pq;

    // g-cost (distance so far)
    vector<vector<int>> g(ROW, vector<int>(COL, INT_MAX));

    // parent for path reconstruction
    map<pair<int,int>, pair<int,int>> parent;

    // Start
    g[src.first][src.second] = 0;
    pq.push({0, src});
    parent[src] = src;

    // 4 directions (easier to explain)
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};

    while (!pq.empty()) {
        auto best = pq.top(); 
        pq.pop();

        int r = best.second.first;
        int c = best.second.second;

        // Reached destination?
        if (r == dest.first && c == dest.second) {
            printPath(parent, dest);
            return;
        }

        // Explore neighbors
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (isValid(nr, nc) && isFree(grid, nr, nc)) {
                int new_g = g[r][c] + 1;
                int f = new_g + h(nr, nc, dest.first, dest.second);

                if (new_g < g[nr][nc]) {
                    g[nr][nc] = new_g;
                    parent[{nr,nc}] = {r,c};
                    pq.push({f, {nr, nc}});
                }
            }
        }
    }

    cout << "No path found.\n";
}

int main() {
    vector<vector<int>> grid = {
        {1,0,1,1,1,1,0,1,1,1},
        {1,1,1,0,1,1,1,0,1,1},
        {1,1,1,0,1,1,0,1,0,1},
        {0,0,1,0,1,0,0,0,0,1},
        {1,1,1,0,1,1,1,0,1,0},
        {1,0,1,1,1,1,0,1,0,0},
        {1,0,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,1},
        {1,1,1,0,0,0,1,0,0,1}
    };

    pair<int,int> src = {8,0};
    pair<int,int> dest = {0,0};

    aStar(grid, src, dest);
    return 0;
}
