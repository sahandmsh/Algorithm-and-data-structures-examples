#include <iostream>
#include <vector>
#include <queue>
#include <pair>
using namespace std;
typedef vector<vector<int>> Adj_Lists;
enum CATEGORY {UNKNOWN,RED,BLUE};

class Bipartite_Checker_BFS{
    Adj_Lists adj_lists;
    vector<CATEGORY> nodes_category;
    CATEGORY current_cat = BLUE;
    bool is_biparatite;
public:
    Bipartite_Checker_BFS(Adj_Lists adj_lists): adj_lists(adj_lists),
        nodes_category(vector<CATEGORY> (adj_lists.size(),UNKNOWN)){}
    
    void bfs(int node){
        queue<int> unexplored;
        unexplored.push(node);
        unexplored.push(-1);
        while(!unexplored.empty()){
            int u = unexplored.front();
            unexplored.pop();
            if (u==-1){
                if (!unexplored.empty()){
                    unexplored.push(-1);
                    current_cat = (current_cat==RED)?BLUE:RED;
                }
            }
            else{
                switch (nodes_category[u]){
                    case UNKNOWN:
                        nodes_category[u] = current_cat;
                        for (auto v:adj_lists[u]){unexplored.push(v);}
                        break;
                    case RED:
                        if (current_cat==BLUE){is_biparatite = false;}
                        break;
                    case BLUE:
                        if (current_cat==RED){is_biparatite=false;}
                        break;
                }
            }
        }
    }
    
    void check_bipartite(){
        is_biparatite = true;
        for (int node=0;node<adj_lists.size();++node){
            if (nodes_category[node] == UNKNOWN) bfs(node);
        }
        if (is_biparatite == true){
            cout<<"The graph is biparatite and the category of the nodes are listed as follows\n";
            for (int u=0;u<adj_lists.size();++u){cout<<"node "<<u<<" belongs to category "<<nodes_category[u]<<endl;}
        }
        else cout<<"The graph is not biparatite\n";
    }
};

int main(int argc, const char * argv[]) {
    Adj_Lists adj_lists =Adj_Lists(4);
    vector<pair<int,int>> edges = {{0,2},{0,3},{2,1},{1,3},{2,1}};
    for (auto [u,v]:edges){
        adj_lists[u].push_back(v);
        adj_lists[v].push_back(u);
    }
    Bipartite_Checker_BFS graph(adj_lists);
    graph.check_bipartite();
}
