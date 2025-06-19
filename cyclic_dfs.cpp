#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cyclic_dfs(int v, vector<vector<int>> &adj, vector<bool> &visited,
                vector<bool> &recStack, vector<int> &parent, vector<int> &cycle) {
    visited[v] = true;
    recStack[v] = true;

    for (int u = 0; u < adj.size(); ++u) {
        if (adj[v][u]) {
            if (!visited[u]) {
                parent[u] = v;
                if (cyclic_dfs(u, adj, visited, recStack, parent, cycle))
                    return true;
            } else if (recStack[u]) {
                int current = v;
                cycle.push_back(u);
                while (current != u && current != -1) {
                    cycle.push_back(current);
                    current = parent[current];
                }
                cycle.push_back(u);
                reverse(cycle.begin(), cycle.end());

                cout << "Cycle detected using DFS." << endl;
                cout << "Vertices in the cycle: ";
                for (int x : cycle)
                    cout << x << " ";
                cout << endl;
                return true;
            }
        }
    }

    recStack[v] = false;
    return false;
}

bool dtct_dfs(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<int> parent(n, -1);
    vector<int> cycle;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (cyclic_dfs(i, adj, visited, recStack, parent, cycle)) {
                return true;
            }
        }
    }

    cout << "No cycle detected using DFS." << endl;
    return false;
}

int main() {
    vector<vector<int>> adj = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    };

    dtct_dfs(adj);
    return 0;
}
