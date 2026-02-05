#include <stdio.h>

int main() {
    int senha = 1234;
    int senha_digitada;

    printf("Digite sua senha: \n");
    scanf("%d", &senha_digitada);

    if (senha_digitada == senha) {
        printf("Acesso permitido \n");


    } else {
        printf("Acesso negado \n");

    }

    
}