#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

// Declaring functions
void mincammino(int N, int M, vector<int> X, vector<int> Y, vector<int> P, vector<int> &D){
    vector<pair<int,int>> adj[N];
    bool processed[M];
    for(int j = 0; j < M; j++){
        processed[j] = false;
        adj[X[j]].push_back(make_pair(Y[j], P[j]));
    }

    
    priority_queue<pair<int,int>> q;
    for (int i = 0; i < N; i++) D[i] = 2147483647;
    D[0] = 0;
    q.push({0,0});

    while (!q.empty()) {
        int a = q.top().second; q.pop();
        if (processed[a]) continue;
        processed[a] = true;
        for (auto u : adj[a]) {
            int b = u.first, w = u.second;
            if (D[a]+w < D[b]) {
                D[b] = D[a]+w;
                q.push({-D[b],b});
            }
        }
    }

    for (int i = 0; i < N; i++) D[i] = (D[i] == 2147483647 ? -1 : D[i]);
}

int main() {
    ios::sync_with_stdio(false);

    // Uncomment the following lines if you want to read/write from files
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    // Reading input
    int N, M;
    cin >> N >> M;

    vector<int> X(M), Y(M), P(M), D(N);
    for (int i = 0; i < M; i++) {
        cin >> X[i] >> Y[i] >> P[i];
    }

    // Calling functions
    mincammino(N, M, move(X), move(Y), move(P), D);

    // Writing output
    for(int d : D) {
        cout << d << " ";
    }
    cout << endl;

    return 0;
}
