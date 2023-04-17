#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int INF = 0x3f3f3f3f;

vector<vector<int>> bellman_ford(vector<vector<int>>& graph, int s) {
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);
    dist[s] = 0;
    for (int k = 1; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] != INF && dist[i] != INF && dist[j] > dist[i] + graph[i][j]) {
                    dist[j] = dist[i] + graph[i][j];
                    parent[j] = i;
                }
            }
        }
    }
    vector<vector<int>> result(n, vector<int>());
    for (int i = 0; i < n; ++i) {
        if (dist[i] != INF) {
            stack<int> path;
            int p = parent[i];
            while (p != -1) {
                path.push(p);
                p = parent[p];
            }
            while (!path.empty()) {
                result[i].push_back(path.top());
                path.pop();
            }
            result[i].push_back(i);
        }
    }
    return result;
}

int main() {
    vector<vector<int>> graph = {
        {0, 2, 6, 4},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };
    vector<vector<int>> result = bellman_ford(graph, 0);
    for (int i = 0; i < result.size(); ++i) {
        cout << "Shortest path from node 0 to node " << i << ": ";
        for (int j = 0; j < result[i].size(); ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
