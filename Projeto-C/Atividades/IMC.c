#include <stdio.h>

int main() {
    float peso, altura, imc;

    // Leitura do peso e da altura
    printf("Digite o peso em kg: ");
    scanf("%f", &peso);

    printf("Digite a altura em metros: ");
    scanf("%f", &altura);

    // Cálculo do IMC
    imc = peso / (altura * altura);

    // Exibição do IMC e condição
    printf("Seu IMC é: %.2f\n", imc);

    if (imc < 18.5) {
        printf("Condição: Abaixo do peso\n");
    } else if (imc >= 18.5 && imc < 25) {
        printf("Condição: Peso normal\n");
    } else if (imc >= 25 && imc < 30) {
        printf("Condição: Acima do peso\n");
    } else {
        printf("Condição: Obeso\n");
    }

    return 0;
}
