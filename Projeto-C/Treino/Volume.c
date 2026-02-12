#include <stdio.h>

int main () {
    float altura, largura, profundidade, volume;

    printf("Informe a altura da caixa em cm: \n");
    scanf("%f", &altura);
    printf("Informe a largura da caixa em cm: \n");
    scanf("%f", &largura);
    printf("Informe a profundidade da caixa em cm: \n");
    scanf("%f", &profundidade);

    volume = altura * largura * profundidade;

    printf("O volume foi de %.2f", volume);
}