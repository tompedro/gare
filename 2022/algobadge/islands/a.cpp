#include <stdio.h>
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std;

// constraints
#define MAXN 1000

// input data
int R, C;
int i, j;
int M[MAXN][MAXN];
vector<vector<bool>> processed;
int res = 0;

void dfs(int x, int y){
    if(processed[x][y]) return;
    processed[x][y] = true;
    if(x-1 >= 0 && M[x-1][y]) dfs(x-1, y);
    if(x+1 < R && M[x+1][y]) dfs(x+1, y);
    if(y-1 >= 0 && M[x][y-1]) dfs(x, y-1);
    if(y+1 < C && M[x][y+1]) dfs(x, y+1);
}

int main() {
//  uncomment the following lines if you want to read/write from files
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d %d", &R, &C));
    for(i=0; i<R; i++)
        for (j=0; j<C; j++)
            assert(1 == scanf("%d", &M[i][j]));

    processed.assign(R, vector<bool> (C, false));
    // insert your code here

    for(int i = 0; i < R; i++){
        if(M[i][0] && !processed[i][0]) dfs(i, 0);
        if(M[i][C-1] && !processed[i][C-1]) dfs(i, C-1);
    }
    for(int i = 0; i < C; i++){
        if(M[0][i] && !processed[0][i]) dfs(0, i);
        if(M[R-1][i] && !processed[R-1][i]) dfs(R-1, i);
    }

    for(int i = 1; i < R-1; i++){
        for(int j = 1; j < C-1; j++){
            if(M[i][j] && !processed[i][j]){
                dfs(i,j);
                res++;
            }
        }
    }

    printf("%d\n", res); // print the result
    return 0;
}
