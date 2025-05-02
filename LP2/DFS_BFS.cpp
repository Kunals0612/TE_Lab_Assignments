#include<iostream>
#include<vector>
using namespace std;
class Graph{
   private:
        vector<vector<int>> adj;
        vector<bool>visited;
        vector<int> res;
   public:
        Graph(int V){
            adj.resize(V);
            visited.resize(V);
            for(int i=0; i<V; i++){
                visited[i] = 0;
            }
        }

        void addEdge(int u, int v){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // DFS R
        void DFS_rec(int node){
            visited[node] = true;
            res.push_back(node);
            for(auto & it : adj[node]){
                if(!visited[it]){
                    DFS_rec(it);
                }
            }
        }

        vector<int> DFS(int start){
            DFS_rec(start);
            return res;
        }
       
};
int main(){

    return 0;
}