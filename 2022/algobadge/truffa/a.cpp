#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100000

int sfangate(int N, int V[]) {
    sort(&V[0], &V[N-1]);
    int sum = 0;
    for(int i = 0;i < N; i++){
        sum += V[i];
    }
    
    int j = 0;
    int r = 0;
    while(sum < 0 && j < N){
        if(V[j] < 0){
            sum += -2*V[j];
            r++;
        }
        j++;
        
    }
    return r;
}


int V[MAXN];

int main() {
    FILE *fr, *fw;
    int N, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &N));
    for(i=0; i<N; i++)
        assert(1 == fscanf(fr, "%d", &V[i]));

    fprintf(fw, "%d\n", sfangate(N, V));
    fclose(fr);
    fclose(fw);
    return 0;
}