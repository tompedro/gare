#include <bits/stdc++.h>
using namespace std;

// constraints
const int MAXN = 50000;

// input data
int N, T;
string hashtags[MAXN];

vector<multiset<string>> counter;
vector<set<pair<int,string>>> h;

void push(string a, int k){
	counter[k].insert(a);
    int c = counter[k].count(a);
    	
	if(c > 1){
		set<pair<int,string>>::iterator it = (h[k].insert(make_pair(-c+1, a))).first;
		h[k].erase(it);
		h[k].insert(make_pair(-c, a));
	}else{
		h[k].insert(make_pair(-c, a));
	}
}

void print(){
	for(int i = 0; i <= N-T; i++){
		for (auto itr : h[i])
		{
			cout << itr.first << " " << itr.second << " ";
		} 
		cout << endl;
	}
}

int main() {
//  uncomment the following lines if you want to read/write from files
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin >> N >> T;
    h.resize(N-T+1);
    counter.resize(N-T+1);
    
    for(int i=0; i<N; i++){
    	string a;
    	cin >> a;
    	
    	for(int j = 1; j <= T; j++){
    		if(i-T+j >= 0 && i-T+j <= N-T){
    			push(a, i-T+j);
			}
			
		}
	}
	for(int i = 0; i <= N-T; i++){
		cout << (*h[i].begin()).second << endl;
	}

    return 0;
}
