#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

bool bfs(vector<vector<int>>& graph, int source, int sink, vector<int>& parent) {
    int n = graph.size();
    vector<bool> visited(n, false);
    visited[source] = true;

    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graph[u][v] > 0) {
                q.push(v);
                visited[v] = true;
                parent[v] = u;

                if (v == sink) {
                    return true;
                }
            }
        }
    }

    return false;
}

int edmonds_karp(vector<vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    vector<int> parent(n, -1);
    int max_bandwidth = 0;

    while (bfs(graph, source, sink, parent)) {
        int path_bandwidth = numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            path_bandwidth = min(path_bandwidth, graph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            graph[u][v] -= path_bandwidth;
            graph[v][u] += path_bandwidth;
        }

        max_bandwidth += path_bandwidth;
    }

    return max_bandwidth;
}

int main() {
    int network_number = 1;

    while (true) {
        int n;
        cin >> n;

        if (n == 0) {
            break;
        }

        int s, t, c;
        cin >> s >> t >> c;

        vector<vector<int>> graph(n, vector<int>(n, 0));

        for (int i = 0; i < c; ++i) {
            int u, v, b;
            cin >> u >> v >> b;
            graph[u - 1][v - 1] += b;
            graph[v - 1][u - 1] += b;
        }

        int bandwidth = edmonds_karp(graph, s - 1, t - 1);

        cout << "Network " << network_number << endl;
        cout << "The bandwidth is " << bandwidth << "." << endl << endl;

        network_number++;
    }

    return 0;
}
