#include <stdio.h>

int main(){
    float salario;

    printf("Digite o valor do seu salário a ser reajustado: \n");
    scanf("%f", &salario);

    printf("O seu salário com o reajuste é de: %2.f", salario * 0.05 + salario);
}