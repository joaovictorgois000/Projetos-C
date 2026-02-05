#include <stdio.h>
#include <stdlib.h>

// -------------------- Estruturas --------------------
typedef struct No {
    int dado;
    struct No* prox;
} No;

typedef struct {
    No* frente;
    No* tras;
} Fila;

typedef struct {
    No* topo;
} Pilha;

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

// -------------------- Função que inverte a fila --------------------
void inverterFila(Fila* f) {
    Pilha p;
    inicializarPilha(&p);

    // Passo 1: mover todos os elementos da fila para a pilha
    while (!filaVazia(f)) {
        empilhar(&p, desenfileirar(f));
    }

    // Passo 2: mover todos os elementos da pilha de volta para a fila
    while (!pilhaVazia(&p)) {
        enfileirar(f, desempilhar(&p));
    }
}

// -------------------- Função para exibir a fila --------------------
void exibirFila(Fila* f) {
    No* atual = f->frente;
    printf("Fila: ");
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

// -------------------- Programa principal --------------------
int main() {
    Fila f;
    inicializarFila(&f);

    // Elementos iniciais da fila
    int elementos[] = {5, 12, 19, 23, 7, 28, 15};
    int n = sizeof(elementos) / sizeof(elementos[0]);

    for (int i = 0; i < n; i++)
        enfileirar(&f, elementos[i]);

    printf("Fila original:\n");
    exibirFila(&f);

    inverterFila(&f);

    printf("Fila invertida:\n");
    exibirFila(&f);

    return 0;
}
