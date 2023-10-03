#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> Adj_Lists;
enum COLOR {UNKNOWN,RED,BLUE};

class Bipartite_Checker_DFS{
    Adj_Lists adj_lists;
    vector<COLOR> nodes_color;
    bool is_biparatite;
public:
    Bipartite_Checker_DFS(Adj_Lists adj_lists): adj_lists(adj_lists),
        nodes_color(vector<COLOR> (adj_lists.size(),UNKNOWN)){}
    
    void check_bipartite(){
        is_biparatite = true;
        for (int node=0;node<adj_lists.size();++node){
            if (nodes_color[node] == UNKNOWN) dfs(node,RED);
        }
        if (is_biparatite == true){
            cout<<"The graph is biparatite and the COLOR of the nodes are listed as follows\n";
            for (int u=0;u<adj_lists.size();++u){cout<<"node "<<u<<" belongs to COLOR "<<nodes_color[u]<<endl;}
        }
        else cout<<"The graph is not biparatite\n";
    }
    
    void dfs(int node, COLOR color){
        switch (nodes_color[node]){
            case RED:
                if (color == BLUE) is_biparatite = false; return;
            case BLUE:
                if (color == RED) is_biparatite = false; return;
            case UNKNOWN:
                nodes_color[node] = color;
                for (int v:adj_lists[node]){
                    dfs(v,(color == RED)?BLUE:RED);
        }
        }
    }
};

int main(int argc, const char * argv[]) {
    Adj_Lists adj_lists =Adj_Lists(4);
    vector<pair<int,int>> edges = {{0,2},{0,3},{2,1},{1,3},{2,1}};
    for (auto [u,v]:edges){
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);
    }
    Bipartite_Checker_DFS graph(adj_lists);
    graph.check_bipartite();
}
