#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // 表示正无穷

// 图的边
struct Edge {
    int from; // 起点
    int to; // 终点
    int weight; // 权重
    Edge(int u, int v, int w) : from(u), to(v), weight(w) {}
};

// Bellman-Ford算法
vector<int> bellman_ford(const vector<Edge>& edges, int n, int s) {
    vector<int> dist(n, INF); // 距离数组，初始化为无穷大
    dist[s] = 0; // 源点到自己的距离为0
    for (int i = 0; i < n - 1; ++i) { // 进行n-1轮松弛操作
        for (const auto& e : edges) {
            if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.weight) {
                dist[e.to] = dist[e.from] + e.weight; // 更新距离
            }
        }
    }
    // 检查是否存在负权回路
    for (const auto& e : edges) {
        if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.weight) {
            throw runtime_error("Negative weight cycle detected");
        }
    }
    return dist;
}

int main() {
    int n = 5, s = 0; // 5个点，起点为0
    vector<Edge> edges = {
        {0, 1, 6},
        {0, 2, 7},
        {1, 2, 8},
        {1, 3, 5},
        {2, 3, -4},
        {2, 4, 9},
        {3, 4, 7}
    };
    auto dist = bellman_ford(edges, n, s);
    cout << "Shortest distances from source node " << s << ":\n";
    for (int i = 0; i < n;
