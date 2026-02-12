#include <stdio.h>

int main (){
    int numero;

    printf("Digite um número inteiro qualquer: \n");
    scanf("%d", &numero);

    printf("O sucessor do número digitado é de %d \n", numero + 1);
    printf("O antecesor do número digitado é %d \n", numero - 1);


}