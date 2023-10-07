#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> Adj_Lists;
enum Status{UNVISITED,IN_PROGRESS,FINISHED};

class CyclicGraphException: public runtime_error{
public:
    CyclicGraphException() : runtime_error("The graph is cyclic. Cannot find the topological order") {}
};

class Topological_Sort{
    vector<Status> nodes_stat;
    Adj_Lists adj_lists;
    vector<int> topological_order;
    void dfs(int);
public:
    Topological_Sort(Adj_Lists adj_lists): adj_lists(adj_lists),
        nodes_stat(vector <Status>(adj_lists.size(),UNVISITED)){}
    
    vector<int> find_topological_sort();
    
};

vector<int> Topological_Sort::find_topological_sort(){
    topological_order.resize(0);
    nodes_stat = vector <Status> (adj_lists.size(),UNVISITED);
    for (int node=0;node<adj_lists.size();++node){
        if (nodes_stat[node] == FINISHED) continue;
        dfs(node);
    }
    reverse(topological_order.begin(),topological_order.end());
    return topological_order;
}

void Topological_Sort::dfs(int node){
    switch (nodes_stat[node]){
        case FINISHED: return;
        case IN_PROGRESS: throw CyclicGraphException(); break;
        case UNVISITED:
            nodes_stat[node] = IN_PROGRESS;
            for (auto v:adj_lists[node]){
                dfs(v);
            }
    }
    nodes_stat[node] = FINISHED;
    topological_order.push_back(node);
}


int main(int argc, const char * argv[]) {
    vector <pair<int,int>> edges {{0,1},{1,2},{2,3},{3,4},{2,4}};
    Adj_Lists adj_lists(5);
    for (auto [i,j]:edges){
        adj_lists[i].push_back(j);
    }
    Topological_Sort tp(adj_lists);
    vector <int> tp_order = tp.find_topological_sort();
    for(int i=0;i<tp_order.size();++i) {
        cout<<tp_order[i];
        if (i<tp_order.size()-1) cout<<" -> ";
        else cout<<endl;
    }
}
