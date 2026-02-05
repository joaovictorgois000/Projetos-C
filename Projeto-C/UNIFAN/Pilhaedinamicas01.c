#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *proximo;

} No;

typedef struct Pilha
{
    int tamanho;
    No *topo;

} Pilha;

void push(Pilha *pilha, int valor);
int pop(Pilha *pilha);
int peek(Pilha *pilha);
void imprimir(Pilha *pilha);
int main()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->tamanho = 0;
    pilha->topo = NULL;
    push(pilha, 25);
    push(pilha, 22);
    push(pilha, 11);
    imprimir(pilha); // 25 22 11
}
void push(Pilha *pilha, int valor)
{
    No *no = (No *)malloc(sizeof(No));
    no->valor = valor;
    no->proximo = pilha->topo;
    pilha->topo = no;
    pilha->tamanho = pilha->tamanho + 1;
}
int pop(Pilha *pilha)
{
    // Se a pilha está vazia
    if (pilha->tamanho == 0)
    {
        return -1;
    }
    No *no = pilha->topo;
    pilha->topo = no->proximo;
    pilha->tamanho = pilha->tamanho - 1;
    int valor = no->valor;
    free(no);
    return valor;
}
int peek(Pilha *pilha)
{
    // Se a pilha está vazia
    if (pilha->tamanho == 0)
    {
        return -1;
    }
    return pilha->topo->valor;
}
void imprimir(Pilha *pilha)
{
    No *no = pilha->topo;
    printf("Pilha:\n");
    while (no != NULL)
    {
        printf("%d\n", no->valor);
        no = no->proximo;
    }
    printf("----\n");
}
