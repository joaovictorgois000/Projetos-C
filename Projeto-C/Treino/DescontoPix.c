#include <stdio.h>

int main () {
    float produto, desconto;

    printf("Informe o valor do produto: \n");
    scanf("%f", &produto);

    desconto = produto - (produto * 0.15);

    printf("O produto com desconto foi de %.2f", desconto);

}