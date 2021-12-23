#include <bits/stdc++.h>
#define LOG_MAX 21
typedef long long ll;
using namespace std;

int n;
vector<ll> d;
vector<bool> visited;
vector< vector< pair<int,ll> > > adj;
vector< vector< pair<int,ll> > > ancestors;
ll mn = LLONG_MAX;
vector<int> path;

void dfs(int x){
  if(visited[x]){
    return;
  }
  visited[x] = true;

  for(auto u : adj[x]){
    if(visited[u.first]) continue;
    d[u.first] = d[x] + 1;
    ancestors[u.first][0] = {x,u.second};
    dfs(u.first);
  }
}

void pre(){
  for(int k = 1; k < LOG_MAX; k++){
    for(int i = 0; i < n; i++){
      ancestors[i][k].first = ancestors[ancestors[i][k-1].first][k-1].first;
      ancestors[i][k].second = ancestors[ancestors[i][k-1].first][k-1].second + ancestors[i][k-1].second;
    }
  }
}

pair<int,ll> anc(int u, int p){
  ll distance = 0;
  for(int i = LOG_MAX; i >= 0; i--){
    if(p & (1<<i)){
    	path.push_back(ancestors[u][i].second);
		mn = min(mn,ancestors[u][i].second);
		distance += ancestors[u][i].second;
		u = ancestors[u][i].first;
    }
  }
  return {u,distance};
}

pair<int,ll> lca(int u, int v){
	if(d[u] < d[v]) return lca(v,u);
	ll distance = 0;
	
	pair<int,ll> o = anc(u, d[u]-d[v]); 
	u = o.first;
	distance += o.second;
	// li metto sullo stesso piano
	if(u == v){
		return {u, distance};
	}
	for(int i = LOG_MAX; i >= 0; i--){
		if(ancestors[u][i].first != ancestors[v][i].first){
			path.push_back(ancestors[u][i].second);
			path.push_back(ancestors[v][i].second);
			mn = min(min(mn, ancestors[u][i].second),ancestors[v][i].second);
		  	distance += ancestors[u][i].second + ancestors[v][i].second;
		  	u = ancestors[u][i].first;
		  	v = ancestors[v][i].first;
		}
	}
	path.push_back(ancestors[u][0].second);
	path.push_back(ancestors[v][0].second);
	mn = min(min(mn, ancestors[u][0].second),ancestors[v][0].second);
	return {ancestors[u][0].first, distance + ancestors[u][0].second + ancestors[v][0].second};
}

void inizia(int N, int T, int A[], int B[], int C[]) {
	n = N;
	d.assign(n,0);
	adj.resize(n);
	visited.resize(n);
	ancestors.assign(n, vector<pair<int,ll>> (LOG_MAX+1,{0,0}));
	for (int i = 0; i < N-1; i++) {
		int a = A[i]; int b = B[i];
		adj[a].push_back({b,C[i]});
		adj[b].push_back({a,C[i]});
	}
	
	ancestors[0][0] = {0,0};
	dfs(0);
	pre();
}

long long int distanza1(int u, int v) {
	int ancestor = lca(u,v).first;
	return (d[u] - d[ancestor]) + (d[v] - d[ancestor]);
}

long long int distanza2(int u, int v) {
	ll ancestor = lca(u,v).second;
	return ancestor;
}

long long int minimo(int u, int v) {
	mn = LLONG_MAX;
	lca(u,v);
	
	return mn;
}

long long int massimo(int u, int v) {
	path.clear();
	lca(u,v);
	for(int i = 0; i < path.size(); i++){
		cout <<" => " << path[i] << endl;
	}
	return 123456789123ll;
}
/*
9 1 1
0 1 2
1 2 4
1 3 7
2 8 5
2 4 10
4 7 2
3 5 3
3 6 -1
0 6*/
