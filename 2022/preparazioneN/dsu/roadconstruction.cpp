#include <bits/stdc++.h>
using namespace std;

vector<int> parent;
vector<int> c;
int all = 0;
int sum = 0;

void make_set(int v){
	parent[v] = v;
	c[v] = 1;
}

int find_set(int v){
	if(parent[v] == v){
		return v;
	}
	
	return parent[v] = find_set(parent[v]);
}

void union_set(int u, int v){
	u = find_set(u);
	v = find_set(v);
	if(u != v){
		parent[u] = v;
		c[v] += c[u];
		sum = max(sum, c[v]);
		c[u] = 0;
		all--;
	}
}

int main(){
	int N,M;
	cin >> N >> M;
	
	all = N;
	
	parent.resize(N); c.resize(N);
	
	for(int i = 0; i < N; i++) make_set(i);
	
	for(int i = 0; i < M; i++){
		int a,b;
		cin >> a >> b;
		a--; b--;
		
		union_set(a,b);
		cout << all << " " << sum << endl;
	}
	
	return 0;
}
