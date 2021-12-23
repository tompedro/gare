#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
	vector<Node> sums;
	vector<Node> mins;
	int n;
	
	ST(vector<long long> v){
		n = v.size();
		
		while(__builtin_popcount(n) != 1){
			v.push_back(0);
			n++;
		}
		sums.resize(2*n);
		mins.resize(2*n);
		
		for(int i = 0; i < n; i++){
			sums[n + i].value = v[i]; 
			mins[n + i].value = v[i];
		}
		for(int i = n - 1; i >= 1; i--){
			sums[i].join(sums[2*i], sums[2*i+1]); 
			mins[i].joinMin(mins[2*i], mins[2*i+1]); 
		}
	}
	
	ll sumRange(int i, int l, int r, int a, int z){
		if(a <= l && z >= r) return sums[i].value;
		
		if(a > r || z < l) return 0;
		
		int m = (l+r)/2;
		
		return (
			sumRange(2*i, l, m, a, z) + 
			sumRange(2*i + 1, m+1, r, a, z)
		);
	}
	
	ll sumRange(int a, int z){
		return sumRange(1, 0, n-1, a, z-1);
	}
	
	ll minRange(int i, int l, int r, int a, int z){
		if(a <= l && z >= r) return mins[i].value;
		
		if(a > r || z < l) return LLONG_MAX;
		
		int m = (l+r)/2;
		
		return min(
			minRange(2*i, l, m, a, z),
			minRange(2*i + 1, m+1, r, a, z)
		);
	}
	
	ll minRange(int a, int z){
		return minRange(1, 0, n-1, a, z-1);
	}
	
	
	void add(int i, int l, int r, int a, int z, long long x){
		if(a > r || z < l) return;
		if(r == l){
			sums[i].value += x;
			mins[i].value += x;
			return;
		}
		
		int m = (l+r)/2;
		
		add(2*i, l, m, a, z, x);
		add(2*i + 1, m+1, r, a, z, x);
		
		sums[i].join(sums[2*i], sums[2*i+1]); 
		mins[i].joinMin(mins[2*i], mins[2*i+1]); 
	}
	
	void add(int a, int z, long long x){
		add(1, 0, n-1, a, z-1, x);
	}
	
	void set(int i, int l, int r, int a, int z, long long x){
		if(a > r || z < l) return;
		if(r == l){
			sums[i].value = x;
			mins[i].value = x;
			return;
		}
		
		int m = (l+r)/2;
		
		set(2*i, l, m, a, z, x);
		set(2*i + 1, m+1, r, a, z, x);
		
		sums[i].join(sums[2*i], sums[2*i+1]); 
		mins[i].joinMin(mins[2*i], mins[2*i+1]); 
	}
	void set(int a, int z, long long x){
		set(1, 0, n-1, a, z-1, x);
	}
};

ST tree(vector<long long> (0,0));

long long get_sum(int l, int r){
	return tree.sumRange(l,r);
}
void add(int l, int r, long long x){
	tree.add(l,r,x);
}
void init(vector<long long> a){
	ST t(a);
	tree = t;
}
void set_range(int l, int r, long long x){
	tree.set(l,r,x);
}
long long get_min(int l, int r){
	return tree.minRange(l,r);
}
int lower_bound(int l, int r, long long x){
	return 99999;
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

