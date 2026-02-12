#include <stdio.h>

int main () {
    float nota1, nota2, nota3, media;

    printf("Informe sua primeira nota: \n");
    scanf("%f", &nota1);
    printf("Informe sua segunda nota: \n");
    scanf("%f", &nota2);
    printf("Informe sua terceira nota: \n");
    scanf("%f", &nota3);

    media = (nota1 + nota2 + nota3) / 3;

    printf("Sua media foi de %.2f", media);
}