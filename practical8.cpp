#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);      // Remove for directed graph
    }

    void DFSUtil(int node, vector<bool> &visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor])
                DFSUtil(neighbor, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        DFSUtil(start, visited);
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.emplace(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.emplace(neighbor);
                }
            }
        }
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    auto startDFS = high_resolution_clock::now();

    cout << "\nDFS Traversal: ";
    g.DFS(start);

    auto endDFS = high_resolution_clock::now();

    auto startBFS = high_resolution_clock::now();

    cout << "\n\nBFS Traversal: ";
    g.BFS(start);

    auto endBFS = high_resolution_clock::now();

    cout << "\n\nDFS Time : "
         << duration_cast<nanoseconds>(endDFS - startDFS).count()
         << " ns";

    cout << "\nBFS Time : "
         << duration_cast<nanoseconds>(endBFS - startBFS).count()
         << " ns";

    return 0;
}
