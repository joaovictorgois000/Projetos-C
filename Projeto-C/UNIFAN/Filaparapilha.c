#include <stdio.h>
#include <stdlib.h>

// -------------------- Estruturas --------------------
typedef struct No {
    int dado;
    struct No* prox;
} No;

typedef struct {
    No* topo;
} Pilha;

typedef struct {
    No* frente;
    No* tras;
} Fila;

// -------------------- Funções de Pilha --------------------
void inicializarPilha(Pilha* p) {
    p->topo = NULL;
}

int pilhaVazia(Pilha* p) {
    return (p->topo == NULL);
}

void empilhar(Pilha* p, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dado = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

int desempilhar(Pilha* p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        exit(1);
    }
    No* temp = p->topo;
    int valor = temp->dado;
    p->topo = temp->prox;
    free(temp);
    return valor;
}

// -------------------- Funções de Fila --------------------
void inicializarFila(Fila* f) {
    f->frente = f->tras = NULL;
}

int filaVazia(Fila* f) {
    return (f->frente == NULL);
}

void enfileirar(Fila* f, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dado = valor;
    novo->prox = NULL;
    if (filaVazia(f))
        f->frente = novo;
    else
        f->tras->prox = novo;
    f->tras = novo;
}

int desenfileirar(Fila* f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        exit(1);
    }
    No* temp = f->frente;
    int valor = temp->dado;
    f->frente = temp->prox;
    if (f->frente == NULL)
        f->tras = NULL;
    free(temp);
    return valor;
}

// -------------------- Função que inverte a pilha --------------------
void inverterPilha(Pilha* p) {
    Fila f;
    inicializarFila(&f);

    // Passo 1: mover todos os elementos da pilha para a fila
    while (!pilhaVazia(p)) {
        enfileirar(&f, desempilhar(p));
    }

    // Passo 2: mover todos os elementos da fila de volta para a pilha
    while (!filaVazia(&f)) {
        empilhar(p, desenfileirar(&f));
    }
}

// -------------------- Função para exibir a pilha --------------------
void exibirPilha(Pilha* p) {
    No* atual = p->topo;
    printf("Pilha (topo -> base): ");
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

// -------------------- Programa principal --------------------
int main() {
    Pilha p;
    inicializarPilha(&p);

    // Elementos iniciais da pilha
    int elementos[] = {3, 17, 26, 8, 21, 14, 30};
    int n = sizeof(elementos) / sizeof(elementos[0]);

    // Empilha os elementos na ordem dada (30 será o topo)
    for (int i = 0; i < n; i++)
        empilhar(&p, elementos[i]);

    printf("Pilha original:\n");
    exibirPilha(&p);

    inverterPilha(&p);

    printf("Pilha invertida:\n");
    exibirPilha(&p);

    return 0;
}
