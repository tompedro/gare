#include <bits/stdc++.h>
using namespace std;

vector<int> tree;

int sum(int i){
	int res = 0;
	while(i > 0){
		res += tree[i];
		i -= i & -i;
	}
	
	return res;	
}

//point update
int add(int i, int val){
	if(i < val){
		T[i] += val;
		i += i & -i;
	}
}

void make(vector<int> a){
	tree = a;
	
	for(int i = 1; i < a.size(); i++){
		int p = i + (i & -i);
		if(p < a.size()){
			tree[p] += tree[i];
		}
	}
}

int main(){
	
	return 0;
}
