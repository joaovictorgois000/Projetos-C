#include <stdio.h>

int main() {
    int A, B, temp;

    // Recebendo os valores
    printf("Digite o valor de A: ");
    scanf("%d", &A);
    printf("Digite o valor de B: ");
    scanf("%d", &B);

    printf("\nValores originais: A = %d, B = %d\n", A, B);

    // Algoritmo de Troca
    temp = A; // temp guarda o valor original de A
    A = B;    // A recebe o valor de B
    B = temp; // B recebe o valor original de A (guardado em temp)

    // Exibindo os valores trocados
    printf("Valores trocados: A = %d, B = %d\n", A, B);

    return 0;
}