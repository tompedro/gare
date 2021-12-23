#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	cin >> N;
	
	priority_queue<pair<long long, int> > q;
	for(int i = 0; i < N; i++){
		int a, b;
		cin >> a >> b;
		q.push({a,-1});
		q.push({b,1});
	}
	
	int m = 0;
	int c = 0;
	
	while(!q.empty()){
		auto a = q.top();
		q.pop();
		c += a.second;
		m = max(c,m);	
	}
	
	cout << m << endl;
}
