#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimization ("unroll-loops")
typedef vector<int> vi;
static FILE *fr, *fw;

// Declaring variables
int N;
static int* V;
static long long int numero_ribaltamenti;
vi bit;

void update(int idx, int delta) {
	for (; idx < N; idx = idx | (idx + 1))
		bit[idx] += delta;
}

int query(int r) {
	int ret = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1)
		ret += bit[r];
	return ret;
}

int query(int l, int r) {
	return query(r) - query(l - 1);
}

long long paletta_sort(int n, int V[]){
	N = n;
	bit.assign(N, 0);
	long long r=0;
	vi p,d;
	
	for (int i = 0; i < n; ++i){
		
		if(i%2!=V[i]%2)
			return -1;	
		
		if(V[i]%2==1)
			d.push_back(V[i]);
		else
			p.push_back(V[i]);
	}
	
	for(int i=0; i<d.size(); ++i){
    	r += i - query(d[i]);
    	update(d[i], 1);
	}
	
	
	fill(bit.begin(), bit.end(), 0);
	
	for(int i=0; i<p.size(); ++i){
    	r += i - query(p[i]);
    	update(p[i], 1);
	}

	return r;
}

int main() {
	fr = fopen("input.txt", "r");
	fw = fopen("output.txt", "w");

	// Reading input
	fscanf(fr, "%d ", &N);
	V = (int*)malloc(N * sizeof(int));
	for (int i0 = 0; i0 < N; i0++) {
		fscanf(fr, "%d ", &V[i0]);
	}

	// Calling functions
	numero_ribaltamenti = paletta_sort(N, V);

	// Writing output
	fprintf(fw, "%lld\n", numero_ribaltamenti);
	
	fclose(fr);
	fclose(fw);
	return 0;
}
