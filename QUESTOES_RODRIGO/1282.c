#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000000000LL  // 1e15 (long long)

// Variáveis globais para evitar overhead
#define MAXN 1005
long long X[MAXN], W[MAXN];
long long prefixW[MAXN], prefixXW[MAXN];
long long dp_prev[MAXN], dp_curr[MAXN];
int N, K;

// Função de custo: custo de reagrupar montes de l..r em um único monte
long long custo(int l, int r) {
    long long somaW = prefixW[r] - prefixW[l - 1];
    long long somaXW = prefixXW[r] - prefixXW[l - 1];
    return somaW * X[r] - somaXW;
}

// Função recursiva Divide & Conquer Optimization
void compute(int k, int l, int r, int optL, int optR) {
    if (l > r) return;

    int mid = (l + r) / 2;
    long long bestCost = INF;
    int bestPos = -1;

    for (int j = optL; j <= optR && j < mid; j++) {
        long long val = dp_prev[j] + custo(j + 1, mid);
        if (val < bestCost) {
            bestCost = val;
            bestPos = j;
        }
    }

    dp_curr[mid] = bestCost;

    if (l == r) return;

    compute(k, l, mid - 1, optL, bestPos);
    compute(k, mid + 1, r, bestPos, optR);
}

// Resolve um caso de teste
long long solve_case() {
    prefixW[0] = 0;
    prefixXW[0] = 0;
    for (int i = 1; i <= N; i++) {
        prefixW[i] = prefixW[i - 1] + W[i];
        prefixXW[i] = prefixXW[i - 1] + W[i] * X[i];
    }

    for (int i = 0; i <= N; i++) dp_prev[i] = INF;
    dp_prev[0] = 0;

    for (int k = 1; k <= K; k++) {
        compute(k, 1, N, 0, N - 1);
        for (int i = 0; i <= N; i++) {
            dp_prev[i] = dp_curr[i];
            dp_curr[i] = 0;
        }
    }

    return dp_prev[N];
}

int main() {
    while (scanf("%d %d", &N, &K) == 2) {
        for (int i = 1; i <= N; i++) {
            scanf("%lld %lld", &X[i], &W[i]);
        }
        printf("%lld\n", solve_case());
    }
    return 0;
}
