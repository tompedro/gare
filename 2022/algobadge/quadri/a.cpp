#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
static FILE *fr, *fw;

// Declaring variables
static long long int N;
static long long M;
static long long int* V;
static long long int B;

long long int o = 0;
long long int res = 0;

long long int maxSub(long long int arr[], long long int N, long long int k){
	long long int MAX = 0;
	
	for(long long int i = 0; i < k; i++){
		MAX += arr[i];
	}
	
	long long int last = MAX;
	for(long long int i = 1; i <= N-k; i++){
		last = last - arr[i-1] + arr[i+k-1];
		if(last > MAX) MAX = last;
	}
	
	return MAX;
}

long long int binarySearch(long long int arr[], long long int l, long long int r, long long int x, long long int N){
    if (r >= l) {
        long long int mid = l + (r - l) / 2;
		long long  int a = maxSub(arr, N, mid);
		
        if (a == x){
			res = mid;
            return mid;
		}
			
        if (a > x){
            return binarySearch(arr, l, mid - 1, x, N);
 		}
		
		res = mid;
        return binarySearch(arr, mid + 1, r, x, N);
    }
	return res;
}

long long int quadri(long long int N, long long M, long long int* V){
	return binarySearch(V, 0, N, M, N);
}


int main() {
	fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

	// Iterators used in for loops
	long long int i0;

	// Reading input
	fscanf(fr, "%d %lld", &N, &M);
	V = (long long int*)malloc(N * sizeof(long long int));
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
