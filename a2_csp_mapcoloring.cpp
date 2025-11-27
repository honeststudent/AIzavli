#include <bits/stdc++.h>
using namespace std;

vector<string> order = {"SA", "WA", "NT", "Q", "NSW", "V", "T"};

map<string, vector<string>> adj;
map<string, vector<string>> domain;
map<string, string> assignment;

bool solve(int idx) {
    if (idx == order.size())
        return true;

    string region = order[idx];

    for (string c : domain[region]) {
        bool ok = true;

        // Check neighbors
        for (string n : adj[region]) {
            if (assignment.count(n) && assignment[n] == c) {
                ok = false;
                break;
            }
        }

        if (!ok) continue;

        assignment[region] = c;
        map<string, vector<string>> oldDomain = domain;

        // Forward checking
        for (string n : adj[region]) {
            auto &d = domain[n];
            d.erase(remove(d.begin(), d.end(), c), d.end());
        }

        if (solve(idx + 1))
            return true;

        // Backtrack
        assignment.erase(region);
        domain = oldDomain;
    }

    return false;
}

int main() {
    // Hardcoded adjacency (as before)
    adj["WA"]  = {"NT", "SA"};
    adj["NT"]  = {"WA", "SA", "Q"};
    adj["SA"]  = {"WA", "NT", "Q", "NSW", "V"};
    adj["Q"]   = {"NT", "SA", "NSW"};
    adj["NSW"] = {"Q", "SA", "V"};
    adj["V"]   = {"SA", "NSW"};
    adj["T"]   = {};

    vector<string> colors(3);

    cout << "Enter 3 available colors:\n";
    for (int i = 0; i < 3; i++) {
        cin >> colors[i];
    }

    // Initialize domains for each region
    for (string r : order)
        domain[r] = colors;

    if (solve(0)) {
        cout << "\n--- Solution ---\n";
        for (auto &p : assignment)
            cout << p.first << " -> " << p.second << "\n";
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
