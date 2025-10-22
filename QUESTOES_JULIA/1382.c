#include <stdio.h>
#include <stdlib.h>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N;
        scanf("%d", &N);
        int perm[N + 1];
        int visited[N + 1];
        
        for (int i = 1; i <= N; i++) {
            scanf("%d", &perm[i]);
            visited[i] = 0;
        }

        int ciclos = 0;

        for (int i = 1; i <= N; i++) {
            if (!visited[i]) {
                ciclos++;
                int atual = i;
                while (!visited[atual]) {
                    visited[atual] = 1;
                    atual = perm[atual];
                }
            }
        }

        printf("%d\n", N - ciclos);
    }

    return 0;
}
