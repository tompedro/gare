#include <vector>
using namespace std;

int trova_massimo(int N, vector<int> V) {
	int r = 0;
	for(int i = 0; i < N; i++){
		if(V[i] > r){
			r = V[i];
		}
	}
	return r;
}
