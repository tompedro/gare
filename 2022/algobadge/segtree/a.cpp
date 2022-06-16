#include <vector>
#include <iostream>
#include <limits>
#include <climits>
using namespace std;
typedef long long ll;
constexpr long long inf = LLONG_MAX;
struct ST{
	struct Node{
		ll sum;
		ll m;
		ll lazy;
		ll lazySet;
		
		Node(ll s = 0, ll mi = inf){
			sum = s;
			m = mi;
			lazy = 0;
			lazySet = LLONG_MIN;
		}
		
		void join(Node l, Node r){
			sum = l.sum + r.sum;
			m = min(l.m, r.m);
			l.lazy = r.lazy = 0;
			l.lazySet = r.lazySet = LLONG_MIN;
			lazy = 0;
			lazySet = LLONG_MIN;
		}
	};
	vector<Node> tree;
	ll n;
	

	ST(vector<long long> v){
		ll initialSize = v.size();
		n = v.size();
		
		while(__builtin_popcount(n) != 1){
			v.push_back(0);
			n++;
		}
		tree.assign(2*n, Node());
		
		for(ll i = 0; i < n; i++){
			tree[n + i].sum = v[i]; 
			if(i >= initialSize){
				tree[n + i].m = inf;
			}else{
				tree[n + i].m = v[i];
			}
			
		}
		for(ll i = n - 1; i >= 1; i--){
			tree[i].join(tree[2*i], tree[2*i+1]); 
		}
	}

	void updateLazy(ll i, ll l, ll r){
		if(tree[i].lazySet != LLONG_MIN){
			tree[i].sum = (r-l)*tree[i].lazySet;
			tree[i].m = tree[i].lazySet;
			
			if(2*i + 1 < tree.size()){
				tree[2*i].lazy =  0;
				tree[2*i+1].lazy = 0;
				tree[2*i].lazySet = tree[i].lazySet;
				tree[2*i+1].lazySet = tree[i].lazySet;
			}
			
			tree[i].lazySet = LLONG_MIN;
		}

		if(tree[i].lazy != 0){
			tree[i].sum += (r-l)*tree[i].lazy;
			tree[i].m += tree[i].lazy;
			
			if(2*i + 1 < tree.size()){
				tree[2*i].lazy += tree[i].lazy;
				tree[2*i+1].lazy += tree[i].lazy;
			}
			
			tree[i].lazy = 0;
		}
	}
	
	ll sumRange(ll i, ll l, ll r, ll a, ll z){
		updateLazy(i,l,r);
		if (z <= l || a >= r) return 0;
		if(a <= l && z >= r) return tree[i].sum;

		ll m = (l+r)/2;
		
		return (
			sumRange(2*i, l, m, a, z) + 
			sumRange(2*i + 1, m, r, a, z)
		);
	}
	
	ll sumRange(ll a, ll z){
		return sumRange(1, 0, n, a, z);
	}
	
	ll minRange(ll i, ll l, ll r, ll a, ll z){
		updateLazy(i,l,r);
		if (z <= l || a >= r) return inf;
		if(a <= l && z >= r) return tree[i].m;

		ll m = (l+r)/2;
		return min(
			minRange(2*i, l, m, a, z),
			minRange(2*i + 1, m, r, a, z)
		);
	}
	
	ll minRange(ll a, ll z){
		return minRange(1, 0, n, a, z);
	}
	
	
	void add(ll i, ll l, ll r, ll a, ll z, long long x){
		updateLazy(i,l,r);
		
		if(a >= r || z <= l) return;
		
		if(l >= a && r <= z){
			tree[i].sum += (r-l)*x;
			tree[i].m += x;
			
			if(2*i + 1 < tree.size()){
				tree[2*i].lazy += x;
				tree[2*i+1].lazy += x;
			}
			
			return;
		}
		
		ll m = (l+r)/2;
		
		add(2*i, l, m, a, z, x);
		add(2*i + 1, m, r, a, z, x);
		
		tree[i].join(tree[2*i], tree[2*i+1]); 
	}
	
	void add(ll a, ll z, long long x){
		if (x == 0) return;
		add(1, 0, n, a, z, x);
	}
	
	void set(ll i, ll l, ll r, ll a, ll z, long long x){
		updateLazy(i,l,r);
		
		if(a >= r || z <= l) return;
		if(l >= a && r <= z){
			tree[i].sum = (r-l)*x;
			tree[i].m = x;

			if(2*i + 1 < tree.size()){
				tree[2*i].lazy = 0;
				tree[2*i+1].lazy = 0;
				tree[2*i].lazySet = x;
				tree[2*i+1].lazySet = x;
			}
			
			return;
		}
		
		ll m = (l+r)/2;
		
		set(2*i, l, m, a, z, x);
		set(2*i + 1, m, r, a, z, x);
		
		tree[i].join(tree[2*i], tree[2*i+1]);
	}
	void set(ll a, ll z, long long x){
		set(1, 0, n, a, z, x);
	}
	long long lower_bound(ll i, ll l, ll r, ll a, ll z, ll x){
		updateLazy(i,l,r);
		if ((z <= l || a >= r) || tree[i].m > x) {
			return -1;
		}
		if (r - l <= 1) {
			return l;
		}

		int le = lower_bound(i * 2, l, (l + r) / 2, a, z, x);
		if (le != -1) return le;

		int ri = lower_bound((i * 2) + 1, (l + r) / 2, r, a, z, x);
		return ri;
	}
	
	long long lower_bound(ll a, ll z, ll x) {
		return lower_bound(1, 0, n, a, z, x);
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
int lower_bound(int  l, int  r, long long x){
	ll a = tree.lower_bound(l,r,x);
	if(a == inf) return -1;
	
	return a;
}


int main() {
	ios::sync_with_stdio(false);
	freopen("input.txt","r", stdin);
	freopen("output.txt","w", stdout);
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
		cout << "compio : " << op << " " << l << " " << r << endl;
		if (op == 1) cout << get_sum(l, r) << "\n";
		if (op == 2) add(l, r, x);
		if (op == 3) set_range(l, r, x);
		if (op == 4) cout << get_min(l, r) << "\n";
		if (op == 5) cout << lower_bound(l, r, x) << "\n";
	}
	
	return 0;
}
