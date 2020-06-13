// Detect negative cycle in a weighted graph using Bellman-Ford algorithm
#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {

  int max_cost = 0;

  for(auto& weights : cost) {
    for(auto& weight : weights) {
      max_cost = std::max(max_cost, max_cost+weight);
    }
  }

  vector<int> dist(adj.size(), max_cost);
  dist[0] = 0;

  for(int count = 0; count < adj.size()+1; ++count) {

    for(int i = 0; i < adj.size(); ++i) {

      i = i%adj.size();

      auto& edges = adj[i];

      for(int j = 0; j < edges.size(); ++j) {
        auto& neighbor = edges[j];
        auto new_cost = dist[i] + cost[i][j];

        if (dist[neighbor] > new_cost) {
          dist[neighbor] = new_cost;

          if (count == adj.size()) {
            return 1;
          }

        }

      }

    }

  }

  return 0;
}

int main() {

  int n, m;
  std::cin >> n >> m;

  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());

  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }

  std::cout << negative_cycle(adj, cost);
}
