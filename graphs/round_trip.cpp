#include <iostream>
#include <vector>
using namespace std;

vector<bool> visited;
vector<vector<int> > adj;
int start = 0;
bool isCyclic = false;
vector<int> finalRoad;

void dfs(int i, vector<int> road){
    if(isCyclic) return;
    if(visited[i]){
        return;
    }
    cout << "entro con "<< i << endl;
    road.push_back(i);
    visited[i] = true;

    for(int u = 0; u < adj[i].size(); u++){ 
        if(isCyclic) return;
        if(adj[i][u] == start && road.size() > 2){
            isCyclic = true;
            finalRoad = road;
            return;
        }
        if(visited[adj[i][u]]) continue;
        dfs(adj[i][u], road);
    }
}


int main(){
    freopen("inputRT.txt","r",stdin);
    int N,M;
    cin >> N >> M;
    adj.resize(N);
    visited.assign(N,0);

    for(int i = 0; i < M; i++){
        int a,b;
        cin >> a >> b;

        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }

    for(int i = 0; i < N; i++){
        start = i;
        visited.assign(N,0);
        vector<int> a(0);
        dfs(i, a);
        if(isCyclic){
            cout << finalRoad.size()+1 << endl;
            for(int j = 0; j < finalRoad.size(); j++) cout << finalRoad[j]+1 << " ";
            cout << start+1 << endl;
            exit(0);
        }
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}