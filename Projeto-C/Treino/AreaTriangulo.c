#include <stdio.h>

int main () {
    float base, altura, area;

    printf("Informe a base do triangulo: \n");
    scanf("%f",&base);
    printf("Informe a altura do triangulo: \n");
    scanf("%f",&altura);

    area = (base * altura) / 2;

    printf("A area do triangulo foi de: %2.f", area);
}