#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> Adj_Lists;
enum STATUS {NOT_VISITED,IN_PROGRESS,FINISHED};

// strongly connected components
class SCC{
    Adj_Lists adj_lists;
    vector <STATUS> nodes_stat;
    vector <int> finish_order;
public:
    SCC(Adj_Lists adj_lists): adj_lists(adj_lists),
    nodes_stat ( vector<STATUS> (adj_lists.size(),NOT_VISITED) ) {}
    
    void find_SCC(){
        for (int node = 0;node<adj_lists.size();++node){
            if (nodes_stat[node] == FINISHED) continue;
            dfs (node);
        }
        vector <int> reverse_finish_order (finish_order.rbegin(),finish_order.rend());
        graph_transpose();
        finish_order.clear();
        fill (nodes_stat.begin(),nodes_stat.end(),NOT_VISITED);
        cout<<"These are the SCCs:\n";
        for (int node:reverse_finish_order){
            if (nodes_stat[node] == FINISHED) continue;
            dfs (node);
            for (auto i:finish_order){cout<<i<<", ";}
            cout<<endl;
            finish_order.clear();
        }
        
    }
    
private:
    void dfs(int node){
        if (nodes_stat[node] == NOT_VISITED){
            nodes_stat[node] = IN_PROGRESS;
            for(auto v:adj_lists[node]) dfs(v);
            nodes_stat[node] = FINISHED;
            finish_order.push_back(node);
        }
    }
    
    void graph_transpose(){
        Adj_Lists temp = Adj_Lists (adj_lists.size());
        for (int u=0;u<adj_lists.size();++u){
            for (auto v:adj_lists[u]){
                temp[v].push_back(u);
            }
        }
        adj_lists = temp;
    }
    
};

int main(int argc, const char * argv[]) {
    int n = 8;
    Adj_Lists adj_lists(n);
    vector<pair<int, int>> edges {{0,1},{1,2},{2,3},{3,0},{2,4},{4,5},{5,6},{6,4},{6,7}};
    for (auto [u, v] : edges) {
        adj_lists[u].push_back(v);
    }

    SCC graph1(adj_lists);
    graph1.find_SCC();
    return 0;
}
