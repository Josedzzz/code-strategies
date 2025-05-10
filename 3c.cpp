#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int knapsack(int W, vector<int> &weights, vector<int> &values, int n) {
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= n; i++) {
    for (int w = 1; w <= W; w++) {
      if (weights[i - 1] <= w) {
        dp[i][w] =
            max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }
  return dp[n][W];
}

int main() {
  vector<int> values = {2, 5, 10, 14, 15};
  vector<int> weights = {1, 3, 4, 5, 7};
  int W = 8;
  int n = values.size();
  int max_value = knapsack(W, weights, values, n);
  cout << "Valor máximo obtenido: " << max_value << endl;
  return 0;
}
