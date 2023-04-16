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

const int MAXN = 1005;

// 邻接表存图
vector<pii> G[MAXN];

// Prim 算法求最小生成树
int prim(int n, int s) {
    int ans = 0;
    vector<bool> vis(n, false);
    vector<int> dist(n, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, s});
    dist[s] = 0;
    while (!pq.empty()) {
        pii u = pq.top();
        pq.pop();
        if (vis[u.second]) continue;
        vis[u.second] = true;
        ans += u.first;
        for (pii e : G[u.second]) {
            if (!vis[e.second] && e.first < dist[e.second]) {
                dist[e.second] = e.first;
                pq.push({dist[e.second], e.second});
            }
        }
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        G[u].push_back({w, v});
        G[v].push_back({w, u});
    }
    int ans = prim(n, 0);
    cout << ans << endl;
    return 0;
}
