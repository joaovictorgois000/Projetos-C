#include <stdio.h>

int main() {
    float nota1, nota2, media;

    printf("Digite suas duas notas: ");
    scanf("%f %f", &nota1, &nota2);

    media = (nota1 + nota2) / 2;

    if (media >= 7) {
        printf("Aprovado\n");
    } else if (media < 3) {
        printf("Reprovado\n");
    } else {
        printf("Recuperacao\n");
    }

    return 0;
}