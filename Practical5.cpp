
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int weight[n], profit[n];

    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    cout << "Enter profits of items: ";
    for (int i = 0; i < n; i++) {
        cin >> profit[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> W;

    int dp[n + 1][W + 1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            else if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    profit[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "Maximum Profit: " << dp[n][W] << endl;

    return 0;
}

