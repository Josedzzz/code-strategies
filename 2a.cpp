#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Bill {
  int value;
  int availableQuantity;
};

bool compareByHigherDenomination(const Bill &a, const Bill &b) {
  return a.value > b.value;
}

bool dispenseMoney(int requestedAmount, vector<Bill> &bills) {
  if (requestedAmount % 10000 != 0) {
    cout << "The requested amount must be divisible by 10000." << endl;
    return false;
  }
  vector<int> dispensedBills(bills.size(), 0);
  for (int i = 0; i < bills.size(); ++i) {
    int maxBills = requestedAmount / bills[i].value;
    int toDispense = min(maxBills, bills[i].availableQuantity);
    dispensedBills[i] = toDispense;
    requestedAmount -= toDispense * bills[i].value;
  }
  if (requestedAmount != 0) {
    cout << "Insufficient availability to dispense the requested amount."
         << endl;
    return false;
  }
  cout << "Bills dispensed:" << endl;
  for (int i = 0; i < bills.size(); ++i) {
    cout << "Bills of " << bills[i].value << ": " << dispensedBills[i] << endl;
  }
  return true;
}

int main() {
  vector<Bill> bills = {{10000, 300}, {20000, 200}, {50000, 100}, {100000, 50}};
  sort(bills.begin(), bills.end(), compareByHigherDenomination);
  int amount;
  cout << "Enter the amount of money to withdraw: ";
  cin >> amount;
  dispenseMoney(amount, bills);
  return 0;
}
