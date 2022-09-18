#include<bits/stdc++.h>
using namespace std;

int best_score(int N, int K, vector<int> &monete){
	int sum = 0;
	int memo[N];
	deque<int> q;
	
	for(int i = 0; i < N; i++){
		sum += monete[i];
		if(i < K){
			memo[i] = sum;
		}else{
			if (i-K-1 >= 0 && !q.empty() && q.front() == memo[i-K-1])
    			q.pop_front();
			//cout << "m : " << m.first << endl;
			memo[i] = sum - q.front();
		}
		//cout << memo[i] << endl;
		while (!q.empty() && q.back() > memo[i])
		    q.pop_back();
		q.push_back(memo[i]);
	}
	return memo[N-1];
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int N, K;
	cin>>N>>K;
	vector<int> v(N);
	for(int i=0;i<N;i++)
		cin>>v[i];
	cout<<best_score(N,K,v);
}
