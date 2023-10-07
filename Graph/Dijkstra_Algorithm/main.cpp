#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> NodeDist;
typedef vector<vector<NodeDist>> Adj_Lists;

//custom comparator for priority queue
class nopathexception:public runtime_error{
public:
    nopathexception():runtime_error("THERE IS NO PATH BETWEEN THE GIVEN NODES!"){}
};

class SSSP{
    Adj_Lists adj_lists;
    vector<bool> visited;
    vector<int> nodes_parent;
    vector<int> distances;
    const int UNKNOWN = -1;
    struct comp{
        bool operator()(NodeDist a, NodeDist b){
            return (a.second>=b.second);
        }
    };
    
    void dijkstra(int start){
        visited = vector<bool>(adj_lists.size(),false);
        distances = vector<int>(adj_lists.size(),UNKNOWN);
        nodes_parent = vector<int>(adj_lists.size(),UNKNOWN);
        priority_queue <NodeDist,vector<NodeDist>,comp> pq;
        pq.push(NodeDist(start,0));
        nodes_parent[start] = start;
        distances[start] = 0;
        
        while(!pq.empty()){
            auto [u,dist] = pq.top();
            pq.pop();
            if (visited[u] == true) continue;
            visited[u] = true;
            for (auto [v,w]:adj_lists[u]){
                if (distances[v] == UNKNOWN || distances[v]>w+distances[u]){
                    distances[v] = w+distances[u];
                    nodes_parent[v] = u;
                    pq.push(NodeDist(v,distances[v]));
                }
            }
        }
    }
public:
    SSSP(Adj_Lists adj_lists):adj_lists(adj_lists), 
        visited(vector<bool>(adj_lists.size(),false)),
        distances(vector<int>(adj_lists.size(),UNKNOWN)),
        nodes_parent(vector<int>(adj_lists.size(),UNKNOWN)){}
    
    void shortestPath(int start, int end){
        dijkstra(start);
        if (visited[end] == false) throw nopathexception();
        vector<int> ans;
        ans.push_back(end);
        int temp = end;
        while (temp!=start){
            temp = nodes_parent[temp];
            ans.push_back(temp);
        }
        reverse(ans.begin(),ans.end());
        cout<<"Path from node "<<start<< " to "<<end<<": ";
        for (auto node:ans) cout<<node<<"  ";
        cout<<"\nThe distance between the given nodes is: "<<distances[end]<<endl;
    }
    
};

int main() {
    int n = 5;
    Adj_Lists adj_lists(n);
    vector<tuple<int, int, int>> edges {
        make_tuple(0, 1, 6),
        make_tuple(0, 2, 10),
        make_tuple(0, 3, 4),
        make_tuple(1, 0, 2),
        make_tuple(1, 2, 3),
        make_tuple(1, 4, 5),
        make_tuple(3, 1, 1),
        make_tuple(3, 4, 2),
        make_tuple(4, 2, 1)
    };
    for (auto [u, v, w] : edges) {
        adj_lists[u].push_back(make_pair(v, w));
    }

    SSSP graph(adj_lists);
    graph.shortestPath(0,2);
}
