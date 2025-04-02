#include <bits/stdc++.h>
using namespace std;

class RailwayNetwork {
private:
    unordered_map<string, vector<string>> connections;

    // Helper function to normalize case
    string toLower(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    // Depth Limit Search function (helper for iterative deepening)
    bool depthLimitSearch(string current, string target, int level, int limit, set<string>& visited) {
        if (level > limit) return false;

        cout << "Searching at Level " << level << ": " << current << endl;  // Debug line

        if (current == target) {
            cout << "Target " << target << " found at Level " << level << endl;  // Debug line
            return true;
        }

        visited.insert(current);
        for (auto& neighbor : connections[current]) {
            if (visited.find(neighbor) == visited.end()) {
                if (depthLimitSearch(neighbor, target, level + 1, limit, visited)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    RailwayNetwork() {
        int choice;
        string station1, station2;
        while (1) {
            cout << "\nEnter names of two connected stations: ";
            cin >> station1 >> station2;
            station1 = toLower(station1);
            station2 = toLower(station2);
            addConnection(station1, station2);
            cout << "Do you want to add another connection? (0/1): ";
            cin >> choice;
            if (choice == 0) break;
        }
    }

    void addConnection(string u, string v) {
        connections[u].push_back(v);
        connections[v].push_back(u);
    }

    // Breadth First Search
    void bfs(string start) {
        queue<pair<string, int>> q; // Pair of station and level
        set<string> visited;
        q.push({start, 0});
        visited.insert(start);

        cout << "\nBreadth First Search:\n";
        while (!q.empty()) {
            string station = q.front().first;
            int level = q.front().second;
            q.pop();

            cout << "Level " << level << ": " << station << endl;

            for (auto& neighbor : connections[station]) {
                if (visited.find(neighbor) == visited.end()) {
                    q.push({neighbor, level + 1});
                    visited.insert(neighbor);
                }
            }
        }
    }

    // Depth First Search
    void dfs(string current, int level, set<string>& visited) {
        visited.insert(current);
        cout << "Level " << level << ": " << current << endl;

        for (auto& neighbor : connections[current]) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, level + 1, visited);
            }
        }
    }

    void depthFirstSearch(string start) {
        set<string> visited;
        cout << "\nDepth First Search:\n";
        dfs(start, 0, visited);
    }

    // Iterative Deepening Search
    void iterativeDeepeningSearch(string start, string target, int maxDepth) {
        cout << "\nIterative Deepening Search:\n";
        for (int depth = 1; depth <= maxDepth; ++depth) {
            set<string> visited;
            cout << "Searching at depth " << depth << "..." << endl;
            if (depthLimitSearch(start, target, 0, depth, visited)) {
                cout << "Found " << target << " at depth " << depth << endl;
                return;
            }
        }
        cout << target << " is not reachable from " << start << " within the depth " << maxDepth << endl;
    }
};

int main() {
    RailwayNetwork rn;

    cout << "\n-----------------------Railway Network Connections--------------------------" << endl;

    int choice = 0;
    string startStation, targetStation;
    int depth;

    while (1) {
        cout << "\nChoose an option:\n";
        cout << "1. Breadth First Search\n";
        cout << "2. Depth First Search\n";
        cout << "3. Iterative Deepening Search\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the starting station: ";
                cin >> startStation;
                rn.bfs(startStation);
                break;
            case 2:
                cout << "Enter the starting station: ";
                cin >> startStation;
                rn.depthFirstSearch(startStation);
                break;
            case 3:
                cout << "Enter the starting station: ";
                cin >> startStation;
                cout << "Enter the target station: ";
                cin >> targetStation;
                cout << "Enter the maximum depth for search: ";
                cin >> depth;
                rn.iterativeDeepeningSearch(startStation, targetStation, depth);
                break;
            case 4:
                cout << "Exiting. Thank you for using the Railway Network system!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again!" << endl;
        }
    }
}