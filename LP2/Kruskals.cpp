#include<bits/stdc++.h>
using namespace std;
class DSU{
   private:
        vector<int> rank, parent;
   public: 
        DSU(int V){
            rank.resize(V);
            parent.resize(V);
            for(int i=0; i<V; i++){
                parent[i] = i;
                rank[i] = 1;
            }
        }

        int find(int i){
            return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
        }
        void unite(int u, int v){
            int s1 = find(u), s2 = find(v);
            if(s1 != s2){
                if(rank[s1] < rank[s2]){
                    parent[s1] = s2; 
                }else if(rank[s1] > rank[s2]){
                    parent[s2] = s1;
                }else{
                    parent[s2] = s1;
                    rank[s1]++;
                }
            }
        }
};
bool comparator(vector<int>& a, vector<int>& b){
    if(a[2] <= b[2]){
        return true;
    }
    return false;
}
int kruskalsMST(int V, vector<vector<int>> edges){
    sort(edges.begin(), edges.end(), comparator);

    int cost = 0;
    int count = 0;
    
    DSU dsu(V);

    for(auto &edge : edges){
        int u = edge[0], v = edge[1], w = edge[2];
        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u,v);
            cost += w;
            if(++count == V-1){
                break;
            }
        }
    }
    return cost;
}
int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> edges;
    cout << "Enter each edge in the format: u v w\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int mstCost = kruskalsMST(V, edges);
    cout << "Minimum Cost of MST: " << mstCost << endl;
    
    return 0;
}