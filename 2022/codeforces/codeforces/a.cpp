#include <iostream>
#include <string>
using namespace std;

void f(int N, int* arr){
    for(int i = 0; i < N - 2; i++){
        for(int j = i + 1; j < N; j++){
            for(int k = j + 1; k < N; k++){
                string a = to_string(arr[i]+arr[j]+arr[k]);
                if(a[a.size() - 1] == '3'){
                    cout << "YES" << endl;
                    return;
                }
            }
        }
    }
    cout << "NO" << endl;
    return;
}

int main() {
    int T;
    
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
    cin >> T;

    for(int p = 0; p < T; p++){
        int N;
        cin >> N;
        int arr[N];
        for(int i = 0; i < N; i++){
            cin >> arr[i];
        }
        f(N, arr);
    }
}
