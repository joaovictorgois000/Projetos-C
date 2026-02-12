#include <stdio.h>

int main () {
    float salario, reajuste;

    printf("Informe seu salario atual par reajuste: \n");
    scanf("%f", &salario);

    reajuste = salario + (salario * 0.05);

    printf("Seu salario com reajuste foi de %.2f", reajuste);


}