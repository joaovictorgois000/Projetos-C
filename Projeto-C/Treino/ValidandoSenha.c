#include <stdio.h>

int main () {
    int senha, senha_digitada;

    printf("Digite sua senha: \n");
    scanf("%d", &senha_digitada);

    senha = 1234;

    if (senha_digitada == senha) {
        printf("Acesso Permitido \n");
        
    } else {
        printf("Aceso negado \n");

    }

}