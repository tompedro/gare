#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;
int MAX = 0;
bool done = false;

long long fast_exp(long long a, long long b){
  if(b == 0) return 1;
  if(b == 1) return a;
 
  long long x = fast_exp(a, b/2);
  if(b%2 == 0){
    return (x*x);
  } else {
    return x*x*a;
  }
}

void r(long long n, int N, int M, int l, int last){
	if(done) return;
	if(n % M > MAX){
		MAX = n % M;
	}
	if(n % M == M - 1){
		MAX = n % M;
		done = true;
		return;
	}
	if(l == N) return;
	for(int i = 3; i < 10; i+=3){
		if(i == last) continue;
		r(n + i*fast_exp(10,l), N, M, l+1, i);
	}
}

long long occulta(int N, int M) {
    // Mettete qui il codice della soluzione
    r(3,N,M,1,3);
    r(6,N,M,1,6);
    r(9,N,M,1,9);
    done = false;
    return MAX;
}


int main() {
    FILE *fr, *fw;
    int T, N, M, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &T));
    for (i=0; i<T; i++) {
        assert(2 == fscanf(fr, "%d %d", &N, &M));
        fprintf(fw, "%d ", occulta(N, M));
    }

    fprintf(fw, "\n");
    fclose(fr);
    fclose(fw);
    return 0;
}
