#include <stdio.h>

int main () {
    float peso, altura, imc;

    printf("Informe seu peso: \n");
    scanf("%f",&peso);
    printf("Informe sua altura: \n");
    scanf("%f",&altura);

    imc = peso / (altura * altura);

    printf("Seu IMC é de %.2f",imc);
}