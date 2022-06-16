#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <limits>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

#define MAXN 5000
#define MAXK 5000
#define MAXP 1000000
#define INF numeric_limits<int>::max()

int N, K, MIN = INF;
int P[MAXN];
int memo[MAXN][MAXK];
int memo2[MAXN];

int r(int i, int v){
    if(v > MIN) return INF; 
    if(v >= K) return v;
    if(i >= N) return INF;
    if(memo[i][v] && memo2[i] >= memo[i][v]) return memo[i][memo2[i]];
    if(memo[i][v]) return memo[i][v];

    if(i+1 <= N){
        int val;
        if(v+P[i] > MIN){
            val = r(i+1, v);
        }else{
            val = min(r(i+1, v + P[i]), r(i+1, v));
        }
        
        if(val >= K) MIN = min(MIN, val);
        if(v > memo2[i]) memo2[i] = v;
        memo[i][v] = val;
    
        return val;
    }
    return INF;
}

int mangia(int n, int K, int p[]) {
    sort(P, P + n, greater<int>());
    for(int i = 0; i < n; i++) memo2[i] = -1;
    r(0, 0);
    //cout << r(0, 0) << endl;
    return MIN;
}


int main() {
    FILE *fr, *fw;
    int i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(2 == fscanf(fr, "%d %d", &N, &K));
    for(i=0; i<N; i++)
        assert(1 == fscanf(fr, "%d", &P[i]));

    fprintf(fw, "%d\n", mangia(N, K, P));
    fclose(fr);
    fclose(fw);
    return 0;
}
