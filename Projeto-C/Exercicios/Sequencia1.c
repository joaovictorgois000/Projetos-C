#include <stdio.h>

int main(){

    float c, f;

    printf("Digite a temperatura em Fahrenheit: \n");
    scanf("%f" , &f);

    c = (5 * f - 160) / 9.0;
    printf("A temperatura em Celsius é de: %f \n" ,c);
}