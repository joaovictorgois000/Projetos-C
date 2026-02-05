#include <stdio.h>
#include <stdlib.h>
typedef struct No
{
    int valor;
    struct No *anterior;
    struct No *proximo;
} No;
typedef struct Fila
{
    int tamanho;
    No *inicio;
    No *final;
} Fila;
void enfileirar(Fila *fila, int valor);
int remover(Fila *fila);
void imprimir(Fila *fila);
int main()
{
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->tamanho = 0;
    fila->inicio = NULL;
    enfileirar(fila, 21);
    enfileirar(fila, 33);
    enfileirar(fila, 50);
    imprimir(fila); // 21 33 50
}

void enfileirar(Fila *fila, int valor)
{
    No *no = (No *)malloc(sizeof(No));
    no->valor = valor;
    no->anterior = NULL;
    no->proximo = NULL;
    if (fila->tamanho == 0)
    { // Se a fila está vazia
        fila->inicio = no;
    }
    if (fila->tamanho > 0)
    {
        fila->final->proximo = no;
        no->anterior = fila->final;
    }
    fila->final = no;
    fila->tamanho = fila->tamanho + 1;
}

int remover(Fila *fila)
{
    if (fila->tamanho == 0)
    {
        return -1;
    } // Se a fila está vazia
    No *no = fila->inicio;
    fila->inicio = no->proximo;
    if (fila->inicio != NULL)
    {
        fila->inicio->anterior = NULL;
    }
    if (fila->inicio == NULL)
    {
        fila->final = NULL;
    }
    fila->tamanho = fila->tamanho - 1;
    int valor = no->valor;
    free(no);
    return valor;
}

void imprimir(Fila *fila)
{
    No *no = fila->inicio;
    printf("Fila: ");
    while (no != NULL)
    {
        printf("%d ", no->valor);
        no = no->proximo;
    }
    printf("\n");
}