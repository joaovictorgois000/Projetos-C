#include <stdio.h>

int main () {
    float C, P;

    printf("Informe o comprimento em polegadas para ser convertido em cm: \n");
    scanf("%f", &P);

    C = P * 2.54;

    printf("O valor em polegadas foi de %.2f", C);
}