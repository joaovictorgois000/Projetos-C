#include <stdio.h>

int main(){

    float volume, altura, largura, profundidade;

    printf("Digite o valor da altura da caixa d'agua: \n");
    scanf("%f" , &altura);
    printf("Digite o valor da largura da caixa d'agua: \n");
    scanf("%f" , &largura);
    printf("Digite o valor da profundidade da caixa d'agua: \n");
    scanf("%f" , &profundidade);

    volume = altura * largura * profundidade;

    printf("O volume da caixa d'agua foi de: %f \n" , volume);
}