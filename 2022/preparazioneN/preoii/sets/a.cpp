#include <iostream>
#include <vector>
#include <list>
using namespace std;

int MAX = 0;

void r(vector<int> l, int score){
    /*cout << "entro con : ";
    for(list<int>::iterator it5 = l.begin(); it5 != l.end(); ++it5){
        cout << *it5 << " ";
    } 
    cout << endl;*/
    
    for (int i = 0; i < l.size()-2; i++){
        cout << i <<" " << l[i] << endl;
        if((l[i] ^ l[i+1] ^ l[i+2])== 0){
            cout << "cancello : " << l[i] << endl;
            vector<int> v2(l);
            v2.erase(next(v2.begin(),i),next(v2.begin(), i+3));
            r(v2, score+3);
        }
    }
    MAX = max(score, MAX);
}

int conta(int N, vector<int> D){
    //list<int> l(D.begin(), D.end());

    r(D, 0);
    return MAX;
}

int main() {
	// se vuoi leggere da file decommenta queste due linee
	assert(freopen("input.txt", "r", stdin));
	//assert(freopen("output.txt", "w", stdout));

	int n;
	cin >> n;

	vector<int> d(n);
	for (auto &x : d)
		cin >> x;

	int ans = conta(n, d);
	cout << ans << '\n';
}
