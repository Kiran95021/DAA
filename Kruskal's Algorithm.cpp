#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int parent[100];

int find(int x) {
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void unionSet(int u, int v) {
    u = find(u);
    v = find(v);

    if (u != v)
        parent[v] = u;
}

int main() {
    int n, e;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<Edge> edges(e);

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // Initialize parent
    for (int i = 0; i < n; i++)
        parent[i] = i;

    // Sort edges according to weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    int mstWeight = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    int count = 0;

    for (auto edge : edges) {
        int u = edge.u;
        int v = edge.v;

        // Check whether adding edge creates a cycle
        if (find(u) != find(v)) {
            cout << u << " - " << v << " : " << edge.w << endl;

            mstWeight += edge.w;
            unionSet(u, v);

            count++;

            if (count == n - 1)
                break;
        }
    }

    cout << "Minimum Cost = " << mstWeight << endl;

    return 0;
}
