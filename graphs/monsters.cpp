#include <iostream>
#include <vector>
#include <string>
using namespace std;

pair<int,int> start;
int N,M;
bool possible = false;
vector<char> path;

vector<pair<int,int> > move(vector<vector<char> > &lab, pair<int,int> posPlayer, vector<pair<int,int> > &m){
    vector<pair<int,int> > res; 
    for(pair<int,int> pos : m){
        if(pos.second > 0 && lab[pos.second - 1][pos.first] == '.' && pos.second > posPlayer.second){
            lab[pos.second - 1][pos.first] = 'M';
            lab[pos.second][pos.first] = '.';
            pos.second -= 1;
        } else if(pos.second < N-1 && lab[pos.second + 1][pos.first] == '.' && pos.second < posPlayer.second){
            lab[pos.second + 1][pos.first] = 'M';
            lab[pos.second][pos.first] = '.';
            pos.second += 1;
        } else if(pos.first > 0 && lab[pos.second][pos.first - 1] == '.' && pos.first  > posPlayer.first){
            lab[pos.second][pos.first - 1] = 'M';
            lab[pos.second][pos.first] = '.';
            pos.first -= 1;
        } else if(pos.first < M-1 && lab[pos.second][pos.first + 1] == '.' && pos.first  < posPlayer.first){
            lab[pos.second][pos.first + 1] = 'M';
            lab[pos.second][pos.first] = '.';
            pos.first += 1;
        }
        res.push_back(pos);
    }
    cout << endl;
    for(int i = 0; i < N;i++){
        for(int j = 0; j < M; j++) cout << lab[i][j];
        cout << endl;
    }
    return res;
}

void way(pair<int,int> pos, vector<vector<char> >lab, vector<pair<int,int> > m,vector<char> moves, vector<vector<bool> > visited){
    if(possible || visited[pos.second][pos.first]){
        return;
    }

    if(pos.first >= M-1 || pos.first <= 0 || pos.second >= N-1 || pos.second <= 0){
        possible = true;
        path = moves;
        return;
    }

    visited[pos.second][pos.first] = true;

    if(lab[pos.second - 1][pos.first] == '.'){
        pair<int,int> newPos = make_pair(pos.first, pos.second - 1);
        vector<char> newMoves = moves;
        newMoves.push_back('U');
        vector<vector<char> > newLab = lab;

        vector<pair<int,int> > ms = move(newLab, newPos, m);
        if(lab[pos.second - 1][pos.first] == '.') way(newPos, newLab, ms, newMoves, visited);
    }

    if(lab[pos.second + 1][pos.first] == '.'){
        pair<int,int> newPos = make_pair(pos.first, pos.second + 1);
        vector<char> newMoves = moves;
        newMoves.push_back('D');
        vector<vector<char> > newLab = lab;
        vector<pair<int,int> > ms = move(newLab, newPos, m);

        if(lab[pos.second + 1][pos.first] == '.') way(newPos, newLab, ms, newMoves, visited);
    }

    if(lab[pos.second][pos.first - 1] == '.'){
        pair<int,int> newPos = make_pair(pos.first - 1, pos.second);
        vector<char> newMoves = moves;
        newMoves.push_back('L');
        vector<vector<char> > newLab = lab;
        vector<pair<int,int> > ms = move(newLab, newPos, m);

        if(lab[pos.second][pos.first - 1] == '.') way(newPos, newLab, ms, newMoves, visited);
    }

    if(lab[pos.second][pos.first + 1] == '.'){
        pair<int,int> newPos = make_pair(pos.first + 1, pos.second);
        vector<char> newMoves = moves;
        newMoves.push_back('R');
        vector<vector<char> > newLab = lab;
        vector<pair<int,int> > ms = move(newLab, newPos, m);

        if(lab[pos.second][pos.first + 1] == '.') way(newPos, newLab, ms, newMoves, visited);
    }
}

int main(){
    cin >> N >> M;
    vector<vector<char> > lab(N, vector<char> (M));
    vector<pair<int,int> > monsters;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            char a;
            cin >> a;
            
            if(a == 'A'){
                start = make_pair(j,i);
                lab[i][j] = '.';
            }else if(a == 'M'){
                monsters.push_back(make_pair(j,i));
                lab[i][j] = 'M';
            }else{
                lab[i][j] = a;
            }
            
        }
    }
    vector<char> ms;
    vector<vector<bool> > v(N, vector<bool> (M,false));
    way(start, lab, monsters, ms, v);

    if(possible){
        cout << "YES" << endl;
        cout << path.size() << endl;
        for(int i = 0; i < path.size(); i++) cout << path[i];
        cout << endl;
    }else{
        cout << "NO" << endl;
    }

    return 0;
}