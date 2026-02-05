#include <stdio.h>

int main () {
    float a,b,c;

    printf("Digite o primeiro valor do lado do triangulo: \n");
    scanf("%f", &a);
    printf("Digite o segundo valor do lado do triangulo: \n");
    scanf("%f", &b);
    printf("Digite o terceiro valor do lado do triangulo: \n");
    scanf("%f", &c);

    if (a == b && b == c) {
        printf("Triangulo Equilatero");

    } else if ((a == b && a!= c) || (a == c && a!= b) || (c == b && c!= a)) {
        printf("Triangulo Isoceles");

    } else {
        printf("Triangulo Escaleno");

    }
    

}