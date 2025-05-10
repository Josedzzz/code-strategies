#include <iostream>
#include <vector>
using namespace std;

int binomialTab(int n, int k) {
  vector<vector<int>> C(n + 1, vector<int>(k + 1, 0));
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= min(i, k); ++j) {
      if (j == 0 || j == i)
        C[i][j] = 1;
      else
        C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
  }
  return C[n][k];
}

int binomialMemo(int n, int k, vector<vector<int>> &memo) {
  if (k == 0 || k == n)
    return 1;
  if (memo[n][k] != -1)
    return memo[n][k];
  memo[n][k] = binomialMemo(n - 1, k - 1, memo) + binomialMemo(n - 1, k, memo);
  return memo[n][k];
}

int main() {
  int n = 4, k = 2;
  cout << "C(" << n << ", " << k << ") = " << binomialTab(n, k) << endl;
  vector<vector<int>> memo(n + 1, vector<int>(k + 1, -1));
  cout << "C(" << n << ", " << k << ") = " << binomialMemo(n, k, memo) << endl;
  return 0;
}
