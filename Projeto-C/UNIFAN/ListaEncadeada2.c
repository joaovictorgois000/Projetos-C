#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da lista
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

// Função que insere mantendo a lista em ordem crescente
void inserirOrdenado(No** lista, int valor) {
    No* novo = criarNo(valor);

    // Caso 1: lista vazia ou o novo valor é menor que o primeiro elemento
    if (*lista == NULL || valor < (*lista)->valor) {
        novo->proximo = *lista;
        *lista = novo;
        return;
    }

    // Caso 2: encontrar o local correto de inserção
    No* atual = *lista;
    while (atual->proximo != NULL && atual->proximo->valor < valor) {
        atual = atual->proximo;
    }

    // Inserir o novo nó na posição correta
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

// Função para imprimir a lista
void imprimirLista(No* lista) {
    No* atual = lista;
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// Função para liberar a memória da lista
void liberarLista(No** lista) {
    No* atual = *lista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *lista = NULL;
}

int main() {
    No* lista = NULL;

    // Inserções em ordem aleatória
    inserirOrdenado(&lista, 30);
    inserirOrdenado(&lista, 10);
    inserirOrdenado(&lista, 50);
    inserirOrdenado(&lista, 20);
    inserirOrdenado(&lista, 40);

    imprimirLista(lista); // Saída esperada: 10 -> 20 -> 30 -> 40 -> 50 -> NULL

    liberarLista(&lista);
    return 0;
}
