#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
static FILE *fr, *fw;

// Declaring variables
static int N;
static long long M;
static int* V;
static int B;

int o = 0;
int res = 0;

int maxSub(int arr[], int N, int k){
	int MAX = 0;
	
	for(int i = 0; i < k; i++){
		MAX += arr[i];
	}
	
	int last = MAX;
	for(int i = 1; i <= N-k; i++){
		last = last - arr[i-1] + arr[i+k-1];
		if(last > MAX) MAX = last;
	}
	
	return MAX;
}

int binarySearch(int arr[], int l, int r, int x, int N){
    if (r >= l) {
        int mid = l + (r - l) / 2;
		int a = maxSub(arr, N, mid);
		
        if (a == x)
            return mid;
        if (a > x){
            return binarySearch(arr, l, mid - 1, x, N);
 		}
 		o = a;
 		res = mid;
        return binarySearch(arr, mid + 1, r, x, N);
    }
    
    return o;
}

int quadri(int N, long long M, int* V){
	binarySearch(V, 0, N, M, N);
	return res;
}



int main() {
	fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

	// Iterators used in for loops
	int i0;

	// Reading input
	fscanf(fr, "%d %lld", &N, &M);
	V = (int*)malloc(N * sizeof(int));
	for (i0 = 0; i0 < N; i0++) {
	    fscanf(fr, "%d", &V[i0]);
	}

	// Calling functions
	B = quadri(N, M, V);

	// Writing output
	fprintf(fw, "%d\n", B);
	
	fclose(fr);
	fclose(fw);
	return 0;
}
