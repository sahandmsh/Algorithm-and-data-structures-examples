#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> Adj_Matrix;

class NoPathExsitsException:public runtime_error{
public:
    NoPathExsitsException():runtime_error("NO PATH EXISTS FROM GIVEN START POINT TO END POINT"){};
};

class MSSP{
    Adj_Matrix predecessor_matrix;
    Adj_Matrix distances_matrix;
    const int INF = 1'000'000'000, UNKNOWN=-1;
public:
    MSSP(Adj_Matrix adj_matrix):distances_matrix(adj_matrix){
        predecessor_matrix = Adj_Matrix(adj_matrix.size(),vector<int>(adj_matrix.size(),UNKNOWN));
        for (int i=0;i<distances_matrix.size();++i){
            predecessor_matrix[i][i] = i;
            for (int j=0;j<distances_matrix.size();++j)
                if (distances_matrix[i][j] == 0){
                    distances_matrix[i][j] = INF;
                }
                else predecessor_matrix[i][j] = i;
            distances_matrix[i][i] = 0;
        }
        floyd_Warshall();
    }
    
    void floyd_Warshall(){
        int n = int(distances_matrix.size());
        for (int k=0;k<n-1;++k){
            for (int i=0;i<n;++i){
                for (int j=0;j<n;++j){
                    if (distances_matrix[i][k]+distances_matrix[k][j]<distances_matrix[i][j]){
                        distances_matrix[i][j] = distances_matrix[i][k]+distances_matrix[k][j];
                        predecessor_matrix[i][j] = predecessor_matrix[k][j];
                    }
                }
            }
        }
    }
    
    void shortest_path(int start,int end){
        if (predecessor_matrix[start][end] == UNKNOWN) throw NoPathExsitsException();
        int temp = end;
        vector<int> path;
        path.push_back(temp);
        while (temp != start){
            temp = predecessor_matrix[start][temp];
            path.push_back(temp);
        }
        cout<<"The shortest path from node "<<start<<" to node "<<end<<" is:  ";
        reverse(path.begin(),path.end());
        for (int i=0;i<path.size();++i){
            cout<<path[i]<<"  ";
        }
        cout<<"\nThe shortest distance from node "<<start<<" to "<<end<<" is:   "<<distances_matrix[start][end]<<endl;
    }
    
};

int main() {
    int n = 5;
    Adj_Matrix adj_matrix(n, vector<int>(n, 0));
    vector<tuple<int, int, int>> edges {
        make_tuple(0, 1, 10),
        make_tuple(0, 2, 3),
        make_tuple(0, 3, 20),
        make_tuple(1, 3, 5),
        make_tuple(2, 1, 2),
        make_tuple(2, 3, 6),
        make_tuple(2, 4, 15),
        make_tuple(3, 4, 11)
    };
    for (auto [v, u, w] : edges) {
        adj_matrix[v][u] = w;
    }
    
    MSSP graph(adj_matrix);
    for (int start = 0;start<n;++start){
        for (int end = 0; end<n;++end){
            try{
                graph.shortest_path(start, end);
            } catch (NoPathExsitsException exc) {cout<<"No path from node "<<start<<" to "<<end<<endl;}
            cout<<"--------------------------------------------------\n";
        }
    }
}
