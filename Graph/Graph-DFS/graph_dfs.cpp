#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> Adj_Lists;
enum node_status{NOT_VISITED,IN_PROGRESS,FINISHED};

class Cycle_Checker{
    Adj_Lists adj_lists;
    vector <int> nodes_stat;
    bool cyclic=false;
public:
    Cycle_Checker(Adj_Lists adj_lists):adj_lists(adj_lists){
        nodes_stat = vector<int> (adj_lists.size(),NOT_VISITED);
    }
    
    void dfs (int node,int parent=-1){
        nodes_stat[node] = IN_PROGRESS;
        for (auto i:adj_lists[node]){
            if (i == parent) continue;
            switch (nodes_stat[i]){
                case FINISHED:
                    break;
                case NOT_VISITED:
                    dfs(i); break; //for directed graphs
//                    dfs(i,node); break; //for undirected graphs
                case IN_PROGRESS:
                    cyclic = true; break;
            }
        }
        this->nodes_stat[node] = FINISHED;
    }
    
    bool is_cyclic (){
        for (int node = 0; node<adj_lists.size();++node){
            if (nodes_stat[node] == FINISHED){continue;}
            dfs(node);
            if (cyclic == true){return true;}
        }
        return false;
    }
};

int main() {
    int n = 5;
    Adj_Lists adj_lists(n);
    vector<pair<int, int>> edges {{0, 1}, {1, 2}, {2, 3}, {1, 3},{2,4},{4,1}};         // cyclic example, directed graph
//    vector<pair<int, int>> edges {{0, 1}, {1, 2}, {2, 3}, {1, 3},{2,4}};         // acyclic example, directed graph
    for (auto [u, v] : edges) {
        adj_lists[u].push_back(v);
    }
    Cycle_Checker cycle_checker(adj_lists);
    cout << "The given graph is " << ((cycle_checker.is_cyclic()==false)?"acylic":"cyclic") << endl;
}
