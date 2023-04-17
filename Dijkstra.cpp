#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#include <climits>


using namespace std;

typedef pair<int, int> pii;

const int INF = 0x3f3f3f3f;

struct Edge {
    int to, weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

vector<vector<Edge>> adj; // 邻接表表示图
vector<int> dist; // 存储源节点到各个节点的最短距离
vector<bool> visited; // 标记节点是否已访问

void dijkstra(int s) {
    dist[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s}); // 距离,节点编号
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge e : adj[u]) {
            int v = e.to, w = e.weight;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    adj.resize(n + 1);
    dist.assign(n + 1, INF);
    visited.assign(n + 1, false);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    dijkstra(s);
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) cout << "INF ";
        else cout << dist[i] << " ";
    }
    return 0;
}
