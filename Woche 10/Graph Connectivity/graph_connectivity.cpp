#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

const int MAXN = 26;

int n;
bool adj[MAXN][MAXN], vis[MAXN];
map<char, int> name_to_index;

// Recursive function to perform DFS traversal
void dfs(int u) {
    vis[u] = true;
    for (int v = 0; v < n; ++v) {
        if (adj[u][v] && !vis[v]) {
            dfs(v);
        }
    }
}

// Function to count the number of maximal connected subgraphs in the current graph
int count_maximal_connected_subgraphs() {
    int count = 0;
    memset(vis, false, sizeof(vis));
    for (int u = 0; u < n; ++u) {
        if (!vis[u]) {
            dfs(u);
            ++count;
        }
    }
    return count;
}

int main() {
    int t;
    string line;
    getline(cin, line);
    t = stoi(line);
    getline(cin, line); // consume blank line
    while (t--) {
        memset(adj, false, sizeof(adj));
        name_to_index.clear();
        char max_node_name;
        getline(cin, line);
        max_node_name = line[0];
        n = max_node_name - 'A' + 1;
        while (getline(cin, line) && line != "") {
            char u_name = line[0];
            char v_name = line[1];
            int u = name_to_index[u_name];
            int v = name_to_index[v_name];
            if (u == 0) {
                u = name_to_index[u_name] = u_name - 'A';
            }
            if (v == 0) {
                v = name_to_index[v_name] = v_name - 'A';
            }
            adj[u][v] = adj[v][u] = true;
        }
        cout << count_maximal_connected_subgraphs() << endl;
        if (t) {
            cout << endl; // add blank line between test cases
        }
    }
    return 0;
}
