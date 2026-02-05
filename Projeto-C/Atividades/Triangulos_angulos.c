#include <stdio.h>

int main(){

    float a,b,c;

    printf("Digite o valor do primeiro angulo: \n");
    scanf("%f" , &a);

    printf("Digite o valor do segundo angulo: \n");
    scanf("%f" , &b);

    printf("Digite o valor do terceiro angulo: \n");
    scanf("%f" , &c);

    if (a == 90 || b == 90 || c == 90) {
        printf("Triangulo retangulo\n");

    } else if (a > 90 || b > 90 || c > 90) {
        printf("Triangulo Obtusangulo\n");

    } else {
        printf("Triangulo Acutangulo\n");

        return 0;
    }

    





    



}