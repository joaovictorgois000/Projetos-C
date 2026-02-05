#include <stdio.h>

int main(){

    float produto, desconto, produto_com_desconto;

    printf("Insira o valor do produto: \n");
    scanf("%f" , &produto);

    desconto = produto * 15/100;
    produto_com_desconto = produto - desconto;

    printf("O valor do produto com desconto a vista foi de: %f \n" ,produto_com_desconto);
    
}