#include <stdio.h>

int main(){

    float salario_atual, salario_reajuste, aumento;

    printf("Digite o seu salario atual: \n");
    scanf("%f", &salario_atual);

    aumento = salario_atual * 5/100;
    salario_reajuste = salario_atual + aumento;

    printf("Seu salario com reajuste foi de: %f" , salario_reajuste);


}