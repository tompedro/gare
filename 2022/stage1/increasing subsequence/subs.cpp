#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
vector<int> V,v;

int bs(int l, int r, int x){
	if(r > l){
		int m = (l+r)/2;
		
		if(v[m] == x) return m;
		else if(v[m] < x) return bs(m+1, r, x);
		
		return bs(l, m, x);
	}
	return l;
}
 
int main(){
	cin >> N;
	
	for(int i = 0; i < N; i++){
		int a;
		cin >> a;
		V.push_back(a);
	}
	
	v.push_back(V[0]);
	
	for(int i = 1; i < N; i++){
		if(V[i] > v[v.size() - 1]){
			v.push_back(V[i]);
		}else{
			v[bs(0,v.size()-1,V[i])] = V[i];
		}
		
	}
	cout << v.size() << endl;
	return 0;
}
