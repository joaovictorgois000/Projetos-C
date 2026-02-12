#include <stdio.h>

int main() {
    float altura, pesoIdeal;
    int sexo;

    printf("Digite sua altura (em metros): ");
    scanf("%f", &altura);

    printf("Digite seu sexo (1 - Feminino | 2 - Masculino): ");
    scanf("%d", &sexo);

    if (sexo == 1) {
        // Fórmula para mulheres
        pesoIdeal = (62.1 * altura) - 44.7;
        printf("Seu peso ideal é: %.2f kg\n", pesoIdeal);
    } 
    else if (sexo == 2) {
        // Fórmula para homens
        pesoIdeal = (72.7 * altura) - 58;
        printf("Seu peso ideal é: %.2f kg\n", pesoIdeal);
    } 
    else {
        printf("Sexo inválido! Digite 1 para Feminino ou 2 para Masculino.\n");
    }

    return 0;
}
