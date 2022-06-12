/*#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

long long int fat(long long int n){
	if(n == 2){
		return 2;
	}else if(n == 3){
		return 6;
	}else if(n == 1){
		return 1;
	}else {
		return n*fat(n-1);
	}
}

double f(long long int n,long long int a){
	if(n == 3){
		return 9;
	}else if(n == 4){
	    return 72;   
	}else if(n == 5){
	    return 600;   
	}else {
		return (a*n*(n-1)/2) + f(n-1, a/(n-1))*n;
	}
}

double scosse(int n) {
	if(n == 6) return 7.5;
	if(n == 7) return 10.5;
	if(n == 8) return 14;
	long long int a = fat(n-1);
    return (double)f(n,a)/(a*n);
}


int main() {
    FILE *fr, *fw;
    int N;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &N));
    fprintf(fw, "%.6f\n", scosse(N));
    fclose(fr);
    fclose(fw);
    return 0;
}*/

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;


double scosse(int n) {
    return (double)(n-1)*n/4;
}


int main() {
    FILE *fr, *fw;
    int N;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &N));
    fprintf(fw, "%.6f\n", scosse(N));
    fclose(fr);
    fclose(fw);
    return 0;
}
