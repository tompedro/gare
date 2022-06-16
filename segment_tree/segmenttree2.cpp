#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

struct ST{
	struct Node{
		ll value;
		ll valueMin;
		queue<pair<int,int> > lazy;
		
		Node(ll v = 0){
			value = v;
			valueMin = v;
		}
		
		void join(Node l, Node r){
			value = l.value + r.value;
			valueMin = min(l.valueMin, r.valueMin);
		}

		void addLazy(queue<pair<int,int> > p){
			while(!p.empty()){
				pair<int,int> a = p.front();
				p.pop();
				lazy.push(a);
			}
		}

		queue<pair<int,int> > apply(int l, int r){
			queue<pair<int,int> > q;
			q = lazy;
			while(!lazy.empty()){
				pair<int,int> a;
				a = lazy.front();
				lazy.pop();
				if(a.first == 0){
					value += a.second*(r-l+1);
					valueMin += a.second;
				}else{
					value = a.second*(r-l+1);
					valueMin = a.second;
				}
			}
			return q;
		}

		bool isLazy() {return !lazy.empty();}
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
		tree.resize(2*n);
		
		for(ll i = 0; i < n; i++){
			tree[n + i].value = v[i]; 
			if(i >= initialSize){
				tree[n + i].valueMin = LLONG_MAX;
			}else{
				tree[n + i].valueMin = v[i];
			}
			
		}
		for(ll i = n - 1; i >= 1; i--){
			tree[i].join(tree[2*i], tree[2*i+1]);
		}
	}
	
	ll sumRange(ll i, ll l, ll r, ll a, ll z){
		if(a > r || z < l) return 0;
		
		if(tree[i].isLazy()){
			queue<pair<int,int> > u = tree[i].apply(l,r);
			
			if(l != r){
				tree[2*i].addLazy(u);
				tree[2*i+1].addLazy(u);
			}
		}
		
		if(a <= l && z >= r) return tree[i].value;
		
		ll m = (l+r)/2;
		
		return (
			sumRange(2*i, l, m, a, z) + 
			sumRange(2*i + 1, m+1, r, a, z)
		);
	}
	
	ll sumRange(ll a, ll z){
		/*for(ll i = 0; i < 2*n; i++) cout << tree[i].value << " ";
		cout << endl;*/
		return sumRange(1, 0, n-1, a, z-1);
	}
	
	ll minRange(ll i, ll l, ll r, ll a, ll z){
		if(a > r || z < l) return LLONG_MAX;
		
		if(tree[i].isLazy()){
			queue<pair<int,int> > u = tree[i].apply(l,r);
			
			if(l != r){
				tree[2*i].addLazy(u);
				tree[2*i+1].addLazy(u);
			}
		}
		
		if(a <= l && z >= r) return tree[i].valueMin;
		
		ll m = (l+r)/2;
		
		return min(
			minRange(2*i, l, m, a, z),
			minRange(2*i + 1, m+1, r, a, z)
		);
	}
	
	ll minRange(ll a, ll z){
		/*for(ll i = 0; i < 2*n; i++) cout << tree[i].value << " ";
		cout << endl;*/
		return minRange(1, 0, n-1, a, z-1);
	}
	
	
	void add(ll i, ll l, ll r, ll a, ll z, long long x){
		if(tree[i].isLazy()){
			queue<pair<int,int> > u = tree[i].apply(l,r);
			
			if(l != r){
				tree[2*i].addLazy(u);
				tree[2*i+1].addLazy(u);
			}
		}
		
		if(l > r || a > r || z < l) return;
		
		if(l >= a && r <= z){
			tree[i].value += (r-l+1)*x;
			tree[i].valueMin += x;
			
			if(l != r){
				queue<pair<int,int> > u;
				u.push(make_pair(0,x));
				tree[2*i].addLazy(u);
				tree[2*i+1].addLazy(u);
			}
			
			return;
		}
		
		ll m = (l+r)/2;
		
		add(2*i, l, m, a, z, x);
		add(2*i + 1, m+1, r, a, z, x);
		
		tree[i].join(tree[2*i], tree[2*i+1]);
	}
	
	void add(ll a, ll z, long long x){
		/*for(ll i = 0; i < 2*n; i++) cout << tree[i].value << " ";
		cout << endl;*/
		add(1, 0, n-1, a, z-1, x);
	}
	
	void set(ll i, ll l, ll r, ll a, ll z, long long x){
		if(tree[i].isLazy()){
			queue<pair<int,int> > u = tree[i].apply(l,r);
			
			if(l != r){
				tree[2*i].addLazy(u);
				tree[2*i+1].addLazy(u);
			}
		}
		
		if(l > r || a > r || z < l) return;
		
		if(l >= a && r <= z){
			tree[i].value = x*(r-l+1);
			tree[i].valueMin = x;
			
			if(l != r){
				queue<pair<int,int> > u;
				u.push(make_pair(1,x));
				tree[2*i].addLazy(u);
				tree[2*i+1].addLazy(u);
			}
			
			return;
		}
		
		ll m = (l+r)/2;
		
		set(2*i, l, m, a, z, x);
		set(2*i + 1, m+1, r, a, z, x);
		
		tree[i].join(tree[2*i], tree[2*i+1]);
	}
	void set(ll a, ll z, long long x){
		/*for(ll i = 0; i < 2*n; i++) cout << tree[i].value << " ";
		cout << endl;*/
		set(1, 0, n-1, a, z-1, x);
	}
	long long lower_bound(ll i, ll l, ll r, ll a, ll z, ll x){
		if(i > tree.size()) return LLONG_MAX;
		if(a >= r || z <= l) return LLONG_MAX;
		if(tree[i].valueMin > x)	return LLONG_MAX;
		
		if(tree[i].isLazy()){
			queue<pair<int,int> > u = tree[i].apply(l,r);
			
			if(l != r){
				tree[2*i].addLazy(u);
				tree[2*i+1].addLazy(u);
			}
		}
		
		if(r-l == 1){
			return i - (tree.size()-n);
		}
		
		return min(
			lower_bound(2*i, l, (l+r)/2, a, z, x),
			lower_bound(2*i+1, (l+r)/2, r, a, z, x)
		);
	}
	
	long long lower_bound(ll a, ll z, ll x) {
		/*for(ll i = 0; i < 2*n; i++) cout << tree[i].value << " ";
		cout << endl;*/
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
