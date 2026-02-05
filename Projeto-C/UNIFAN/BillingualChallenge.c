#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função para transformar string em minúscula
void toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

typedef struct {
    char portugues[120];
    char ingles[120];
} atividade;

int main() {
    // Banco de palavras e frases
    atividade lista[] = {
        {"professor", "teacher"},
        {"enfermeira", "nurse"},
        {"queijo", "cheese"},
        {"leite", "milk"},
        {"escola", "school"},
        {"eu gosto de estudar ingles.", "i like to study english"},
        {"fernanda esta feliz", "fernanda is happy"},
        {"ela tem 10 anos", "she is 10 years old"},
        {"hoje esta fazendo muito frio", "it is very cold today"},
        {"caio esta com medo daquele cachorro", "caio is scared of that dog"},
        {"ele e meu irmao", "he is my brother"}
    };

    int n = sizeof(lista) / sizeof(lista[0]);
    int pontos = 0;
    char resposta[220];

    printf("**** Bem-vindo(a) ao Jogo de Ingles: Traducao de Palavras e Frases **** \n");
    printf("Digite a traducao correta em ingles sem abreviacoes!\n");
    printf("Nao se preocupe com maiusculas/minusculas.\n\n");

    for (int i = 0; i < n; i++) {
        printf("Traduza: %s\n", lista[i].portugues);
        printf("Sua resposta: ");
        fgets(resposta, sizeof(resposta), stdin);

        // remover '\n' do final
        resposta[strcspn(resposta, "\n")] = 0;

        // padronizar em minúsculas para comparação
        char respostaLower[220], inglesLower[220];
        strcpy(respostaLower, resposta);
        strcpy(inglesLower, lista[i].ingles);
        toLower(respostaLower);
        toLower(inglesLower);

        if (strcmp(respostaLower, inglesLower) == 0) {
            printf("✅ Correto!\n\n");
            pontos++;
        } else {
            printf("❌ Errado! Resposta correta: %s\n\n", lista[i].ingles);
        }
    }

    printf("**** Fim de jogo ****\n");
    printf("Voce acertou %d de %d.\n", pontos, n);

    if (pontos == n) {
        printf("🎉 Parabens!! Seu ingles esta excelente!\n");
    } else if (pontos >= n/2) {
        printf("👍 Muito bom! Continue praticando!\n");
    } else {
        printf("💪 Nao desanime! Pratique ate ficar craque!\n");
    }

    return 0;
}
