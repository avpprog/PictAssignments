#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Object {
    int width, height, id;
    bool placed;
    char symbol;
};

struct Position {
    int x, y;
};

struct State {
    vector<vector<char>> room;
    vector<Object> objects;
    int usedArea;

    // Heuristic: remaining empty space
    int heuristic(int roomArea) const {
        return roomArea - usedArea;
    }

    bool operator>(const State& other) const {
        return heuristic(room.size() * room[0].size()) > other.heuristic(other.room.size() * other.room[0].size());
    }
};

// Check if object fits in position
bool canPlace(const vector<vector<char>>& room, const Object& obj, int x, int y) {
    int h = room.size();
    int w = room[0].size();

    if (x + obj.height > h || y + obj.width > w) return false;

    for (int i = x; i < x + obj.height; ++i)
        for (int j = y; j < y + obj.width; ++j)
            if (room[i][j] != '.') return false;

    return true;
}

// Place object in room
void placeObject(vector<vector<char>>& room, const Object& obj, int x, int y) {
    for (int i = x; i < x + obj.height; ++i)
        for (int j = y; j < y + obj.width; ++j)
            room[i][j] = obj.symbol;
}

// A* Placement
void arrangeObjects(int rows, int cols, vector<Object>& objects) {
    priority_queue<State, vector<State>, greater<State>> pq;

    vector<vector<char>> emptyRoom(rows, vector<char>(cols, '.'));
    State start = {emptyRoom, objects, 0};
    pq.push(start);

    while (!pq.empty()) {
        State current = pq.top(); pq.pop();

        bool allPlaced = true;
        for (const auto& obj : current.objects) {
            if (!obj.placed) {
                allPlaced = false;
                break;
            }
        }

        if (allPlaced) {
            cout << "\nFinal Room Arrangement:\n";
            for (const auto& row : current.room) {
                for (char c : row)
                    cout << c << ' ';
                cout << '\n';
            }
            return;
        }

        for (int idx = 0; idx < current.objects.size(); ++idx) {
            if (current.objects[idx].placed) continue;
            Object obj = current.objects[idx];

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (canPlace(current.room, obj, i, j)) {
                        State next = current;
                        placeObject(next.room, obj, i, j);
                        next.objects[idx].placed = true;
                        next.usedArea += obj.width * obj.height;
                        pq.push(next);
                        goto next_object; // break nested loops after placing one instance
                    }
                }
            }
        next_object:;
        }
    }

    cout << "Could not place all objects.\n";
}

// Main menu
int main() {
    int roomRows, roomCols;
    vector<Object> objects;
    int choice;

    do {
        cout << "\n--- Object Arrangement Menu ---\n";
        cout << "1. Enter room dimensions\n";
        cout << "2. Enter rectangular objects\n";
        cout << "3. Enter square objects\n";
        cout << "4. Arrange objects using A*\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter room rows and columns: ";
            cin >> roomRows >> roomCols;
            break;

        case 2: {
            int n;
            cout << "Enter number of rectangular objects (max 5): ";
            cin >> n;
            for (int i = 0; i < n; ++i) {
                Object obj;
                obj.id = i;
                obj.placed = false;
                cout << "Enter width and height for rectangle " << i + 1 << ": ";
                cin >> obj.width >> obj.height;
                obj.symbol = 'R' + i;
                objects.push_back(obj);
            }
            break;
        }

        case 3: {
            int n;
            cout << "Enter number of square objects (max 4): ";
            cin >> n;
            for (int i = 0; i < n; ++i) {
                Object obj;
                obj.id = i;
                obj.placed = false;
                cout << "Enter side length for square " << i + 1 << ": ";
                cin >> obj.width;
                obj.height = obj.width;
                obj.symbol = 'S' + i;
                objects.push_back(obj);
            }
            break;
        }

        case 4:
            arrangeObjects(roomRows, roomCols, objects);
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}