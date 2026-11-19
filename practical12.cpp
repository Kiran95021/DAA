
#include <iostream>
#include <climits>
using namespace std;

#define N 4

int tsp(int graph[N][N], int mask, int pos) {
    if (mask == (1 << N) - 1) {
        return graph[pos][0];
    }

    int ans = INT_MAX;

    for (int city = 0; city < N; city++) {
        if ((mask & (1 << city)) == 0) {
            int newAns = graph[pos][city] +
                         tsp(graph, mask | (1 << city), city);

            ans = min(ans, newAns);
        }
    }

    return ans;
}

int main() {
    int graph[N][N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int result = tsp(graph, 1, 0);

    cout << "Minimum travelling cost: " << result << endl;

    return 0;
}
