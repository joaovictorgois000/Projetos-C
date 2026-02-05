#include <stdio.h>

typedef struct Tempo {
    int hora;
    int minuto;
} Tempo;

// Função que recebe um vetor de Tempos e devolve a soma em minutos
int soma(Tempo v[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += v[i].hora * 60 + v[i].minuto;
    }
    return total;
}

int main() {
    int N;
    printf("Digite a quantidade de tempos: ");
    scanf("%d", &N);

    Tempo vetor[N];

    // Lendo os tempos
    for (int i = 0; i < N; i++) {
        printf("Digite a hora e os minutos do tempo %d: ", i+1);
        scanf("%d %d", &vetor[i].hora, &vetor[i].minuto);
    }

    // Chamando a função e imprimindo o resultado
    int totalMinutos = soma(vetor, N);
    printf("A soma total em minutos é: %d\n", totalMinutos);

    return 0;
}
