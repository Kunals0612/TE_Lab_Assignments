#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:

    vector<vector<int>> adj;
    vector<bool> visited;
    vector<int> res;
    queue<int> q;

public:
    Graph(int V) {
        adj.resize(V);
        visited.resize(V, false);
    }

    void reset(int V) {
        visited.assign(V, false);
        res.clear();
        queue<int> empty;
        swap(q, empty); // clear the queue
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // For undirected graph
    }

    // DFS Recursive
    void DFS_rec(int node) {
        visited[node] = true;
        res.push_back(node);
        for (auto &it : adj[node]) {
            if (!visited[it]) {
                DFS_rec(it);
            }
        }
    }

    vector<int> DFS(int start) {
        reset(adj.size());
        DFS_rec(start);
        return res;
    }

    // BFS Recursive
    void BFS_Rec() {
        if (q.empty()) return;

        int node = q.front();
        q.pop();
        res.push_back(node);

        for (auto &it : adj[node]) {
            if (!visited[it]) {
                visited[it] = true;
                q.push(it);
            }
        }

        BFS_Rec();
    }

    vector<int> BFS(int start) {
        reset(adj.size());
        visited[start] = true;
        q.push(start);
        BFS_Rec();
        return res;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cout<<"Enter u: "; cin >> u;
        cout<<"Enter v: "; cin >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting node for DFS and BFS: ";
    cin >> start;

    vector<int> dfs_result = g.DFS(start);
    cout << "DFS (recursive): ";
    for (int x : dfs_result) cout << x << " ";
    cout << endl;

    vector<int> bfs_result = g.BFS(start);
    cout << "BFS (recursive): ";
    for (int x : bfs_result) cout << x << " ";
    cout << endl;

    return 0;
}
