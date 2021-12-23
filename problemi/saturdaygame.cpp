#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, k;
	cin >> n >> k;
	
	int limit = 1;
	while(limit < k) limit *= 2;
	
	for(int a = 0; a < limit; a++){
		int b = a^k;
		if(a == b) continue;	
		for(int c = 0; c < limit; c++){
			if(c == a || c == b) continue;
			int d = a+b-c;
			if(d == c) continue;
			if((c^d) == k){
				cout << a << " " << b << endl;
				cout << c << " " << d << endl;
				return 0;
			}
		}
	}
}
