#include <stdio.h>

int main(){

    float a, b, c;

    printf("Lado a: ");
    scanf("%f" , &a);

    printf("Lado b: ");
    scanf("%f" , &b);

    printf("Lado c: ");
    scanf("%f" , &c);

    if (a==b && b==c){
        printf("Equilatero \n");

    } else if ((a== b && a!= c) || (a == c && a!= b) || (c==b && c!= a)){
        printf("Isoceles \n");

    } else {
        printf("Escaleno \n");
    }


}