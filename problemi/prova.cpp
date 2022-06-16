#include <iostream>
#include <math.h>
using namespace std;

int main(){

    for(int i = 0; i < 50; i++){
        cout << ((long long)pow(26,i)%(1000000007)) << endl;
    }

    return 0;
}