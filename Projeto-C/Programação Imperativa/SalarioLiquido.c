#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main () {
    setlocale(LC_ALL, "Portuguese");
    char nome[50];
    char sexo;
    int idade;
    float salB, saliq;

    for(int i = 1; i <= 2; i++){

    

    printf("Insira seu nome: \n");
    scanf("%s",nome);

    printf("Informe seu sexo (M) ou (F) \n");
    scanf(" %c",&sexo);

    printf("Insira sua idade: \n");
    scanf("%d",&idade);

    printf("Insira seu salario: \n");
    scanf("%f",&salB);

    switch (sexo) {
        case 'm':
        case 'M':
        if (idade >= 30){
            saliq = salB + (salB*0.10);
            printf("Seu salário liquido é: %.2f",saliq);


        } else {
            saliq = salB + (salB*0.08);
            printf("Seu salário liquido é: %.2f",saliq);
            
        }

        break;


        case 'f':
        case 'F':
        if (idade >= 30){
            saliq = salB + (salB*0.14);
            printf("Seu salário liquido é: %.2f",saliq);


        } else {
            saliq = salB + (salB*0.12);
            printf("Seu salário liquido é: %.2f",saliq);

        break;
    default:
    printf("Sexo inválido");


    }

    }
}
return 0;
}
