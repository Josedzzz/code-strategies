#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Item {
  int id;
  double weight;
  double value;
  double valuePerWeight() const { return value / weight; }
};

void showSelection(const vector<Item> &items, const vector<double> &x,
                   const string &criterion) {
  double totalValue = 0;
  double totalWeight = 0;
  cout << "\n--- Selection by " << criterion << " ---\n";
  cout << fixed << setprecision(2);
  for (int i = 0; i < items.size(); ++i) {
    if (x[i] > 0) {
      cout << "Item " << items[i].id << ": " << (x[i] * items[i].weight)
           << "kg (x = " << x[i] << "), Value = " << (x[i] * items[i].value)
           << "\n";
      totalValue += x[i] * items[i].value;
      totalWeight += x[i] * items[i].weight;
    }
  }
  cout << "Total value: " << totalValue << "\n";
  cout << "Total weight: " << totalWeight << "\n";
}

vector<double> fractionalKnapsack(vector<Item> items, double maxCapacity,
                                  int criterion) {
  switch (criterion) {
  case 1: // By value
    sort(items.begin(), items.end(),
         [](const Item &a, const Item &b) { return a.value > b.value; });
    break;
  case 2: // By weight (smallest first)
    sort(items.begin(), items.end(),
         [](const Item &a, const Item &b) { return a.weight < b.weight; });
    break;
  case 3: // By value/weight
    sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
      return a.valuePerWeight() > b.valuePerWeight();
    });
    break;
  }
  vector<double> x(items.size(), 0);
  double currentWeight = 0;
  for (int i = 0; i < items.size(); ++i) {
    if (currentWeight + items[i].weight <= maxCapacity) {
      x[i] = 1.0;
      currentWeight += items[i].weight;
    } else {
      x[i] = (maxCapacity - currentWeight) / items[i].weight;
      currentWeight = maxCapacity;
      break;
    }
  }
  showSelection(items, x,
                criterion == 1 ? "Value"
                               : (criterion == 2 ? "Weight" : "Value/Weight"));
  return x;
}

int main() {
  double maxCapacity;
  int n;
  cout << "Enter the maximum container capacity: ";
  cin >> maxCapacity;
  cout << "Enter the number of items: ";
  cin >> n;
  vector<Item> items(n);
  for (int i = 0; i < n; ++i) {
    cout << "Item " << i + 1 << ":\n";
    cout << "  Weight: ";
    cin >> items[i].weight;
    cout << "  Value: ";
    cin >> items[i].value;
    items[i].id = i + 1;
  }
  fractionalKnapsack(items, maxCapacity, 1); // By value
  fractionalKnapsack(items, maxCapacity, 2); // By weight
  fractionalKnapsack(items, maxCapacity, 3); // By value/weight
  return 0;
}
