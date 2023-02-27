#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

int costMST(vector<pair<int, int>> graph[], int numVertices) {

  int sumCost = 0;

  // Create a priority queue
  priority_queue<pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>>> queue;

  vector<int> costs(numVertices, INT_MAX);
  vector<bool> visited(numVertices, false);

  int u = 0; // start node
  queue.push(make_pair(0, u));
  costs[u] = 0;

  while (!queue.empty()){
    // Traverse all adjacent nodes of u 
    for (auto x : graph[u]) {

      int cost = x.first;
      int v = x.second;

      if (!visited[v] && cost < costs[v]) {
        costs[v] = cost;
        queue.push(make_pair(cost, v));
      }
    }

    u = queue.top().second;

    if (!visited[u]) {
      visited[u] = true;
      sumCost+= queue.top().first;
    }
    queue.pop();
  }

  return sumCost;
}

int main() {

  int numVertices = 40;
  ifstream fs("p107_network.txt");

  vector<pair<int, int> > graph[numVertices];
  string line, field;

  int sumCost = 0;

  for (int i = 0; getline(fs, line); i++) {

    istringstream s(line);

    for (int j = 0; getline(s, field, ','); j++) {

      if ("-" != field) {
        int cost = atoi(field.c_str());
        graph[i].push_back(make_pair(cost, j));
        sumCost+= cost;
      }
    }
  }
  fs.close();

  cout << sumCost / 2 - costMST(graph, numVertices) << endl;
}