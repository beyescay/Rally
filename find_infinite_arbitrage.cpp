// Detect all nodes reachable from negative cycle nodes, all reachable nodes,
// non-reachable nodes in a weighted graph using Bellman ford algorithm.

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {

  distance[s] = 0;
  reachable[s] = 1;
  queue<int> q;

  for(int count = 0; count < adj.size()+1; ++count) {

    for (int i = 0; i < adj.size(); ++i) {

      auto& edges = adj[i];

      for(int j = 0; j < edges.size(); ++j) {

        auto& neighbor = edges[j]
        auto new_cost = distance[i] + cost[i][j];

        if (distance[i] != std::numeric_limits<long long>::max() && distance[neighbor] > new_cost) {

          distance[neighbor] = new_cost;
          reachable[neighbor] = 1;

          if (count == adj.size()) {
            q.push(neighbor);
          }

        }

      }

    }

  }

  vector<int> visited(adj.size(), 0);

  while(!q.empty()) {

    auto curr = q.front();
    shortest[curr] = 0;
    q.pop();

    for(auto& neighbor : adj[curr]) {

      if(visited[neighbor] == 0) {
        q.push(neighbor);
        visited[neighbor] = 1;
      }

    }

  }

}

int main() {

  int n, m, s;
  std::cin >> n >> m;

  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());

  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }

  std::cin >> s;
  s--;

  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);

  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
