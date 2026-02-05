
#include <stdio.h>

int main() {
    int sexo;
    float altura, peso;

    printf("Qual o seu sexo? Utilize 1 para feminino e 2 para masculino: ");
    scanf("%d", &sexo);

    printf("Qual sua altura? ");
    scanf("%f", &altura);

    if (sexo == 1) {
        peso = (62.1 * altura) - 44.7;
        printf("Seu peso ideal é: %.2f\n", peso);
    } else if (sexo == 2) {
        peso = (72.7 * altura) - 58;
        printf("Seu peso ideal é: %.2f\n", peso);
    } else {
        printf("Sexo inválido.\n");
    }

    return 0;
}