#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int MAX = 0;
int N;
vector<int> memo;

int r(int x[], int y[], int d, int t){
    if(d >= N) return t;
    if(memo[d] != -1) return t + memo[d];
    int best = max(r(x, y, d+1, t+x[N - d - 1]), r(x, y, d+2, t+y[N - d - 1]));
    memo[d] = best - t;
    return best;
}


int tempo_massimo(int n, int x[], int y[]){
    N = n;
    memo.assign(N, -1);
    return r(x, y, 0, 0);
    
}

int main()
{
    FILE *in = fopen("input.txt", "r"), *out = stdout;
    assert(fscanf(in, "%d", &N) == 1);

    int *a = (int*)calloc(N, sizeof(int));
    int *b = (int*)calloc(N, sizeof(int));

    for(int i=0; i<N; i++){
      assert(fscanf(in, "%d", a + i) == 1);
      assert(fscanf(in, "%d", b + i) == 1);
    }

    int answ = tempo_massimo(N, a, b);
    fprintf(out, "%d\n", answ);

    free(a);
    free(b);

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
