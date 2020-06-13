// Dijkstra's algorithm implementation. Return the min dist between two vertices of a weighted graph

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {

  vector<int> dist(adj.size(), -1);
  dist[s] = 0;

  auto compare = [&](int a, int b){ return dist[a] > dist[b];};
  priority_queue<int, vector<int>, decltype(compare)> priority_q(compare);

  priority_q.push(s);

  while(!priority_q.empty()) {

    auto curr = priority_q.top();

    if (curr == t) {
      return dist[curr];
    }

    priority_q.pop();

    auto& edges = adj[curr];
    for(int idx = 0; idx < edges.size(); ++idx) {

      auto to_node = edges[idx];
      auto new_cost = dist[curr] + cost[curr][idx];

      if (dist[to_node] == -1 || dist[to_node] > new_cost) {
        dist[edges[idx]] = new_cost;
        priority_q.push(to_node);
      }

    }

  }

  return -1;
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

  int s, t;
  std::cin >> s >> t;
  s--, t--;

  std::cout << distance(adj, cost, s, t);
}
