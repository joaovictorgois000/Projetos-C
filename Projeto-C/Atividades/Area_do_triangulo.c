#include <stdio.h>

int main(){

    float area, base, altura;

    printf("Digite o valor da base do triangulo: \n");
    scanf("%f" , &base);
    printf("Digite o valor da altura do triangulo: \n");
    scanf("%f" , &altura);

    area = (base * altura)/2;

    printf("O valor da area do triangulo é de: %.2f \n" , area);
}