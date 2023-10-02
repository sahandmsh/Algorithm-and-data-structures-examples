// Calculating a^b 

#include <iostream>
using namespace std;
class power{
public:
    double num_power(int x , int power){
        double ans = 1.0 , y = x;
        if (power<0){y = 1/y;}
        if (power != 0){
            for (int i=1;i<=abs(power);++i){
                ans *= y;
            }
        }
        return ans;
    }
};

int main(){
    power p;
    cout<<p.num_power(-2,3)<<endl;
}
