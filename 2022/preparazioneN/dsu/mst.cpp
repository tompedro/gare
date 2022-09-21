#import <bits/stdc++.h>
using namespace std;

struct Edge{
	int u, v;
	long long w; 
	bool operator<(Edge const& e){
		return w < e.w;
	}
};

vector<int> parent;
vector<int> ranks;
vector<Edge> g;

void make_set(int v){
	parent[v] = v;
	ranks[v] = 0;
}

int find_set(int v){
	if(parent[v] == v){
		return v;
	}
	return parent[v] = find_set(parent[v]);
}

void union_set(int u, int v){
	int a = find_set(u);
	int b = find_set(v);
	if(a != b){
		if(ranks[b] > ranks[a]){
			swap(a,b);
		}
		parent[b] = a;
		if(ranks[a] == ranks[b]){
			ranks[a]++;
		}
	}
}


int main(){
	int N,M;
	long long cost = 0;
	vector< pair<int,int> > result;
	cin >> N >> M;
	
	parent.resize(N);
	ranks.resize(N);
	
	for(int i = 0; i < M; i++){
		Edge e;
		cin >> e.u >> e.v >> e.w;
		e.u--;
		e.v--;
		
		g.push_back(e);	
	}
	
	for(int i = 0; i < N; i++)
		make_set(i);
		
	sort(g.begin(), g.end());

	for(Edge e: g){
		if(find_set(e.u) != find_set(e.v)){
			cost += e.w;
			result.push_back({e.u > e.v ? e.v : e.u, e.u > e.v ? e.u : e.v});
			union_set(e.u, e.v);
		}
	}
	
	sort(result.begin(), result.end());
	
	cout << cost << endl;
	for(auto e : result){
		
		cout << e.first+1 << " " << e.second+1<< endl;
	}
	
	return 0;
}
