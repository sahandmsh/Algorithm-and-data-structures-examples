#include <iostream>
#include <vector>
#include <map>
using namespace std;
class check{
public:
    void checksum(int value, vector <int> & a){
        map <int , int> m;
        for (int i:a){
            if (m[value-i]>0){
                cout<<"TRUE!\n";
                return;
            }
            else {m[i]+=1;}
        }
        cout<<"FALSE!\n";
    }
};

int main(){
    vector <int> a = {1,2,5,7,8,4,56};
    int value = 64;
    check solution;
    solution.checksum(value,a);
    return 0;
}
