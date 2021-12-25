#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct ST{
	struct Node{
		ll value;
		
		Node(ll v = 0){
			value = v;
		}
		
		void join(Node l, Node r){
			value = l.value + r.value;
		}
	};
	vector<Node> sums;
	vector<ll> lazy;
	ll n;
	
	ST(vector<long long> v){
		n = v.size();
		
		while(__builtin_popcount(n) != 1){
			v.push_back(0);
			n++;
		}
		sums.resize(2*n);
		lazy.assign(2*n,0);
		
		for(ll i = 0; i < n; i++){
			sums[n + i].value = v[i]; 
			
		}
		for(ll i = n - 1; i >= 1; i--){
			sums[i].join(sums[2*i], sums[2*i+1]); 
		}
	}
	
	ll sumRange(int i, int l, int r, int a, int z){
		if(a > r || z < l) return 0;
		
		if(lazy[i] != 0){
			sums[i].value += (r-l+1)*lazy[i];
			
			if(l != r){
				lazy[2*i] += lazy[i];
				lazy[2*i+1] += lazy[i];
			}
			
			lazy[i] = 0;
		}
		
		if(a <= l && z >= r) return sums[i].value;
		
		int m = (l+r)/2;
		
		return (
			sumRange(2*i, l, m, a, z) + 
			sumRange(2*i + 1, m+1, r, a, z)
		);
	}
	
	ll sumRange(int a, int z){
		/*for(int i = 0; i < 2*n; i++) cout << sums[i].value << " ";
		cout << endl;*/
		return sumRange(1, 0, n-1, a, z);
	}
	
	
	void add(ll i, ll l, ll r, ll a, ll z, ll x){
		if(lazy[i] != 0){
			sums[i].value += (r-l+1)*lazy[i];
			
			if(l != r){
				lazy[2*i] += lazy[i];
				lazy[2*i+1] += lazy[i];
			}
			
			lazy[i] = 0;
		}
		
		if(l > r || a > r || z < l) return;
		
		if(l >= a && r <= z){
			sums[i].value += (r-l+1)*x;
			
			if(l != r){
				lazy[2*i] += x;
				lazy[2*i+1] += x;
			}
			
			return;
		}
		
		ll m = (l+r)/2;
		
		add(2*i, l, m, a, z, x);
		add(2*i + 1, m+1, r, a, z, x);
		
		sums[i].join(sums[2*i], sums[2*i+1]); 
	}
	
	void add(int a, int z, long long x){
		add(1, 0, n-1, a, z, x);/*
		for(int i = 0; i < 2*n; i++) cout << lazy[i] << " ";
		cout << endl;
		for(int i = 0; i < 2*n; i++) cout << sums[i].value << " ";
		cout << endl;*/
	}
	
	ll get(ll i, ll l, ll r, ll u){
		if(lazy[i] != 0){
			sums[i].value += (r-l+1)*lazy[i];
			
			if(l != r){
				lazy[2*i] += lazy[i];
				lazy[2*i+1] += lazy[i];
			}
			
			lazy[i] = 0;
		}
		
		if(i == n+u) return sums[i].value;
		
		ll m = (l+r)/2;
		
		if(u >= l && u <= m){
			get(2*i, l, m, u);
		}else{
			get(2*i + 1, m+1,r, u);
		}
	}
	
	ll get(ll i){
		return get(1, 0, n-1, i);
	}
};

ST tree(vector<long long> (0,0));

void add(int l, int r, long long x){
	tree.add(l,r,x);
}
void init(vector<long long> a){
	ST t(a);
	tree = t;
}

int main() {
	/*freopen("test_input.txt","r",stdin);
	freopen("output.txt","w",stdout);*/
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	vector<long long> a(n);
	for (ll i = 0; i < n; i++)
		cin >> a[i];
	init(a);
	
	for (ll i = 0; i < q; i++) {
		ll op, l, r;
		long long x;
		cin >> op;
		if (op == 2)
			cin >> x;
		if (op == 1)
			cin >> l >> r >> x;
		if (op == 2) cout << tree.get(x-1) << "\n";
		if (op == 1) add(l-1, r-1, x);
	}
	
	return 0;
}
/*
8 3
7 6 4 6 2 9 4 8
1 8 8 10
2 1
2 2
*/
