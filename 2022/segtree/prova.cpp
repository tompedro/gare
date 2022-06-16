#include <bits/stdc++.h>

using namespace std;

// Valori neutri rispettivamente per somma e minimo.
const long long NEUTRO = 0;
const long long NEUTRO_MIN = LLONG_MAX;

struct Nodo {
	long long val;
	long long mi;
	long long lazySet;
	long long lazyAdd;
	Nodo() : val(NEUTRO), mi(NEUTRO_MIN), lazySet(LLONG_MIN), lazyAdd(0) {};
	// Nodo tiene valore della somma e minimo.
	void join(Nodo &a, Nodo &b) {
		val = a.val + b.val;
		mi = min(a.mi, b.mi);
	}
};

int n, realSize;
vector<Nodo> segTree;

void isLazy(int u, int left, int right) {
	if (segTree[u].lazySet != LLONG_MIN) {
		// Sei lazy! Impostati!
		segTree[u].val = (right - left) * segTree[u].lazySet;
		segTree[u].mi = segTree[u].lazySet;
		if ((u * 2) + 1 < segTree.size()) {
			segTree[u * 2].lazySet = segTree[u].lazySet;
			segTree[(u * 2) + 1].lazySet = segTree[u].lazySet;
		}
		segTree[u].lazySet = LLONG_MIN;
	}
	if (segTree[u].lazyAdd != 0) {
		// Sei lazy! Impostati!
		segTree[u].val += (right - left) * segTree[u].lazyAdd;
		segTree[u].mi += segTree[u].lazyAdd;
		if ((u * 2) + 1 < segTree.size()) {
			segTree[u * 2].lazyAdd += segTree[u].lazyAdd;
			segTree[(u * 2) + 1].lazyAdd += segTree[u].lazyAdd;
		}
		segTree[u].lazyAdd = 0;
	}
}

void build(int u, int l, int r, vector<long long> &dati);
void init(vector<long long> a) {
	n = a.size();
	realSize = 1;
	while (realSize < n) {
		// grandezza del vettore deve essere una potenza di due.
		realSize *= 2;
	}
	// prima metà si tiene l'albero binario, seconda metà i dati.
	segTree.assign(realSize * 2, Nodo());
	build(1, 0, realSize, a);
}

void build(int u, int l, int r, vector<long long> &dati) {
	if (r - l <= 1) {
		// Sono una foglia, quindi imposto il valore direttamente
		// Se elemento è effettivamente un elemento, essendo dati non per forza una potenza di 2
		if (l < dati.size()) {
			segTree[u].val = dati[l];
			segTree[u].mi = dati[l];
		}
	} else {
		// Non sono una foglia, ricorro...
		build(u * 2, l, (l + r)/2, dati);
		build((u * 2) + 1, (l + r)/2, r, dati);
		// joino i risultati
		segTree[u].join(segTree[u * 2], segTree[u * 2 + 1]);
	}
}

long long get_min(int u, int left, int right, int l, int r) {
	if (r <= left || l >= right) {
		// Non compreso nel mio insieme. Mi fermo quì!
		return NEUTRO_MIN;
	}
	if (left >= l && right <= r) {
		// Mi piace, mi fermo quì
		return segTree[u].mi;
	}
	isLazy(u, left, right);

	// Devo ricorrere 😭
	return min(
			get_min(u * 2, left, (left + right) / 2, l, r),
			get_min((u * 2) + 1, (left + right) / 2, right, l, r)
			);
}
long long get_sum(int u, int left, int right, int l, int r) {
	if (r <= left || l >= right) {
		// Non compreso nel mio insieme. Mi fermo quì!
		return NEUTRO;
	}
	if (left >= l && right <= r) {
		// Mi piace, mi fermo quì
		return segTree[u].val;
	}
	isLazy(u, left, right);

	// Devo ricorrere 😭
	return (
			get_sum(u * 2, left, (left + right) / 2, l, r) +
			get_sum((u * 2) + 1, (left + right) / 2, right, l, r)
			);
}

long long get_min(int l, int r) {return get_min(1, 0, realSize, l, r); }
long long get_sum(int l, int r) {return get_sum(1, 0, realSize, l, r); }

void set_range(int u, int left, int right, int l, int r, long long x) {
	isLazy(u, left, right);
	if (l >= right || r <= left) return;
	if (left >= l && right <= r) {
		// Sono interamente contenuto, aggiorno il valore
		// e metto lazy i figli
		segTree[u].val = (right - left) * x;
		segTree[u].mi = x;
		if ((u * 2) + 1 < segTree.size()) {
		    segTree[u * 2].lazyAdd = 0;
			segTree[(u * 2) + 1].lazyAdd = 0;
			segTree[u * 2].lazySet = x;
			segTree[(u * 2) + 1].lazySet = x;
		}
	} else {
		// Non sono una foglia, ricorro...
		set_range(u * 2, left, (left + right)/2, l, r, x);
		set_range((u * 2) + 1, (left + right)/2, right, l, r, x);
		// joino i risultati
		segTree[u].join(segTree[u * 2], segTree[u * 2 + 1]);
	}
}
void set_range(int l, int r, long long x) {set_range(1, 0, realSize, l, r, x);}

void add(int u, int left, int right, int l, int r, long long x) {
	isLazy(u, left, right);
	if (l >= right || r <= left) return;
	if (left >= l && right <= r) {
		// Sono interamente contenuto, aggiorno il valore
		// e metto lazy i figli
		segTree[u].val += (right - left) * x;
		segTree[u].mi += x;
		if ((u * 2) + 1 < segTree.size()) {
		    
			segTree[u * 2].lazyAdd += x;
			segTree[(u * 2) + 1].lazyAdd += x;
		}
	} else {
		// Non sono una foglia, ricorro...
		add(u * 2, left, (left + right)/2, l, r, x);
		add((u * 2) + 1, (left + right)/2, right, l, r, x);
		// joino i risultati
		segTree[u].join(segTree[u * 2], segTree[u * 2 + 1]);
	}
}
void add(int l, int r, long long x) {
	if (x == 0) return;
	add(1, 0, realSize, l, r, x);
}

int lower_bound(int u, int left, int right, int l, int r, long long x) {
	isLazy(u, left, right);
	if ((r <= left || l >= right) || segTree[u].mi > x) {
		// NON VA BENE 😭
		return -1;
	}
	if (right - left <= 1) {
		// Che bello! Sono una foglia 😁
		return left;
	}

	int le = lower_bound(u * 2, left, (left + right) / 2, l, r, x);
	if (le != -1) return le;

	int ri = lower_bound((u * 2) + 1, (left + right) / 2, right, l, r, x);
	return ri;
}

int lower_bound(int l, int r, long long x) {
	return lower_bound(1, 0, realSize, l, r, x);
}