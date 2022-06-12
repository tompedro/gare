#include <stdio.h>
#include <assert.h>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int compra(int N, int M, int A, int B) {
    // Mettete qui il codice della soluzione
    int m = 0;
    while(N > 0){
    	if(N*A < B){
    		m += N*A;
    		break;
		}else{
			N -= M;
			m += B;
		}
	}
	if(N*A < m) m = N*A;
	return m;
}

int main() {
    FILE *fr, *fw;
    int N, M, A, B;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    assert(4 == fscanf(fr, "%d%d%d%d", &N, &M, &A, &B));

    fprintf(fw, "%d\n", compra(N, M, A, B));
    fclose(fr);
    fclose(fw);
    return 0;
}
