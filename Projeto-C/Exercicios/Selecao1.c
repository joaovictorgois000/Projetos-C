#include <stdio.h>

int main(){

    float v1, v2, v3, soma;

    printf("Escreva tres valores: \n");
    scanf("%f %f %f" , &v1, &v2, &v3);

    if (v1 < v2 && v1 < v3){
        soma = v2 + v3;
    } else if (v2 < v1 && v2< v3){
        soma = v1 + v3;

    } else {
        soma = v1 + v2;
    }
    printf("A soma do dois maiores valores é de: %f" , soma);

    return 0;
}