#include<bits/stdc++.h>
using namespace std;
class Prims{
   public:
      int spanningTree(int V, vector<vector<pair<int,int>>>& adj){
          priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
          //weight and node
          pq.push({0,0});
          vector<int> vis(V, 0);
          int sum = 0;
          while(!pq.empty()){

              auto it = pq.top();
              pq.pop();

              int node = it.second;
              int weight = it.first;
              
              if(vis[node] == 1){
                continue;
              }
              vis[node] = 1;
              sum += weight;

              for(auto & it : adj[node]){
                  int adjNode = it.first;
                  int adjweight = it.second;
                  if(vis[adjNode] != 1){
                      pq.push({adjweight, adjNode});
                  }
              }
          }
          return sum;
      }
};
int main(){
    int V;
    cout<<"Enter the number of vertices: ";
    cin>>V;

    int edge;
    cout << "Enter the number of edges: ";
    cin >> edge;

    vector<vector<int>> edges;
    vector<vector<pair<int,int>>> adj(V);
    for (int i = 0; i < edge; i++)
    {
        cout << "Enter the edges (node1 node2 weight):  " << i << endl;
        int node1, node2, weight;
        cin >> node1 >> node2 >> weight;
        edges.push_back({node1, node2, weight}); // Convert 1-based to 0-based
        adj[node1].push_back({node2, weight});
        adj[node2].push_back({node1, weight});
    }
    Prims obj;
    int sum = obj.spanningTree(V, adj);
    cout << "The sum of all the edge weights: " << sum << endl;
    return 0;
}