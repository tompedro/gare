#include <assert.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
// constraints
#define MAXD 1000
#define ll long long int

// input data
int C, D, Y;
int M[MAXD + 1];
int P[MAXD + 1];

ll solve(){
	int cos[D+1];
	cos[1] = C + M[1] - P[1];
	for (int i = 2; i <= D; i++)
	{
		cos[i] = cos[i-1] + M[i] - P[i] + P[i-1];
	}
	D = min(D, Y);
	vector < int > memo(Y+1, 1<<30);
	vector < int > useful(0);
	memo[0] = 0;
	for (int i = 0; i <= D; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			memo[i] = min(memo[i], memo[i-j] + cos[j]);
		}
		
		if (cos[i] == memo[i])
		{
			useful.push_back(i);
		}
	}
	
	for (int i = 0; i <= Y; i++)
	{
		for (auto j : useful)
		{
			if (i - j >= 0)
			{
				memo[i] = min(memo[i], memo[i-j] + cos[j]);
			}
		}
	}
	return memo[Y];
}

int main() {
  //  uncomment the following lines if you want to read/write from files
  freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  assert(3 == scanf("%d %d %d", &C, &D, &Y));
  // warning! M and P are 1-based
  for (int i = 1; i <= D; i++) assert(1 == scanf("%d", &M[i]));
  for (int i = 1; i <= D; i++) assert(1 == scanf("%d", &P[i]));

  // insert your code here

  printf("%d\n", solve());  // print the result
  return 0;
}
