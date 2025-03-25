#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
//edge: weight,vertice1,vertice2
typedef tuple<int,int,int> Edge;

class Disjoint_Set_Union{
    vector<int> parents;
    vector<int> ranks;
public:
    Disjoint_Set_Union(int n){
        parents = vector<int> (n);
        ranks = vector<int> (n,0);
        for (int i=0;i<n;++i)parents[i] = i;
    }
    int find_root(int u){
        int root = u;
        while (parents[root]!= root){root = parents[root];}
        while (parents[u]!=root){
            int temp = parents[u];
            parents[u] = root;
            u = temp;
        }
        return root;
    }
    
    void subset_union(int u, int v){
        if (find_root(u) == find_root (v)) return;
        else if (ranks[u] == ranks[v]){
            parents[v] = u;
            ++ ranks[u];
        }
        else if (ranks[u]>ranks[v]){
            parents[v] = u;
        }
        else{
            parents[u] = v;
        }
    }
};

void minimumSpanningTree(int vertices_count, vector<Edge>& edges_list){
    auto disjSetUnion = Disjoint_Set_Union(vertices_count);
    sort(edges_list.begin(),edges_list.end());
    int mst_weight_sum = 0;
    vector<Edge> mst_edges;
    for (auto [w,u,v]:edges_list){
            if (disjSetUnion.find_root(u) != disjSetUnion.find_root(v)) {
                disjSetUnion.subset_union(u,v);
                mst_weight_sum += w;
                mst_edges.push_back({w,u,v});
            }
    }
    cout<<"The sum of the weights of the minimum spanning tree is: "<<mst_weight_sum<<endl;
    cout<<"MST edges are:\n";
    for (auto [w,u,v]:mst_edges) cout<<u<<"->"<<v<<" : "<<w<<endl;
}

int main(int argc, const char * argv[]) {
    int vertices_count = 5;
    //edge: weight,vertice1,vertice2
    vector<Edge> edges_list={
        make_tuple(7,0,1),
        make_tuple(2,0,2),
        make_tuple(8,0,3),
        make_tuple(4,0,4),
        make_tuple(8,1,2),
        make_tuple(3,1,3),
        make_tuple(6,2,4)
    };
    minimumSpanningTree(vertices_count,edges_list);
    return 0;
}
