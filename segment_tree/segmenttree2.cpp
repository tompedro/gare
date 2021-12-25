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
		
		void joinMin(Node l, Node r){
			value = min(l.value, r.value);
		}
	};
	vector<Node> sums;
	vector<Node> mins;
	vector<ll> lazy;
	ll n;
	
	ST(vector<long long> v){
		ll initialSize = v.size();
		n = v.size();
		
		while(__builtin_popcount(n) != 1){
			v.push_back(0);
			n++;
		}
		sums.resize(2*n);
		mins.resize(2*n);
		lazy.assign(2*n,0);
		
		for(ll i = 0; i < n; i++){
			sums[n + i].value = v[i]; 
			if(i >= initialSize){
				mins[n + i].value = LLONG_MAX;
			}else{
				mins[n + i].value = v[i];
			}
			
		}
		for(ll i = n - 1; i >= 1; i--){
			sums[i].join(sums[2*i], sums[2*i+1]); 
			mins[i].joinMin(mins[2*i], mins[2*i+1]); 
		}
	}
	
	ll sumRange(ll i, ll l, ll r, ll a, ll z){
		if(a > r || z < l) return 0;
		
		if(lazy[i] != 0){
			sums[i].value += (r-l+1)*lazy[i];
			mins[i].value += lazy[i];
			
			if(l != r){
				lazy[2*i] += lazy[i];
				lazy[2*i+1] += lazy[i];
			}
			
			lazy[i] = 0;
		}
		
		if(a <= l && z >= r) return sums[i].value;
		
		ll m = (l+r)/2;
		
		return (
			sumRange(2*i, l, m, a, z) + 
			sumRange(2*i + 1, m+1, r, a, z)
		);
	}
	
	ll sumRange(ll a, ll z){
		/*for(ll i = 0; i < 2*n; i++) cout << sums[i].value << " ";
		cout << endl;*/
		return sumRange(1, 0, n-1, a, z-1);
	}
	
	ll minRange(ll i, ll l, ll r, ll a, ll z){
		if(a > r || z < l) return LLONG_MAX;
		
		if(lazy[i] != 0){
			sums[i].value += (r-l+1)*lazy[i];
			mins[i].value += lazy[i];
			
			if(l != r){
				lazy[2*i] += lazy[i];
				lazy[2*i+1] += lazy[i];
			}
			
			lazy[i] = 0;
		}
		
		if(a <= l && z >= r) return mins[i].value;
		
		ll m = (l+r)/2;
		
		return min(
			minRange(2*i, l, m, a, z),
			minRange(2*i + 1, m+1, r, a, z)
		);
	}
	
	ll minRange(ll a, ll z){
		//ll res = minRange(1, 0, n-1, a, z-1);
		/*for(ll i = 0; i < 2*n; i++) cout << lazy[i] << " ";
		cout << endl;
		for(ll i = 0; i < 2*n; i++) cout << mins[i].value << " ";
		cout << endl;*/
		return minRange(1, 0, n-1, a, z-1);
	}
	
	
	void add(ll i, ll l, ll r, ll a, ll z, long long x){
		if(lazy[i] != 0){
			sums[i].value += (r-l+1)*lazy[i];
			mins[i].value += lazy[i];
			
			if(l != r){
				lazy[2*i] += lazy[i];
				lazy[2*i+1] += lazy[i];
			}
			
			lazy[i] = 0;
		}
		
		if(l > r || a > r || z < l) return;
		
		if(l >= a && r <= z){
			sums[i].value += (r-l+1)*x;
			mins[i].value += x;
			
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
		mins[i].joinMin(mins[2*i], mins[2*i+1]); 
	}
	
	void add(ll a, ll z, long long x){
		add(1, 0, n-1, a, z-1, x);
		/*for(ll i = 0; i < 2*n; i++) cout << lazy[i] << " ";
		for(ll i = 0; i < 2*n; i++) cout << sums[i].value << " ";
		cout << endl;*/
	}
	
	void set(ll i, ll l, ll r, ll a, ll z, long long x){
		if(lazy[i] != 0){
			sums[i].value += (r-l+1)*lazy[i];
			mins[i].value += lazy[i];
			
			if(l != r){
				lazy[2*i] += lazy[i];
				lazy[2*i+1] += lazy[i];
			}
			
			lazy[i] = 0;
		}
		
		if(a > r || z < l) return;
		if(r == l){
			sums[i].value = x;
			mins[i].value = x;
			return;
		}
		
		ll m = (l+r)/2;
		
		set(2*i, l, m, a, z, x);
		set(2*i + 1, m+1, r, a, z, x);
		
		sums[i].join(sums[2*i], sums[2*i+1]); 
		mins[i].joinMin(mins[2*i], mins[2*i+1]); 
	}
	void set(ll a, ll z, long long x){
		set(1, 0, n-1, a, z-1, x);
	}
	long long lower_bound(ll i, ll l, ll r, ll a, ll z, ll x){
		if(i > mins.size()) return LLONG_MAX;
		if(a >= r || z <= l) return LLONG_MAX;
		if(mins[i].value > x)	return LLONG_MAX;
		
		if(lazy[i] != 0){
			sums[i].value += (r-l+1)*lazy[i];
			mins[i].value += lazy[i];
			
			if(l != r){
				lazy[2*i] += lazy[i];
				lazy[2*i+1] += lazy[i];
			}
			
			lazy[i] = 0;
		}
		
		if(r-l == 1){
			return i - (mins.size()-n);
		}
		
		return min(
			lower_bound(2*i, l, (l+r)/2, a, z, x),
			lower_bound(2*i+1, (l+r)/2, r, a, z, x)
		);
	}
	
	long long lower_bound(ll a, ll z, ll x) {
		return lower_bound(1, 0, n-1, a, z-1, x);
	}
};

ST tree(vector<long long> (0,0));

long long get_sum(ll l, ll r){
	return tree.sumRange(l,r);
}
void add(ll l, ll r, long long x){
	tree.add(l,r,x);
}
void init(vector<long long> a){
	ST t(a);
	tree = t;
}
void set_range(ll l, ll r, long long x){
	tree.set(l,r,x);
}
long long get_min(ll l, ll r){
	return tree.minRange(l,r);
}
ll lower_bound(ll l, ll r, long long x){
	ll a = tree.lower_bound(l,r,x);
	if(a == LLONG_MAX) return -1;
	return a;
}

int main() {
	freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	ll n, q;
	cin >> n >> q;
	
	vector<long long> a(n);
	for (ll i = 0; i < n; i++)
		cin >> a[i];
	init(a);
	
	for (ll i = 0; i < q; i++) {
		ll op, l, r;
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
1 2 3 4 5
2 0 3 7
*/
