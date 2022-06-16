#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
static FILE *fr, *fw;

// Declaring variables
static int N;
static int d;
static int L;
static int* messaggio;
static char* plaintext;

long long fast_exp(long long a, long long b){
  if(b == 0) return 1;
  if(b == 1) return a;
 
  long long x = fast_exp(a, b/2);
  if(b%2 == 0){
    return (x*x)%N;
  } else {
    return (((x*x)%N)*a)%N;
  }
}

int cast(int n) {
   return '0' + n;
}

// Declaring functions
void decifra(int N, int d, int L, int* messaggio, char* plaintext){
	for(int i = 0; i < L; i++){
		plaintext[i] = (char)fast_exp(messaggio[i],d);
	}
	plaintext[L] = '\0';
}

int main() {
	/*fr = stdin;
	fw = stdout;*/

	fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
	// Iterators used in for loops
	int i0;

	// Reading input
        fscanf(fr, "%d %d %d", &N, &d, &L);
	messaggio = (int*)malloc(100 * sizeof(int));
	plaintext = (char*)malloc(110 * sizeof(char));
	for (i0 = 0; i0 < L; i0++)
            fscanf(fr, "%d", &messaggio[i0]);

	
	// Calling functions
	decifra(N, d, L, messaggio, plaintext);

	// Writing output
        fprintf(fw, "%s\n", plaintext);
	
	fclose(fr);
	fclose(fw);
	return 0;
}
