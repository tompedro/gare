#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
static FILE *fr, *fw;

// Declaring variables
static int N;
static ll L;
static ll* D;
static ll* P;
static ll C;

// Declaring functions

bool r(ll k, ll l, ll i){
	if(i >= N && l <= k) return true; 
	if(l > k) return false;
	
	ll a = (i+1 >= N) ? (L-D[i]) : (D[i+1] - D[i]);
	
	if(l+P[i] <= k && P[i] < l){
		return r(k, P[i]+a, i+1);
	}else{
		return r(k, l+a, i+1);
	}
}

ll percorri(int N, ll L, ll D[], ll P[]){
	
	ll left = 0; ll right = L; ll m;
	
	while(left < right - 1){
		m = (left+right)/2;
		if(r(m,D[0],0)){
			right = m;	
		}else {
			left = m;
		}
	}
	return r(left,D[0],0) ? left : right;
}



int main() {
	fr = stdin;
	fw = stdout;

	// Reading input
	fscanf(fr, " %d %lld", &N, &L);
	D = (ll*)malloc((N) * sizeof(ll));
	for (int i0 = 0; i0 < N; i0++) {
		fscanf(fr, " %lld", &D[i0]);
	}
	P = (ll*)malloc((N) * sizeof(ll));
	for (int i0 = 0; i0 < N; i0++) {
		fscanf(fr, " %lld", &P[i0]);
	}

	// Calling functions
	C = percorri(N, L, D, P);

	// Writing output
	fprintf(fw, "%lld\n", C);

	fclose(fr);
	fclose(fw);
	return 0;
}
