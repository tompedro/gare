#include <iostream>
#include <vector>
using namespace std;

long long trova(int N);

static int N, chiamate = 0, lunghezza_massima = 0;
static vector<int> v;

long long somma(int a, int b) {
    lunghezza_massima = max(lunghezza_massima, b - a + 1);
    chiamate++;
    long long tot = 0;
    for (int i = a; i <= b; i++) tot += v[i];
    return tot;
}

long long subarray_massimo(int a, int b) {
    lunghezza_massima = max(lunghezza_massima, b - a + 1);
    chiamate++;
    long long ma = 0;
    for (int i = a; i <= b; i++) {
        for (int j = i; j <= b; j++) {
            long long tot = 0;
            for (int h = i; h <= j; h++) tot += v[h];
            if (tot > ma) ma = tot;
        }
    }
    return ma;
}

long long subarray_minimo(int a, int b) {
    lunghezza_massima = max(lunghezza_massima, b - a + 1);
    chiamate++;
    long long mi = 0;
    for (int i = a; i <= b; i++) {
        for (int j = i; j <= b; j++) {
            long long tot = 0;
            for (int h = i; h <= j; h++) tot += v[h];
            if (tot < mi) mi = tot;
        }
    }
    return mi;
}

long long trova(int N) {
    int l = 0, r = N;
    int res = -1;
    int add = 0;
    while(r-l > 1){
        int mid = (r+l)/2;
        if(somma(mid,mid) >= 0){
            l = mid;
        }else{
            r = mid;
        }
    }
    
    N = l+1;
    cout << N << endl;
    long long sum = 0;
    int j = 0;
    int a = floor(sqrt(N));
    int b = ceil(sqrt(N));
    if(a*b < N) a = b;
    for(int i = 0; i < a; i++){
        int j = (i+1)*b - 1;
        if(j >= N) j = N-1;
        sum += somma(i*b, j);
    }
    return sum;
}



int main() {
    // se preferisci leggere e scrivere da file
    // ti basta decommentare le seguenti due righe:

    assert(freopen("input.txt", "r", stdin));
    // ofstream cout("output.txt");
    cin >> N;
    v.resize(N);
    for (int i = 0; i < N; i++) cin >> v[i];
    long long ans = trova(N);
    cout << "La tua risposta e' " << ans << endl;
    cout << "Hai effettuato " << chiamate << " chiamate" << endl;
    cout << "La lunghezza massima tra le chiamate e' " << lunghezza_massima << endl;
    return 0;
}
