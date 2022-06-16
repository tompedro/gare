#include <iostream>
using namespace std;
#define ll long long
#define int long long
ll mm = 1000000007;

int exp(int x, unsigned int y, int p){
    int res=1; x=x%p;
    while(y>0){
        if (y&1) res= (res*x)%p; y=y>>1; x=(x*x)%p;
    }
    return res;
}
signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    /*freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);*/

    int N;
    cin >> N;
    
    for(int i = 0; i < N; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        int r = exp(b,c,mm-1);
        cout << exp(a,r,mm) << endl;
    }
}