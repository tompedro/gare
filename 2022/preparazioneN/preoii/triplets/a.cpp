#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

vector< vector<int> > g, up;
vector<int> tin, tout, d;

int timer = 0;

bool ancestor(int a, int b){ // a è ancestor di b
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void bfs(int x, int p){
	tin[x] = timer++;
    up[0][x] = p;
	for(int a : g[x]){
		if(a == p) continue;
		d[a] = d[x] + 1;
		bfs(a, x);
	}
	tout[x] = timer++;
}

int lca(int a, int b){
	if(ancestor(a,b)) return a;
	if(ancestor(b,a)) return b;

	for(int i = 18; i >= 0; i--){
		if(!ancestor(up[i][a],b)) a = up[i][a];
	}

	return up[0][a];
}

int distance(int a, int b){
	return d[a] + d[b] - 2*d[lca(a,b)];
}

int build(int N, std::vector<int> A, std::vector<int> B){
	g.resize(N); tin.resize(N); tout.resize(N);
	d.assign(N, 0); up.assign(19, vector<int> (N));
	
	for(int i = 0; i < N-1; i++){
		g[A[i]].push_back(B[i]);
		g[B[i]].push_back(A[i]);
	}
	

	bfs(0,0);
	int p1 = max_element(d.begin(), d.end()) - d.begin();
    timer = 0;

	d[p1] = 0;
	bfs(p1,p1);
	int p2 = max_element(d.begin(), d.end()) - d.begin();

	//cout << p1 << " " << p2 << endl;

	for(int i = 1; i < 19; i++){
		for(int j = 0; j < N; j++){
			up[i][j] = up[i-1][up[i-1][j]];
		}
	}

	int M = 0;
	for(int i = 0; i < N; i++){
		if(i != p1 && i != p2){
			M = max(M, distance(p1,i) + distance(p2,i));
		}
	}
	
	return d[p2] + M;
}

int main() {
	// se vuoi leggere da file decommenta queste due linee
	assert(freopen("input.txt", "r", stdin));
	// assert(freopen("output.txt", "w", stdout));

	int n;
	assert(std::cin >> n);

	std::vector<int> a(n - 1), b(n - 1);
	for (int i = 0; i < n - 1; ++i) {
		assert(std::cin >> a[i] >> b[i]);
	}

	int ans = build(n, move(a), move(b));
	std::cout << ans << '\n';
}
