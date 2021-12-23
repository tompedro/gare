#include <bits/stdc++.h>
using namespace std;
int cities = 0, boxes;
vector<long long> pop;

int check(int a){
	int sm = 0;
	
	for(int i = 0; i < cities; i++){
		if(pop[i] > a){
			sm += pop[i]/a;	
		}else{
			sm++;
		}
		if(sm > boxes){
			return 1;
		}
	}
	if(sm == boxes){
		return 0;
	}
	return -1;
}

int main(){
	while(true){
		cin >> cities >> boxes;
		if(cities == -1){
			break;
		}
		long long upper = 0;
	
		for(int i = 0; i < cities; i++){
			long long a;
			cin >> a;
			pop.push_back(a);
			upper = max(a,upper);
		}
		
		int a = 0;
		int z = upper;
		while(a <= z){
			int m = (a+z)/2;
			int result = check(m);
			if(result == 0){
				cout << upper/(upper/m) << endl;
				break;
			} else if(result == 1){
				a = m + 1;
			} else if(result == -1){
				z = m - 1;
			}
		}
		
		pop.clear();
	}
	return 0;
}
