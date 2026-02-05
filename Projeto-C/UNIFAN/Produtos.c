#include <stdio.h>

#define MAX_NOME 30

// Estrutura Produto
typedef struct {
    int codigo;
    char nome[MAX_NOME];
    float preco;
    int quantidade;
} Produto;

int main() {
    int N;
    printf("Digite a quantidade de produtos: ");
    scanf("%d", &N);

    Produto vetor[N];

    // Cadastro dos produtos
    for (int i = 0; i < N; i++) {
        printf("\n=== Produto %d ===\n", i+1);

        printf("Codigo: ");
        scanf("%d", &vetor[i].codigo);

        printf("Nome: ");
        scanf(" %[^\n]", vetor[i].nome); // lê string com espaços

        printf("Preco: ");
        scanf("%f", &vetor[i].preco);

        printf("Quantidade em estoque: ");
        scanf("%d", &vetor[i].quantidade);
    }

    // 1. Produtos com preço acima de R$ 100
    printf("\nProdutos com preco acima de R$ 100:\n");
    for (int i = 0; i < N; i++) {
        if (vetor[i].preco > 100) {
            printf("Codigo: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
                   vetor[i].codigo, vetor[i].nome, vetor[i].preco, vetor[i].quantidade);
        }
    }

    // 2. Produto com maior quantidade em estoque
    int indiceMaior = 0;
    for (int i = 1; i < N; i++) {
        if (vetor[i].quantidade > vetor[indiceMaior].quantidade) {
            indiceMaior = i;
        }
    }

    printf("\nProduto com maior quantidade em estoque:\n");
    printf("Codigo: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
           vetor[indiceMaior].codigo, vetor[indiceMaior].nome,
           vetor[indiceMaior].preco, vetor[indiceMaior].quantidade);

    return 0;
}
