#include <bits/stdc++.h>
using namespace std;

struct ST{
	struct Node{
		int value;
		
		Node(int v = 0){
			value = v;
		}
		
		void join(Node l, Node r){
			value = l.value + r.value;
		}
		
		void joinMin(Node l, Node r){
			value = min(l.value, r.value);
		}
	};
	vector<Node> nodes;
	vector<Node> mins;
	vector<long long> initialData;
	int n, real_size;
	
	ST(vector<long long> v){
		initialData = v;
		n = v.size();
		if(n == 0) return;
		
		real_size = 1;
		while(real_size < n)
			real_size *= 2;
			
		nodes.assign(2 * real_size, Node());
		mins.assign(2 * real_size, Node(INT_MAX));
		
		build(1,0,real_size,v);
	}
	
	void build(int u, int l, int r, vector<long long> v){
		if(r - l == 1){
			if(l < n){
				nodes[u].value = v[l];
				mins[u].value = v[l];
			}
		}else{
			build(2*u, l, (l+r)/2, v);
			build(2*u + 1, (l+r)/2, r, v);
			nodes[u].join(nodes[2*u], nodes[2*u+1]);
			mins[u].joinMin(mins[2*u],mins[2*u+1]);
		}	
	}

	void updateRange(int u, int l, int r, int a, int z, int x){
    	if(a >= r || z <= l) return;
        if(r - l == 1 && l >= a && l < z){
    		nodes[u].value = x;
    		mins[u].value = x;
    		return;
		}
		
		if(2*u > nodes.size()) return;
        
        if(a >= (l+r)/2 || z <= l){
			if(!(a >= r || z <= (l+r)/2)){
				updateRange(2*u+1, (l+r)/2, r, a, z, x);
			}
		}else {
			if (a >= r || z <= (l+r)/2){
				updateRange(2*u, l, (l+r)/2, a, z, x);
			}else{
				updateRange(2*u, l, (l+r)/2, a, z, x);
				updateRange(2*u+1, (l+r)/2, r, a, z, x);
			}	
		}
        
        nodes[u].join(nodes[2*u], nodes[2*u+1]);
        mins[u].joinMin(mins[2*u], mins[2*u+1]);
	}
	
	void updateRange(int l, int r, int x) {
		return updateRange(1, 0, real_size, l, r, x);
	}
    
    void addRange(int u, int l, int r, int a, int z, int x){
    	if(a >= r || z <= l) return;
    	if(r - l == 1 && l >= a && l < z){
    		nodes[u].value += x;
    		mins[u].value += x;
    		return;
		}

		if(2*u > nodes.size()) return;
		
		if(a >= (l+r)/2 || z <= l){
			if(!(a >= r || z <= (l+r)/2)){
				addRange(2*u+1, (l+r)/2, r, a, z, x);
			}
		}else {
			if (a >= r || z <= (l+r)/2){
				addRange(2*u, l, (l+r)/2, a, z, x);
			}else{
				addRange(2*u, l, (l+r)/2, a, z, x);
				addRange(2*u+1, (l+r)/2, r, a, z, x);
			}	
		}
		
        nodes[u].join(nodes[2*u], nodes[2*u+1]);
        mins[u].joinMin(mins[2*u], mins[2*u+1]);
	}
	
	void addRange(int l, int r, int x) {
		return addRange(1, 0, real_size, l, r, x);
	}
	
	void printTree(){
		for(int i = 0; i < nodes.size(); i++){
			cout << nodes[i].value << endl;
		}
	}
	
	long long sumRange(long long u, int a, int z, int l, int r){
		if(a >= r || z <= l) return 0;
        if(l >= a && r <= z) return nodes[u].value;
		
		if(a >= (l+r)/2 || z <= l){
			if(!(a >= r || z <= (l+r)/2)){
				return sumRange(2*u+1, a, z, (l+r)/2, r);
			}
		}else {
			if (a >= r || z <= (l+r)/2){
				return sumRange(2*u, a, z, l, (l+r)/2);
			}else{
				return sumRange(2*u, a, z, l, (l+r)/2) + sumRange(2*u+1, a, z, (l+r)/2, r);
			}	
		}
	}
	
	long long sumRange(int a, int z) {
		return sumRange(1, a, z, 0, real_size);
	}
	
	long long minRange(long long u, int a, int z, int l, int r){
		if(a >= r || z <= l) return LLONG_MAX;
        if(l >= a && r <= z) return mins[u].value;
		
		return min(
			minRange(2*u, a, z, l, (l+r)/2),
			minRange(2*u+1, a, z, (l+r)/2, r)
		);
	}
	
	long long minRange(int a, int z) {
		return minRange(1, a, z, 0, real_size);
	}
	
	long long lowerBound(int u, int l, int r, int a, int z, int x){
		if(u > mins.size()) return LLONG_MAX;
		if(a >= r || z <= l) return LLONG_MAX;
		if(mins[u].value > x)	return LLONG_MAX;
		if(r-l == 1){
			return u - (mins.size()-real_size);
		}
		
		return min(
			lowerBound(2*u, l, (l+r)/2, a, z, x),
			lowerBound(2*u+1, (l+r)/2, r, a, z, x)
		);
	}
	
	long long lowerBound(int a, int z, int x) {
		return lowerBound(1, 0, real_size, a, z, x);
	}
};

ST tree(vector<long long> (0,0));

long long get_sum(int l, int r){
	return tree.sumRange(l, r);
}
void add(int l, int r, long long x){
	tree.addRange(l,r,x);
	return;
}
void init(vector<long long> a){
	ST t(a);
	tree = t;
}
void set_range(int l, int r, long long x){
	tree.updateRange(l,r,x);
	return;
}
long long get_min(int l, int r){
	return tree.minRange(l,r);
}
int lower_bound(int l, int r, long long x){
	return tree.lowerBound(l,r,x);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	vector<long long> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	init(a);
	
	for (int i = 0; i < q; i++) {
		int op, l, r;
		long long x;
		cin >> op;
		cin >> l >> r;
		if (op == 2 or op == 3 or op == 5)
			cin >> x;
		if (op == 1) cout << get_sum(l, r) << "\n";
		if (op == 2) add(l, r, x);
		if (op == 3) set_range(l, r, x);
		if (op == 4) cout << get_min(l, r) << "\n";
		if (op == 5) cout << lower_bound(l, r, x) << "\n";
	}
	
	return 0;
}
/*
5 1
1 3 -2 8 -7
1 0 3


10 4
17 -15 13 27 -29 -6 -15 -29 1 -9
2 0 9 4
3 2 4 -22
3 6 7 3
1 0 6



*/
