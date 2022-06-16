#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;
int N, M;
int MAX = 0;
bool a[10][10];

void r(int i, int j, int count){
	MAX = max(MAX, count);
	if(i >= N && j >= M) return;
	if(MAX > count + M*N - (i*N + j)) return;
	
	a[i][j] = true;
	bool c = true;
	if(i - 2 >= 0){
		if(j - 2 >= 0){
			if(a[i - 2][j - 2] && a[i-1][j-1]){
				c = false;
			}
		}
		if(a[i-2][j] && a[i-1][j]){
			c = false;
		}
		if(j + 2 < M){
			if(a[i - 2][j + 2] && a[i-1][j+1]){
				c = false;
			}
		}
	}
	if(j - 2 >= 0){
		if(a[i][j - 2] && a[i][j-1]){
			c = false;
		}
	}
			
	
	if(c) r(i+(j+1>=M),(j+1>=M ? 0 : j+1),count+1);
	a[i][j] = false;
	r(i+(j+1>=M),(j+1>=M ? 0 : j+1),count);
}

int gioca(int N, int M) {
    r(0,0,0);
    return MAX;
}


int main() {
    FILE *fr, *fw;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(2 == fscanf(fr, "%d %d", &N, &M));

    fprintf(fw, "%d\n", gioca(N, M));
    fclose(fr);
    fclose(fw);
    return 0;
}
