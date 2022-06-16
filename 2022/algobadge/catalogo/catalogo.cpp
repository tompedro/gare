#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int catalogo[INT_MAX];

void aggiungi(long long int id) {
    catalogo[id] += 1;
}

void togli(long long int id) {
    catalogo[id] -= 1;
}

int conta(long long int id) {
    return catalogo[id];
}

