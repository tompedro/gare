#include <vector>
#include <math.h>
using namespace std;

long long somma(int l, int r);
long long subarray_massimo(int l, int r);
long long subarray_minimo(int l, int r);

long long trova(int N) {
    int l = 0, r = N;
    int res = -1;
    int add = 0;
    while(r-l > 1){
        int mid = (r+l)/2;
        if(somma(mid,mid) >= 0){
            l = mid;
        }else{
            r = mid;
        }
    }
    
    N = l+1;
    long long sum = 0;
    int j = 0;
    int a = floor(sqrt(N));
    int b = ceil(sqrt(N));
    if(a*b < N) a = b;
    for(int i = 0; i < a; i++){
        int j = (i+1)*b - 1;
        if(j >= N) j = N-1;
        sum += somma(i*b, j);
    }
    return sum;
}


