#include <iostream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

set<string> left_side;
set<string> right_side;
string farmer_side = "left";

void initialize_game() {
    left_side.insert("farmer");
    left_side.insert("wolf");
    left_side.insert("goat");
    left_side.insert("cabbage");
}

bool is_safe(const set<string>& side) {
    // Unsafe if (wolf and goat together without farmer) OR (goat and cabbage together without farmer)
    bool has_farmer = side.count("farmer") > 0;
    bool has_wolf = side.count("wolf") > 0;
    bool has_goat = side.count("goat") > 0;
    bool has_cabbage = side.count("cabbage") > 0;

    if (!has_farmer && has_wolf && has_goat) return false;
    if (!has_farmer && has_goat && has_cabbage) return false;
    return true;
}

string move_item(const string& item_in) {
    string item = item_in;
    bool none = (item == "none");

    if (farmer_side == "left") {
        if (!none) {
            if (!left_side.count(item)) return "Invalid move!";
            left_side.erase(item);
            right_side.insert(item);
        }
        farmer_side = "right";
        left_side.erase("farmer");
        right_side.insert("farmer");
    } else { // farmer on right
        if (!none) {
            if (!right_side.count(item)) return "Invalid move!";
            right_side.erase(item);
            left_side.insert(item);
        }
        farmer_side = "left";
        right_side.erase("farmer");
        left_side.insert("farmer");
    }

    if (!is_safe(left_side) || !is_safe(right_side)) {
        return "Move not allowed! Items left alone unsafely.";
    }
    return "Move successful!\n";
}

void display_state() {
    cout << "Left Side: ";
    if (left_side.empty()) {
        cout << "(empty)";
    } else {
        bool first = true;
        for (const auto& s : left_side) {
            if (!first) cout << ", ";
            cout << s;
            first = false;
        }
    }
    cout << endl;

    cout << "Right Side: ";
    if (right_side.empty()) {
        cout << "(empty)";
    } else {
        bool first = true;
        for (const auto& s : right_side) {
            if (!first) cout << ", ";
            cout << s;
            first = false;
        }
    }
    cout << endl;

    cout << "Farmer is on the " << farmer_side << " side." << endl;
}

bool is_game_won() {
    return left_side.empty();
}

int main() {
    initialize_game();
    cout << "Welcome to the Wolf, Goat, and Cabbage game!" << endl << endl;
    display_state();

    while (!is_game_won()) {
        cout << endl;
        cout << "What do you want to move? (wolf, goat, cabbage, none): ";
        string move_input;
        if (!(cin >> move_input)) break;
        transform(move_input.begin(), move_input.end(), move_input.begin(), ::tolower);

        if (move_input != "none" && move_input != "wolf" && move_input != "goat" && move_input != "cabbage") {
            cout << "Invalid item! Please choose wolf, goat, cabbage, or none." << endl;
            continue;
        }

        string result = move_item(move_input);
        cout << result << endl;
        display_state();

        if (result.rfind("Move not allowed", 0) == 0) { // starts with
            break;
        }
    }

    if (is_game_won()) {
        cout << "Congratulations! You won the game!" << endl;
    } else {
        cout << "Game over! Try again." << endl;
    }

    return 0;
}
