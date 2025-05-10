#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int from;
  int to;
  int cost;
};

bool compareByCost(const Edge &a, const Edge &b) { return a.cost < b.cost; }

class DisjointSet {
  vector<int> parent, rank;

public:
  DisjointSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++)
      parent[i] = i;
  }

  int find(int x) {
    if (parent[x] != x)
      parent[x] = find(parent[x]); // Path compression
    return parent[x];
  }

  bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY)
      return false;
    if (rank[rootX] < rank[rootY])
      parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
      parent[rootY] = rootX;
    else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }
    return true;
  }
};

int kruskal(int N, vector<Edge> &edges, vector<Edge> &mst) {
  sort(edges.begin(), edges.end(), compareByCost);
  DisjointSet ds(N);
  int totalCost = 0;
  for (const Edge &e : edges) {
    if (ds.unite(e.from, e.to)) {
      mst.push_back(e);
      totalCost += e.cost;
    }
  }
  return totalCost;
}

int main() {
  int N = 5; // number of municipalities (0 to 4)
  vector<Edge> connections = {
      {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
  vector<Edge> mst;
  int total = kruskal(N, connections, mst);
  cout << "Minimum cost to connect all municipalities: " << total << " COP"
       << endl;
  cout << "Connections used:" << endl;
  for (const Edge &e : mst) {
    cout << "Municipality " << e.from << " <-> " << e.to << " : " << e.cost
         << " COP" << endl;
  }
  return 0;
}
