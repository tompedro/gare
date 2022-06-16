#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int Q, i;
static long long int id;
static char t;

// Declaring functions
void aggiungi(long long id);
void togli(long long id);
int conta(long long id);

int main() {
    // Uncomment the following lines if you want to read/write from files
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    assert(1 == scanf("%d", &Q));

    for(i = 0; i < Q; i++){
        assert(2 == scanf(" %c %lld", &t, &id));

        if(t == 'a') {
            aggiungi(id);
        } else if (t == 't') {
            togli(id);
        } else if (t == 'c') {
            printf("%d\n", conta(id));
        }
    }

    return 0;
}
