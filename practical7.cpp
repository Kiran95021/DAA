#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int minCoins(vector<int> &coins, int amount) {
    // DP array to store minimum coins required for each value
    vector<int> dp(amount + 1, INT_MAX);

    // Base case
    dp[0] = 0;

    // Build the DP table
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    // If amount cannot be formed
    if (dp[amount] == INT_MAX)
        return -1;

    return dp[amount];
}

int main() {
    int n, amount;

    cout << "Enter number of coin denominations: ";
    cin >> n;

    vector<int> coins(n);

    cout << "Enter coin denominations: ";
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    cout << "Enter amount to make change: ";
    cin >> amount;

    int result = minCoins(coins, amount);

    if (result == -1)
        cout << "Change cannot be made with given denominations." << endl;
    else
        cout << "Minimum number of coins required = " << result << endl;

    return 0;
}
