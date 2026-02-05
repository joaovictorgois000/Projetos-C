#include <stdio.h>

int main(){

    int senha = 1234;
    int acertou;
    
    printf("Digite a sua senha: \n");
    scanf("%d" , &senha);

    acertou = senha == 1234;

    if (acertou) {
        printf("Acesso permitido \n");

    } else {
        printf("Acesso negado \n");
    }
    
}