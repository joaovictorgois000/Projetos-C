#include <stdio.h>

int main(){

    char plano;
    float salario, novo_salario;

    printf("Digite seu salario atual: \n");
    scanf("%f" , &salario);

    printf("Digite o plano de trabalho (A, B, C ou D): \n");
    scanf(" %c" ,  &plano);  // o espaço antes do %c é importante para ignorar o enter anterior

    switch(plano){
        case 'A':
        case 'a':
        novo_salario = salario * 1.5;  // Aumento de 5%
        break;
        case 'B':
        case 'b':
        novo_salario = salario * 1.10; // Aumento de 10%
        break;
        case 'C':
        case 'c':
        novo_salario = salario * 1.15; // Aumento de 15%
        break;
        case 'D':
        case 'd':
        novo_salario = salario * 1.20; // Aumento de 20%
        break;
        default:
        printf("Plano invalido \n");
        return 1; // encerra programa com erro



    }
    printf("Novo salario: R$ %2.f\n" , novo_salario);

    return 0;


}