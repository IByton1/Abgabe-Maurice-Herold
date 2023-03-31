#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>
#include <vector>

using namespace std;

/*
The provided code is an implementation of the Prim's algorithm to find the minimum spanning tree (MST) of a given undirected, weighted graph represented using an adjacency list.
The function takes two parameters: an array of pairs representing the graph and the number of vertices in the graph.
The function returns the sum of the costs of the edges in the MST.
The algorithm uses a priority queue to keep track of the vertices with the minimum cost and a vector of costs to store the minimum cost of reaching each vertex.
The algorithm starts with an arbitrary vertex and adds the edge with the smallest cost connecting it to an unvisited vertex until all vertices have been visited.
*/

// Function to calculate the cost of the minimum spanning tree of the graph
int cost(vector<pair<int, int>> graph[], int numVertices)
{
    int sumCost = 0;

    // Initialize a priority queue of pairs (cost, vertex), sorted by cost
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;

    // Initialize a vector of costs for all vertices, set to infinity except for the first vertex
    vector<int> costs(numVertices, INT_MAX);
    vector<bool> visited(numVertices, false);

    // Add the first vertex to the queue with a cost of zero
    int u = 0;
    queue.push(make_pair(0, u));
    costs[u] = 0;

    // Repeat until all vertices have been visited
    while (!queue.empty())
    {
        // Extract the vertex with the smallest cost from the queue
        u = queue.top().second;
        queue.pop();

        // If the vertex has not been visited yet
        if (!visited[u])
        {
            // Mark the vertex as visited and add its cost to the sum
            visited[u] = true;
            sumCost += costs[u];

            // For each adjacent vertex v
            for (auto x : graph[u])
            {
                int cost = x.first;
                int v = x.second;

                // If v has not been visited yet and the cost to v is smaller than the current cost of v
                if (!visited[v] && cost < costs[v])
                {
                    // Update the cost of v and add it to the queue
                    costs[v] = cost;
                    queue.push(make_pair(cost, v));
                }
            }
        }
    }

    // Return the sum of costs of the minimum spanning tree
    return sumCost;
}

int main()
{
    int numVertices = 40;

    // Read the graph from file and construct the adjacency list
    ifstream fs("p107_network.txt");
    vector<pair<int, int>> graph[numVertices];
    string line, field;

    int sumCost = 0;
    for (int i = 0; getline(fs, line); i++)
    {
        istringstream s(line);

        for (int j = 0; getline(s, field, ','); j++)
        {
            // If the value is not "-", add the edge to the adjacency list and update the sum of costs
            if ("-" != field)
            {
                int cost = stoi(field);
                graph[i].push_back(make_pair(cost, j));
                sumCost += cost;
            }
        }
    }

    fs.close();

    // Calculate the weight of the removed edges by subtracting the cost of the minimum spanning tree from the total cost
    cout << sumCost / 2 - cost(graph, numVertices) << endl;

    return 0;
}
