#include<bits/stdc++.h>
using namespace std;

#define INF INT_MAX

class Graph {
    int V;
    vector<vector<int>> adjMatrix;
    vector<int> parent;

public:
    Graph(int vertices) : V(vertices) {
        adjMatrix.resize(V, vector<int>(V, INF));
        for (int i = 0; i < V; i++) {
            adjMatrix[i][i] = 0;
        }
        parent.resize(V);
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = adjMatrix[v][u] = weight;
    }

    void display() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (adjMatrix[i][j] == INF) {
                    cout << "  INF";
                } else {
                    cout << "  " << adjMatrix[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    void prims() {
        vector<int> key(V, INF);
        vector<bool> inMST(V, false);
        vector<int> parent(V, -1);
        key[0] = 0;
        for (int count = 0; count < V - 1; count++) {
            int u = -1;
            for (int v = 0; v < V; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }

            inMST[u] = true;
            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != INF && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }

        cout << "Edges in MST (Prim's Algorithm):" << endl;
        for (int i = 1; i < V; i++) {
            if (parent[i] != -1) {
                cout << parent[i] << " - " << i << " : " << adjMatrix[i][parent[i]] << endl;
            }
        }
    }

    void dijkstra(int start) {
        vector<int> dist(V, INF);
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);  // To store the parent of each vertex in the path
        dist[start] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = -1;
            for (int v = 0; v < V; v++) {
                if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                    u = v;
                }
            }

            visited[u] = true;

            // Update dist[] and parent[] for adjacent vertices of u
            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != INF && !visited[v] && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    parent[v] = u;  // Update parent to keep track of the path
                }
            }
        }

        // Printing the shortest distances and paths from the source vertex
        cout << "Shortest distances from vertex " << start << " (Dijkstra's Algorithm):" << endl;
        for (int i = 0; i < V; i++) {
            if (dist[i] == INF) {
                cout << "Vertex " << i << ": Unreachable" << endl;
            } else {
                cout << "Vertex " << i << ": " << dist[i] << " Path: ";
                vector<int> path;
                for (int v = i; v != -1; v = parent[v]) {
                    path.push_back(v);
                }
                reverse(path.begin(), path.end());  // Reverse the path to get the correct order
                for (int p : path) {
                    cout << p << " ";
                }
                cout << endl;
            }
        }
    }

    int find(int i) {
        while (parent[i] != i) {
            parent[i] = parent[parent[i]]; // Path compression
            i = parent[i];
        }
        return i;
    }

    void unionSets(int u, int v) {
        int uRoot = find(u);
        int vRoot = find(v);
        parent[uRoot] = vRoot;
    }

    void kruskal() {
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (adjMatrix[i][j] != INF) {
                    edges.push_back({adjMatrix[i][j], {i, j}});
                }
            }
        }
        sort(edges.begin(), edges.end());
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        int mstWeight = 0;
        cout << "Edges in MST (Kruskal's Algorithm):" << endl;
        for (auto edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int uRoot = find(u);
            int vRoot = find(v);

            if (uRoot != vRoot) {
                cout << u << " - " << v << " : " << edge.first << endl;
                mstWeight += edge.first;
                unionSets(uRoot, vRoot);
            }
        }

        cout << "Total weight of MST: " << mstWeight << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    Graph g(V+1);

    cout << "Enter the number of edges: ";
    cin >> E;

    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cout << "Enter edge (u v weight): ";
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    g.display();

    cout << "\nPrim's Algorithm:" << endl;
    g.prims();

    cout << "\nDijkstra's Algorithm:" << endl;
    int startVertex;
    cout << "Enter the start vertex for Dijkstra's Algorithm: ";
    cin >> startVertex;
    g.dijkstra(startVertex);

    cout << "\nKruskal's Algorithm:" << endl;
    g.kruskal();

    return 0;
} 