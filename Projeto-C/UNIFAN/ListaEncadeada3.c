#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
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

// Função para inserir elemento no final da lista
void inserirFinal(No** lista, int valor) {
    No* novo = criarNo(valor);
    if (*lista == NULL) {
        *lista = novo;
    } else {
        No* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
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

// Função que concatena duas listas em uma nova
No* concatenarListas(No* lista1, No* lista2) {
    No* novaLista = NULL;
    No* atual;

    // Copiar os elementos da lista1
    atual = lista1;
    while (atual != NULL) {
        inserirFinal(&novaLista, atual->valor);
        atual = atual->proximo;
    }

    // Copiar os elementos da lista2
    atual = lista2;
    while (atual != NULL) {
        inserirFinal(&novaLista, atual->valor);
        atual = atual->proximo;
    }

    return novaLista;
}

// Função para liberar memória da lista
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
    No* lista1 = NULL;
    No* lista2 = NULL;
    No* listaConcatenada = NULL;

    // Criando a primeira lista
    inserirFinal(&lista1, 10);
    inserirFinal(&lista1, 20);
    inserirFinal(&lista1, 30);

    // Criando a segunda lista
    inserirFinal(&lista2, 40);
    inserirFinal(&lista2, 50);
    inserirFinal(&lista2, 60);

    printf("Lista 1:\n");
    imprimirLista(lista1);

    printf("Lista 2:\n");
    imprimirLista(lista2);

    // Concatenando as listas
    listaConcatenada = concatenarListas(lista1, lista2);

    printf("\nLista concatenada:\n");
    imprimirLista(listaConcatenada);

    // Liberando memória
    liberarLista(&lista1);
    liberarLista(&lista2);
    liberarLista(&listaConcatenada);

    return 0;
}
