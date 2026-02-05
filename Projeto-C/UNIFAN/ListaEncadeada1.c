#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
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

// Inserir um elemento no final da lista
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

// Inserir um elemento no início da lista
void inserirInicio(No** lista, int valor) {
    No* novo = criarNo(valor);
    novo->proximo = *lista;
    *lista = novo;
}

// Imprimir todos os elementos da lista
void imprimirLista(No* lista) {
    No* atual = lista;
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// Remover um elemento específico da lista
void removerElemento(No** lista, int valor) {
    No* atual = *lista;
    No* anterior = NULL;

    while (atual != NULL && atual->valor != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Valor %d não encontrado na lista.\n", valor);
        return;
    }

    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Valor %d removido com sucesso.\n", valor);
}

// Liberar toda a memória da lista
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

    inserirFinal(&lista, 10);
    inserirFinal(&lista, 20);
    inserirInicio(&lista, 5);
    inserirFinal(&lista, 30);

    imprimirLista(lista);

    removerElemento(&lista, 20);
    imprimirLista(lista);

    liberarLista(&lista);
    imprimirLista(lista);

    return 0;
}
