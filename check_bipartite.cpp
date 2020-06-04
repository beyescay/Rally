// Check if a given graph is bipartite or not

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int IsBipartite(vector<vector<int>>& adj) {

  const int max_val = adj.size() + 1;
  vector<int> dist(adj.size(), max_val);
  queue<int> q;

  for (int i = 0; i < adj.size(); ++i) {

    if (dist[i] == max_val) {
      q.push(i);
      dist[i] = 0;

      while(!q.empty()) {
        auto curr_node = q.front();
        q.pop();

        for(auto& next_node : adj[curr_node]) {

          if (dist[next_node] == max_val){
            q.push(next_node);
            dist[next_node] = dist[curr_node] + 1;
          }

          if (dist[next_node] == dist[curr_node]) {
            return 0;
          }

        }
      }
    }

  }

  return 1;

}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  if (IsBipartite(adj)) {
    std::cout << "Graph is bipartite" << std::endl;
  }
  else {
    std::cout << "Graph is not bipartite" << std::endl;
  }
}
