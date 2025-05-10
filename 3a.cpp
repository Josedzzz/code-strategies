#include <iostream>
#include <vector>

using namespace std;

int lucasTabulation(int n) {
  if (n == 0)
    return 2;
  if (n == 1)
    return 1;
  vector<int> lucas(n + 1);
  lucas[0] = 2;
  lucas[1] = 1;

  for (int i = 2; i <= n; ++i) {
    lucas[i] = lucas[i - 1] + lucas[i - 2];
  }
  return lucas[n];
}

int lucasMemo(int n, vector<int> &memo) {
  if (n == 0)
    return 2;
  if (n == 1)
    return 1;
  if (memo[n] != -1)
    return memo[n];
  memo[n] = lucasMemo(n - 1, memo) + lucasMemo(n - 2, memo);
  return memo[n];
}

int main() {
  int n;
  cout << "Enter a number n to compute Lucas(n): ";
  cin >> n;
  cout << "Lucas(" << n << ") = " << lucasTabulation(n) << endl;
  vector<int> memo(n + 1, -1);
  cout << "Lucas(" << n << ") = " << lucasMemo(n, memo) << endl;
  return 0;
}
