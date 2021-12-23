#include <bits/stdc++.h>
using namespace std;
long long N, k;
vector<long long> v;

bool check(long long a){
	long long sum = 0;
	long long n = 1;
	for(long long i = 0; i < N; i++){
		if(sum + v[i] > a){
			if(v[i] > a){
				return false;
			}
			sum = v[i];
			n++;
			continue;
		}
		sum += v[i];
	}
	if(n <= k){
		return true;
	}
	return false;
}

int main(){
	cin >> N >> k;
	long long upper = 0;

	for(int i = 0; i < N; i++){
		long long a;
		cin >> a;
		v.push_back(a);
		upper += a;
	}

	long long a = 0;
	long long z = upper;
	long long m;
	while(a <= z){
		m = (a+z)/2;
		if(check(m)){
			z = m - 1;
		} else {
			a = m + 1;
		} 
	}
	if(!check(m)) m++;
	
	cout << m << endl;
	
	return 0;
}
