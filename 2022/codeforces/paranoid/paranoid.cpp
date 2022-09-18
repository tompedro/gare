#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int T;
	cin >> T;
	
	while(T > 0){
		int N;
		string a;
		cin >> N >> a;
		
		ll res = N;
		for(int i = 0; i < N-1; i++){
			if(a[i+1] != a[i]){
				res += 1 + i;
			}
		}
		
		cout << res << endl;
		T--;
	}
}
