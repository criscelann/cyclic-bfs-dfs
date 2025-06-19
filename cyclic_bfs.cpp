#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool cyclic_bfs(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    for (int start = 0; start < n; ++start) {
        if (visited[start]) continue;

        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < n; ++v) {
                if (adj[u][v]) {
                    if (!visited[v]) {
                        q.push(v);
                        visited[v] = true;
                        parent[v] = u;
                    } else if (v != parent[u]) {
                        vector<int> cycle;
                        cycle.push_back(v);
                        int current = u;
                        while (current != v && current != -1) {
                            cycle.push_back(current);
                            current = parent[current];
                        }
                        cycle.push_back(v);
                        reverse(cycle.begin(), cycle.end());

                        cout << "Cycle detected using BFS." << endl;
                        cout << "Vertices in the cycle: ";
                        for (int x : cycle)
                            cout << x << " ";
                        cout << endl;
                        return true;
                    }
                }
            }
        }
    }

    cout << "No cycle detected using BFS." << endl;
    return false;
}

int main() {
    vector<vector<int>> adj = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    };

    cyclic_bfs(adj);
    return 0;
}
