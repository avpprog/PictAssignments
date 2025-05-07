#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<stack>
#include<map>
using namespace std;

struct State {
    vector<vector<int>> board;
    int row;
    int cost;
    vector<int> vcols;
    vector<int> vs1;
    vector<int> vs2;

    State(int N) : row(0), cost(0), 
        board(N, vector<int>(N, 0)), 
        vcols(N, 0), vs1(2 * N, 0), vs2(2 * N, 0) {}

    bool operator<(const State &other) const {
        return this->cost > other.cost; // for min-heap
    }
};

class branchnbound {
public:
    int n;

    branchnbound(int s) {
        n = s;
    }

    int heuristic(const State& s) {
        int safepos = 0;
        for (int i = s.row; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!s.vcols[j] && !s.vs1[i + j] && !s.vs2[n + j - i])
                    safepos++;
            }
        }
        return n * n - safepos; // fewer safe positions = higher cost
    }

    void solve() {
        priority_queue<State> pq;
        pq.push(State(n));

        while (!pq.empty()) {
            State s = pq.top();
            pq.pop();

            int crow = s.row;

            if (crow == n) {
                printBoard(s.board);
                continue;
            }

            for (int i = 0; i < n; i++) {
                if (!s.vcols[i] && !s.vs1[crow + i] && !s.vs2[n + i - crow]) {
                    State newState = s;
                    newState.board[crow][i] = 1;
                    newState.vcols[i] = 1;
                    newState.vs1[crow + i] = 1;
                    newState.vs2[n + i - crow] = 1;
                    newState.row = crow + 1;
                    newState.cost = heuristic(newState);
                    pq.push(newState);
                }
            }
        }
    }

    void printBoard(const vector<vector<int>>& board) {
        for (auto row : board) {
            for (int x : row) cout << (x ? "Q " : ". ");
            cout << "\n";
        }
        cout << "------------------\n";
    }
};

int main() {
    int N = 8;
    branchnbound obj(N);
    obj.solve();
    return 0;
}

