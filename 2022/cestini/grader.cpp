#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

multimap<int,pair<int,int>> mm;

void inizia(int N, int M){
	for(int i = N; i >= 0; i--){
		mm.insert(make_pair(0,make_pair(-i,i)));
	}
}
void sposta(int a, int b){
	cout << "INDICE : " << (mm.find(b)->second.first-1) << endl;
	cout << "NOME : " << (mm.find(a)->second.first) << endl;
	mm.insert(make_pair(b,make_pair(mm.find(b)->second.first-1,mm.find(a)->second.second)));
	mm.erase(mm.find(a));
}
int controlla(int a, int i){
	std::pair <std::multimap<int,pair<int,int>>::iterator, std::multimap<int,pair<int,int>>::iterator> ret;
    ret = mm.equal_range(a);

    for (multimap<int,pair<int,int>>::iterator it=ret.first; it!=ret.second; ++it){
      if(it->second.first == -i){
      		return it->second.second;
	  }
	}
}

int main() {
    // Uncomment the following lines if you want to read/write from files
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    ios::sync_with_stdio(false);

    int N, M, Q;
    cin >> N >> M >> Q;

    inizia(N, M);

    for (int i = 0; i < Q; i++) {
        char t;
        int a, b;
        cin >> t >> a >> b;
        if (t == 's') {
            sposta(a, b);
        } else {
            cout << controlla(a, b) << '\n';
        }
    }

    return 0;
}
