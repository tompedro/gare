// non finito
#include <stdio.h>
#include <assert.h>
#define MAXN 1000000

static FILE *fr, *fw;

static int N;
static int acceso[MAXN + 1], pulsante[MAXN + 1];

void r(int acceso[], int pulsante[],int u){
    if(u >= N) return;

    int d = u+1;
    for (int i = 1; i < (int) sqrt(d) + 1; i++) { 
        if (d % i == 0){
            if(i*i==d){
                acceso[i] = !acceso[i];
                pulsante[i] = 1;
            }else{
                acceso[i] = !acceso[i];
                pulsante[i] = 1;
                acceso[d/i] = !acceso[d/i];
                pulsante[d/i] = 1;
            }   
        }
    }

    r(acceso, pulsante, u+1);
    r(acceso, pulsante, u+2);
}

void Accendi(int N, int acceso[], int pulsante[]){
    r(acceso, pulsante, 1);
}

int main() {
    int i;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    assert(1 == fscanf(fr, "%d", &N));
    for (i=1; i<=N; i++)
        assert(1 == fscanf(fr, "%d", acceso + i));

    Accendi(N, acceso, pulsante);

    for (i=1; i<=N; i++) {
        if (i > 1) fprintf(fw, " ");
        fprintf(fw, "%d", pulsante[i]);
    }
    fprintf(fw, "\n");
    return 0;
}
