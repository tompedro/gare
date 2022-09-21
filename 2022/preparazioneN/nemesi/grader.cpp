#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
static FILE *fr, *fw;

// Declaring variables
static int N;
static int* nemico;

// Declaring functions


static int gruppi = 0;

void nuovo_gruppo() {
	if (gruppi != 0) fprintf(fw, "\n");
	gruppi++;
}

void aggiungi(int bambino) {
	fprintf(fw, "%d ", bambino);
}

void smista(int N, int* nemico){
	int size = N;
	set<int> bl;
	vector<int> used(N,0);
	
	while(size > 0){
		nuovo_gruppo();
		for(int i = 0; i < N; i++){
			if(used[i] == 0 && used[nemico[i]] != gruppi && bl.find(i) == bl.end()){
				aggiungi(i);
				used[i] = gruppi;
				bl.insert(nemico[i]);
				size--;
			}
		}
		bl.clear();
		
	}
}

int main() {
	fr = fopen("input.txt", "r");
	fw = fopen("output.txt", "w");

	// Reading input
	fscanf(fr, "%d ", &N);
	nemico = (int*)malloc(N * sizeof(int));
	for (int i0 = 0; i0 < N; i0++) {
		//cout << "a : " << i0 << endl; 
		fscanf(fr, "%d ", &nemico[i0]);
	}

	// Calling functions
	smista(N, nemico);

	// Writing output
	
	fclose(fr);
	fclose(fw);
	return 0;
}
