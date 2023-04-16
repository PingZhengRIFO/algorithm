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


class Edge {
public:
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

// 图类
class Graph {
public:
    int V; // 图中的节点数
    vector<Edge> edges; // 所有边的集合

    Graph(int v) : V(v) {}

    // 添加一条边
    void addEdge(int from, int to, int weight) {
        edges.emplace_back(from, to, weight);
    }
};

// 定义一个并查集类
class DisjointSet {
public:
    // 构造函数
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // 查找操作
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // 合并操作
    void merge(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);
        if (xRoot == yRoot) {
            return;
        }
        if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }

private:
    vector<int> parent;  // 存储每个节点的父节点
    vector<int> rank;    // 存储每个节点的秩（即树的高度）
};
// Kruskal算法，返回最小生成树的边集
vector<Edge> kruskal(Graph& graph) {
    vector<Edge> result; // 最小生成树的边集
    int V = graph.V;
    DisjointSet ds(V); // 初始化并查集

    // 将所有边按权重从小到大排序
    sort(graph.edges.begin(), graph.edges.end(),
         [](const Edge& e1, const Edge& e2) {
             return e1.weight < e2.weight;
         });

    // 遍历所有边，将权重最小的边加入最小生成树的边集中
    for (const Edge& e : graph.edges) {
        int from = e.from;
        int to = e.to;
        if (ds.find(from) != ds.find(to)) { // 如果不在同一个集合中，说明加入这条边不会形成环
            ds.merge(from, to); // 将两个节点合并到一个集合中
            result.emplace_back(from, to, e.weight); // 将这条边加入最小生成树的边集中
        }
    }

    return result;
}

int main() {
    int V = 4;
    Graph g(V);

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    vector<Edge> test =kruskal(g);

    return 0;
}
