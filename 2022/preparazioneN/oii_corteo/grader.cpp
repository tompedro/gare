#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int d[1001][1001];
int N, p1, p2, d1, d2;
vector< vector<int> > g;

void bfs(int v) {
	vector<int> visited(N);
	queue <int> Q;
	Q.push(v);
	visited[v] = true;
	while (!Q.empty()) {
		int x = Q.front();
		Q.pop();
		for (auto u : g[x]) {
			if (!visited[u]) {
				visited[u] = true;
				d[v][u] = d[v][x] + 1;
				Q.push(u);
			}
		}
	}
}



bool check(int val) {
    if (d[p1][p2] < val) return false;
	vector <vector<bool>> visited(N, vector <bool> (N));
	queue <pair<int, int>> q;
	q.push({p1, p2});

	while (!q.empty()) {
		int v = q.front().first;
		int u = q.front().second;
		q.pop();

		if (v == d1 && u == d2 && d[v][u] >= val)
			return true;

		for (int x : g[v]) {
			if (d[x][u] >= val && !visited[x][u]) {
				visited[x][u] = true;
				q.push({x, u});
			}
		}

		for (int y : g[u]) {
			if (d[v][y] >= val && !visited[v][y]) {
				visited[v][y] = true;
				q.push({v, y});
			}
		}
	}

	return false;
}


int bs(int l, int r){
	if(l >= r-1){
		return check(l) ? l : r;
	}
	
}

int pianifica(int n, int M, int P1, int D1, int P2, int D2, int A[], int B[]){
	N = n, p1 = P1, d2 = D2, p2 = P2, d1 = D1;
	g.resize(N);
	for(int i = 0; i < M; i++){
		g[A[i]].push_back(B[i]);
		g[B[i]].push_back(A[i]);
	}
	for(int i = 0; i < N; i++) bfs(i);
	if (p1 == d1 && p2 == d2) return d[p1][p2];

	int l = 0, r = 1000;
	while(l < r - 1){
		int m = (l+r)/2;
		if(check(m)){
			l = m;
		}else{
			r = m;
		}
	}
	return check(l) ? l : r;
}

int main() {
	int N, M, P1, D1, P2, D2, *A, *B, i;
	
	assert(2 == scanf("%d %d", &N, &M));
	assert(2 == scanf("%d %d", &P1, &D1));
	assert(2 == scanf("%d %d", &P2, &D2));
	
	A = (int*)malloc(M * sizeof(int));
	B = (int*)malloc(M * sizeof(int));

	for (i = 0; i < M; i++)
		assert(2 == scanf("%d %d", &A[i], &B[i]));
	
	printf("%d\n", pianifica(N, M, P1, D1, P2, D2, A, B));
}
