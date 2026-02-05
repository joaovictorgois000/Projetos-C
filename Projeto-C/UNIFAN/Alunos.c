#include <stdio.h>

 typedef struct Alunos {
    char nome [20];
    int matricula;
    float nota1, nota2;



}Alunos;

int main(){
    float media;

    for (int i = 0; i < 5; i++) {
        printf("%d", i);
        Alunos estudante;

        printf("Informe seu nome: \n");
        scanf("%s" , estudante.nome);

        printf("Informe sua matricula: \n");
        scanf("%d" , &estudante.matricula);

        printf("Insira sua primeira nota: \n");
        scanf("%f" , &estudante.nota1);

        printf("Insira sua segunda nota: \n");
        scanf("%f" , &estudante.nota2);

        media = (estudante.nota1 + estudante.nota2) / 2.0;

        printf("Sua media foi %f \n" , media);



    




    }


    


}

