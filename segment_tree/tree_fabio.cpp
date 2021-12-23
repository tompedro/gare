#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
 
ll n, q;
vi tree;
 
// i -> indice nodo corrente nell'albero
// l -> figlio piu' a sinistra che fa parte del subtree da i
// r -> figlio piu' a destra che fa parte del subtree da i
// l e r costituiscono il range di ricerca di ogni chiamata ricorsiva
// partono rispettivamente 0 e n-1, poi diventano 0 e n/2 a sinistra e n/2+1 e n-1 a destra
// a e b sono gli estremi destro e sinistro della query richiesta
// LA ROOT E' 1, GLI INDICI SONO ZERO BASED, ENTRAMBI GLI ESTREMI SONO INCLUSI
ll query(int i, int l, int r, int a, int b) {
   // se il range su cui facciamo la query e' incluso nel range di ricerca
   // allora restituisci il nodo corrente
   if (a <= l and r <= b) return tree[i];
   // se il range che stiamo guardando (l e r) sta fuori dal range richiesto (a e b)
   // allora restituisci 0
   if (r < a or l > b) return 0;
   // m e' semplicemente il mezzo tra l e r
   int m = (l + r) / 2;
   // restituisci la somma tra la query eseguita sul subtree sinistro
   // e la query eseguita sul subtree destro
   return (
      query(2*i, l, m, a, b) +
      query(2*i+1, m+1, r, a, b)
   );
}
 
void update(int k, int val) {
   // update della foglia
   // siccome l'indice e' dato tra 0 e n-1 bisogna aggiungere perche'
   // le foglie stanno tra n e 2*n - 1
   tree[n + k] = val;
   // parti dal diretto parente della foglia (n+k)/2
   // continua fino alla root compresa (indice 1)
   // dimezza ogni volta (>>= 1 e' la stessa cosa che /= 2)
   // quindi salta al parente del nodo
   for (int i = (n+k)/2; i >= 1; i >>= 1)
      // la funzione per combinare 2 nodi e' una semplice somma
      tree[i] = tree[2*i] + tree[2*i+1];
}
 
int main() {
   cin >> n >> q;
   // v e' il vettore che terra' gli elementi
   vi v(n);
   for (int i = 0; i < n; i++) cin >> v[i];
   // __builtin_popcount(n) conta gli 1 presenti nella rappresentazione
   // in binario del numero
   // se __builtin_popcount(n) restituisce 1 vuol dire che il numero e'
   // una potenza di 2
   while (__builtin_popcount(n) != 1) {
      // fai un padding fino alla potenza di 2 piu' vicina
      v.push_back(0);
      n++;
   }
   
   tree.resize(2*n);
   // inserisci i dati nella seconda meta' dell'albero;
   for (int i = 0; i < n; i++) tree[n + i] = v[i];
   // partendo da n-1 strato per strato fino alla root costruisci l'albero
   for (int i = n-1; i >= 1; i--) tree[i] = tree[2*i] + tree[2*i+1];
 
   int type;
   int a;
   int b;
 
   while (q--) {
      cin >> type >> a >> b;
      if (type == 1)
         // da ricordare che in input gli indici sono 1 based
         update(a-1, b);
      else
         cout << query(1, 0, n-1, a-1, b-1) << endl;
   }
}