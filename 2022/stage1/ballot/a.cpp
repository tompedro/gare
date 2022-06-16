#include <iostream>
#include <queue>
using namespace std;

int N, B;

int check(priority_queue<int> q, int k){
    if(k == 0) return 0;
    int r = 0;
    while(!q.empty()){
        int a = q.top();
        q.pop();
        do{
            a -= k;
            r++;
        }while(a > 0);
    }
    return r;
}

int bs(priority_queue<int> q, int l, int r){
     if (r > l+1) {
        int mid = l + (r - l) / 2;

        if (check(q,mid) > B)
            return bs(q, mid + 1, r);
 
        return bs(q, l, mid - 1);
    }
    if(r == l || r-l == 1){
        if (check(q,r) <= B) return r;
        if (check(q,r+1) <= B) return r+1;
        return -1;
    }
    return -1;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    while(true){
        cin >> N >> B;
        if(N == -1) break;
        priority_queue<int> q;

        for(int i = 0; i < N; i++){
            int a;
            cin >> a;
            q.push(a);
        }
        if(N == B) cout << q.top() << endl;
        else cout << bs(q, 0, q.top()) << endl;
    }
    
}