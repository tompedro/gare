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
        ll MIN;
        ll lazy_sum;
        ll lazy_set;

        Node(ll s = 0, ll m = 0){
            sum = s;
            MIN = m;
            lazy_sum = 0; lazy_set = LLONG_MIN;
        }

        void join(Node l, Node r){
            sum = l.sum + r.sum;
            MIN = min(l.MIN, r.MIN);
            l.lazy_sum = r.lazy_sum = lazy_sum = 0;
            l.lazy_set = r.lazy_set = lazy_set = LLONG_MIN;
        }
    };

    vector<Node> tree;
    ll n;

    ST(vector<ll> a){
        ll initialSize = a.size();
        n = initialSize;

        while(__builtin_popcount(n) != 1){
            a.push_back(0); n++;
        }

        tree.assign(2*n, Node());

        for(ll i = 0; i < n; i++){
            tree[n+i] = Node(a[i], i >= initialSize ? inf : a[i]);
        }

        for(ll i = n-1; i >= 1; i--){
            tree[i].join(tree[2*i], tree[2*i+1]);
        }
    }

    void updateLazy(int x, int l, int r){
        if(tree[x].lazy_set != LLONG_MIN){
            tree[x].sum = (r-l)*tree[x].lazy_set;
            tree[x].MIN = tree[x].lazy_set;

            if(2*x + 1 < 2*n){ // non mi trovo nell'ultimo
                tree[2*x].lazy_sum = 0;
                tree[2*x+1].lazy_sum = 0;
                tree[2*x].lazy_set = tree[x].lazy_set;
                tree[2*x+1].lazy_set = tree[x].lazy_set;
            }

            tree[x].lazy_set = LLONG_MIN;
        }

        if(tree[x].lazy_sum != 0){
            tree[x].sum += (r-l)*tree[x].lazy_sum;
            tree[x].MIN += tree[x].lazy_sum;

            if(2*x + 1 < 2*n){ // non mi trovo nell'ultimo
                tree[2*x].lazy_sum += tree[x].lazy_sum;
                tree[2*x+1].lazy_sum += tree[x].lazy_sum;
            }

            tree[x].lazy_sum = 0;
        }
    }

    ll sumRange(ll i, ll l, ll r, ll a, ll z){
        updateLazy(i,l,r);
        if(l >= z || r <= a) return 0;
        if(l >= a && r <= z) return tree[i].sum;

        ll m = (r+l)/2;

        return sumRange(2*i, l, m, a, z) + sumRange(2*i+1, m, r, a, z); 
	}
	
	ll sumRange(ll a, ll z){
		return sumRange(1, 0, n, a, z);
	}
	
	ll minRange(ll i, ll l, ll r, ll a, ll z){
		updateLazy(i,l,r);
        if(l >= z || r <= a) return inf;
        if(l >= a && r <= z) return tree[i].MIN;

        ll m = (r+l)/2;

        return minRange(2*i, l, m, a, z) + minRange(2*i+1, m, r, a, z);
	}
	
	ll minRange(ll a, ll z){
		return minRange(1, 0, n, a, z);
	}
	
	
	void add(ll i, ll l, ll r, ll a, ll z, long long x){
		updateLazy(i,l,r);
        if(l >= z || r <= a) return;
        if(l >= a && r <= z) {//spingo in giu
            tree[i].sum += (r-l)*x;
            tree[i].MIN += x;

            if(2*i + 1 < 2*n){ // non mi trovo nell'ultimo
                tree[2*i].lazy_sum += x;
                tree[2*i+1].lazy_sum += x;
            }
            return;
        }

        ll m = (r+l)/2;

        add(2*i,l,m,a,z,x);
        add(2*i+1,m,r,a,z,x);

        tree[i].join(tree[2*i], tree[2*i+1]);
	}
	
	void add(ll a, ll z, long long x){
		if (x == 0) return;
		add(1, 0, n, a, z, x);
	}
	
	void set(ll i, ll l, ll r, ll a, ll z, long long x){
		updateLazy(i,l,r);
        if(l >= z || r <= a) return;
        if(l >= a && r <= z) {//spingo in giu
            tree[i].sum = (r-l)*x;
            tree[i].MIN = x;

            if(2*i + 1 < 2*n){ // non mi trovo nell'ultimo
                tree[2*i].lazy_sum = 0;
                tree[2*i+1].lazy_sum = 0;
                tree[2*i].lazy_set = x;
                tree[2*i+1].lazy_set = x;
            }
            return;
        }

        ll m = (r+l)/2;

        set(2*i,l,m,a,z,x);
        set(2*i+1,m,r,a,z,x);

        tree[i].join(tree[2*i], tree[2*i+1]);
	}
	void set(ll a, ll z, long long x){
		set(1, 0, n, a, z, x);
	}
	long long lower_bound(ll i, ll l, ll r, ll a, ll z, ll x){
		updateLazy(i,l,r);
        if(l >= z || r <= a || tree[i].MIN > x) return -1;
        if(r-l <= 1) return i;

        ll mid = (r+l)/2;

        ll left = lower_bound(2*i, l, mid, a, z,x);
        if(left != -1) return left; 

        ll right = lower_bound(2*i+1, mid, l, a, z,x);
        return right;
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
