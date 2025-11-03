#include <stdio.h>

#define MAX_N 5000

int cercas[MAX_N];

// Função recursiva que retorna o número mínimo de pinceladas para pintar as tábuas de l até r
int minPinceladas(int l, int r, int alturaBase) {
    if (l > r) return 0; // Caso base: nenhum quadro

    // Encontrar a altura mínima na sublista
    int alturaMin = cercas[l];
    for (int i = l; i <= r; i++) {
        if (cercas[i] < alturaMin) alturaMin = cercas[i];
    }

    // Custo horizontal inicial: pinta até a altura mínima
    int custoHorizontal = alturaMin - alturaBase;

    int i = l;
    while (i <= r) {
        // Pular tábuas que já estão na altura mínima
        if (cercas[i] == alturaMin) {
            i++;
            continue;
        }
        int inicio = i;
        // Encontrar segmento contínuo maior que alturaMin
        while (i <= r && cercas[i] > alturaMin) i++;
        int fim = i - 1;
        custoHorizontal += minPinceladas(inicio, fim, alturaMin);
    }

    // Custo vertical: pintar cada tábua individualmente
    int custoVertical = r - l + 1;

    // Retornar o mínimo entre pintar horizontalmente ou verticalmente
    return (custoHorizontal < custoVertical) ? custoHorizontal : custoVertical;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &cercas[i]);
    }

    int resultado = minPinceladas(0, N - 1, 0);
    printf("%d\n", resultado);

    return 0;
}
