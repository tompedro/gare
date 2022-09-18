#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;

// Declaring variables
static int N;
static int Q;
static int T;
static int* A;
static int* B;
static int* C;
static int* U;
static int* V;
static long long int* res;

int LOG = 19;
vector< vector<int> > g, up;
vector<int> d;

void dfs(int x, int par){
    up[x][0] = par;
    if(x) d[x] = d[par] + 1;
    for(int a : g[x]){
        if(a == par) continue;
        
        dfs(a, x);
    }
}

// Declaring functions
void inizia(int N, int T, int A[], int B[], int C[]){
    g.resize(N); up.assign(N, vector<int> (19, -1)); d.resize(N);
    for(int i = 0; i < N-1; i++){
        g[A[i]].push_back(B[i]);
        g[B[i]].push_back(A[i]);
    }
   
    dfs(0,0); 

    for(int i = 1; i < LOG; i++){
        for(int j = 0; j < N; j++){
            up[j][i] = up[up[j][i-1]][i-1];
        }
    }
}

int lca(int u, int v){
    if(d[u] > d[v]) swap(u,v);
    int k = d[v] - d[u];

    for(int i = LOG-1; i >= 0; i--){
        if(k & (1 << i)){
            v = up[v][i];
        }
    }

    if(u == v) return u;

    for(int i = LOG-1; i >= 0; i--){
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

long long int distanza1(int u, int v){
    return d[u] + d[v] - 2*d[lca(u,v)];
}


long long int distanza2(int u, int v) {
	return 123456789123ll;
}

long long int minimo(int u, int v) {
	return 123456789123ll;
}

long long int massimo(int u, int v) {
	return 123456789123ll;
}

