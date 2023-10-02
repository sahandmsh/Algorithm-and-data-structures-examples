// This code checks if there are two members of vector some of which equals a given taarget.

#include <iostream>
#include <vector>
#include <map>
using namespace std;
class CheckSum{
public:
    void checksum(int value, vector <int> & nums){
        map <int , int> m;
        for (int i:nums){
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
    vector <int> nums = {1,2,5,7,8,4,56};
    int value = 64;
    CheckSum solution;
    solution.checksum(value,nums);
    return 0;
}
