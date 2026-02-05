#include <stdio.h>

// Função que realiza o Selection Sort
void selectionSort(int vetor[], int tamanho) {
    int i, j, minIndex, temp;

    // Percorre o vetor até o penúltimo elemento
    for (i = 0; i < tamanho - 1; i++) {
        // Assume que o menor elemento está na posição atual
        minIndex = i;

        // Procura o menor elemento no restante do vetor
        for (j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[minIndex]) {
                minIndex = j; // Atualiza o índice do menor elemento encontrado
            }
        }

        // Troca o elemento atual pelo menor encontrado
        temp = vetor[i];
        vetor[i] = vetor[minIndex];
        vetor[minIndex] = temp;
    }
}

// Função principal
int main() {
    int vetor[] = {64, 25, 12, 22, 11};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor original:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    // Chama a função de ordenação
    selectionSort(vetor, tamanho);

    printf("\n\nVetor ordenado:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");
    return 0;
}

