#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_JOGADORES 50

// -----------------------------
// ESTRUTURAS
// -----------------------------
typedef struct {
    char nome[50];
    int idade;
    int nivel;
    int pontuacao;
    int ativo;
} Jogador;

typedef struct {
    char portugues[200];
    char ingles[200];
} Atividade;

// -----------------------------
// VARIÁVEIS GLOBAIS
// -----------------------------
Jogador jogadores[MAX_JOGADORES];
int total = 0;

// -----------------------------
// UTILITÁRIOS (comparação case-insensitive)
// -----------------------------
void strToLowerCopy(const char *src, char *dst) {
    for (int i = 0; src[i] && i < 200; i++) {
        dst[i] = (char) tolower((unsigned char) src[i]);
        dst[i+1] = '\0';
    }
}

// Comparação case-insensitive: retorna <0 se a<b, 0 se iguais, >0 se a>b
int cmpNames(const char *a, const char *b) {
    char A[200], B[200];
    strToLowerCopy(a, A);
    strToLowerCopy(b, B);
    return strcmp(A, B);
}

// -----------------------------
// FUNÇÕES DO JOGO DE TRADUÇÃO
// -----------------------------
void toLowerInplace(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = (char) tolower((unsigned char) str[i]);
}

void jogoTraducaoParaJogador(int idxJogador) {
    // Lista de atividades (português -> inglês)
    Atividade lista[] = {
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
        {"ele e meu irmao", "he is my brother"},
        {"eu estou com fome", "i am hungry"},
        {"voce gosta de musica?", "do you like music?"},
        {"eles estao jogando futebol", "they are playing soccer"},
        {"nos vamos ao mercado agora", "we are going to the market now"},
        {"minha mae trabalha no hospital", "my mother works at the hospital"},
        {"amanha sera um dia importante", "tomorrow will be an important day"},
        {"eu nao entendi o que voce disse", "i did not understand what you said"},
        {"voce pode me ajudar com isso?", "can you help me with this?"},
        {"o cachorro dorme na sala", "the dog sleeps in the living room"},
        {"o livro estava em cima da mesa", "the book was on the table"},
        {"eu preciso estudar para a prova", "i need to study for the test"},
        {"ela vai viajar semana que vem", "she is going to travel next week"},
        {"estou esperando meu amigo chegar", "i am waiting for my friend to arrive"},
        {"hoje acordei muito cedo", "i woke up very early today"},
        {"eles compraram uma casa nova", "they bought a new house"},
        {"eu acho esse filme muito engraçado", "i think this movie is very funny"},
        {"voce pode repetir por favor?", "can you repeat please?"},
        {"estamos aprendendo ingles juntos", "we are learning english together"},
        {"minha escola fica perto de casa", "my school is close to my home"},
        {"o tempo hoje esta muito agradavel", "the weather today is very pleasant"}
    };

    int n = sizeof(lista) / sizeof(lista[0]);
    char resposta[300];
    int pontosSessao = 0;

    printf("\n==== JOGO DE TRADUÇÃO (Jogador: %s) ====\n", jogadores[idxJogador].nome);
    printf("Para cada resposta correta, o jogador ganha +1 ponto.\n");
    printf("Digite a tradução em inglês (sem abreviações). Não se preocupe com maiúsculas.\n\n");

    for (int i = 0; i < n; i++) {
        printf("Traduza: %s\n", lista[i].portugues);
        printf("Sua resposta: ");
        if (!fgets(resposta, sizeof(resposta), stdin)) resposta[0] = '\0';
        resposta[strcspn(resposta, "\n")] = 0;

        char respLow[300], inglLow[300];
        strcpy(respLow, resposta);
        strcpy(inglLow, lista[i].ingles);
        toLowerInplace(respLow);
        toLowerInplace(inglLow);

        if (strcmp(respLow, inglLow) == 0) {
            printf("✔ Correto!\n\n");
            pontosSessao++;
        } else {
            printf("✘ Errado! Resposta correta: %s\n\n", lista[i].ingles);
        }
    }

    jogadores[idxJogador].pontuacao += pontosSessao;
    printf("Fim da sessão. %s ganhou %d ponto(s) nesta sessão.\n", jogadores[idxJogador].nome, pontosSessao);
    printf("Pontuação total atual de %s: %d\n", jogadores[idxJogador].nome, jogadores[idxJogador].pontuacao);
}

// -----------------------------
// GERENCIAMENTO DE JOGADORES (inserção ordenada, busca binária, CRUD)
// -----------------------------
void inserirOrdenado(Jogador novo) {
    if (total >= MAX_JOGADORES) {
        printf("Limite de jogadores atingido!\n");
        return;
    }

    int i = total - 1;
    while (i >= 0 && cmpNames(jogadores[i].nome, novo.nome) > 0) {
        jogadores[i + 1] = jogadores[i];
        i--;
    }

    jogadores[i + 1] = novo;
    total++;
    printf("Jogador cadastrado com sucesso!\n");
}

// Busca binária case-insensitive
int buscarPorNome(const char *nome) {
    int ini = 0, fim = total - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = cmpNames(nome, jogadores[meio].nome);

        if (cmp == 0 && jogadores[meio].ativo)
            return meio;
        else if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

void cadastrarJogador() {
    Jogador j;
    printf("\n--- Cadastro de Jogador ---\n");
    printf("Nome: ");
    scanf(" %[^\n]s", j.nome);
    printf("Idade: ");
    scanf("%d", &j.idade);
    printf("Nivel: ");
    scanf("%d", &j.nivel);
    j.pontuacao = 0; // inicia em zero
    j.ativo = 1;
    // limpa buffer
    getchar();
    inserirOrdenado(j);
}

void listarJogadores() {
    if (total == 0) {
        printf("\nNenhum jogador cadastrado!\n");
        return;
    }
    printf("\n--- Lista de Jogadores (ordem alfabetica) ---\n");
    for (int i = 0; i < total; i++) {
        if (jogadores[i].ativo) {
            printf("%d - %s | Idade: %d | Nivel: %d | Pontos: %d\n",
                i, jogadores[i].nome, jogadores[i].idade, jogadores[i].nivel, jogadores[i].pontuacao);
        }
    }
}

void removerJogador() {
    char nome[50];
    printf("Nome do jogador a remover: ");
    scanf(" %[^\n]s", nome);
    getchar();
    int idx = buscarPorNome(nome);
    if (idx == -1) {
        printf("Jogador não encontrado!\n");
        return;
    }
    for (int i = idx; i < total - 1; i++)
        jogadores[i] = jogadores[i + 1];
    total--;
    printf("Jogador removido!\n");
}

void atualizarJogador() {
    char nome[50];
    printf("Nome do jogador a atualizar: ");
    scanf(" %[^\n]s", nome);
    getchar();

    int idx = buscarPorNome(nome);
    if (idx == -1) {
        printf("Jogador não encontrado!\n");
        return;
    }

    Jogador j = jogadores[idx]; // pega valores atuais (inclui pontuação)
    printf("Novo nome (enter para manter '%s'): ", jogadores[idx].nome);
    char novoNome[50];
    if (!fgets(novoNome, sizeof(novoNome), stdin)) novoNome[0] = '\0';
    novoNome[strcspn(novoNome, "\n")] = 0;
    if (strlen(novoNome) > 0) strcpy(j.nome, novoNome);

    printf("Nova idade (atual %d, digite -1 para manter): ", jogadores[idx].idade);
    int novaIdade;
    if (scanf("%d", &novaIdade) == 1) {
        if (novaIdade != -1) j.idade = novaIdade;
    }
    printf("Novo nivel (atual %d, digite -1 para manter): ", jogadores[idx].nivel);
    int novoNivel;
    if (scanf("%d", &novoNivel) == 1) {
        if (novoNivel != -1) j.nivel = novoNivel;
    }
    getchar(); // limpa buffer

    // Mantemos j.pontuacao (não resetamos)
    // Remover antigo elemento e reinsere ordenado para manter alfabetico (se nome mudou)
    for (int i = idx; i < total - 1; i++)
        jogadores[i] = jogadores[i + 1];
    total--;

    inserirOrdenado(j);
    printf("Jogador atualizado!\n");
}

// Busca de jogador e exibição da pontuação (requisito 5)
void buscarMostrarPontuacao() {
    char nome[50];
    printf("Digite o nome do jogador para buscar: ");
    scanf(" %[^\n]s", nome);
    getchar();
    int idx = buscarPorNome(nome);
    if (idx == -1) {
        printf("Jogador '%s' nao existe.\n", nome);
    } else {
        printf("Jogador encontrado: %s\n", jogadores[idx].nome);
        printf("Pontuação total: %d\n", jogadores[idx].pontuacao);
    }
}

// -----------------------------
// RANKING POR PONTUACAO (requisito 6)
// -----------------------------
int cmpPontuacaoDesc(const void *a, const void *b) {
    const Jogador *pa = (const Jogador *) a;
    const Jogador *pb = (const Jogador *) b;
    if (pa->pontuacao != pb->pontuacao)
        return (pb->pontuacao - pa->pontuacao); // descendente
    // empate por pontuação: ordenar alfabeticamente (case-insensitive)
    return cmpNames(pa->nome, pb->nome);
}

void imprimirRanking() {
    if (total == 0) {
        printf("\nNenhum jogador cadastrado!\n");
        return;
    }

    // Criar cópia apenas com jogadores ativos
    int copiaCount = 0;
    Jogador *copia = malloc(sizeof(Jogador) * total);
    if (!copia) {
        printf("Erro de memória ao criar cópia para ranking.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        if (jogadores[i].ativo) {
            copia[copiaCount++] = jogadores[i];
        }
    }

    // Ordenar a cópia por pontuação (desc)
    qsort(copia, copiaCount, sizeof(Jogador), cmpPontuacaoDesc);

    // Exibir ranking
    printf("\n=== RANKING POR PONTUAÇÃO ===\n");
    printf("%-4s %-25s %-8s %-6s\n", "Pos", "Nome", "Pontos", "Nivel");
    for (int i = 0; i < copiaCount; i++) {
        printf("%-4d %-25s %-8d %-6d\n", i + 1, copia[i].nome, copia[i].pontuacao, copia[i].nivel);
    }

    free(copia);
}

// -----------------------------
// MENU PARA INICIAR JOGO (associado a jogador)
// -----------------------------
void iniciarJogoMenu() {
    char nome[50];
    printf("Digite o nome do jogador que vai jogar: ");
    scanf(" %[^\n]s", nome);
    getchar();

    int idx = buscarPorNome(nome);
    if (idx == -1) {
        printf("Jogador não encontrado. Deseja cadastrar '%s'? (s/n): ", nome);
        char resp = getchar();
        getchar();
        if (resp == 's' || resp == 'S') {
            Jogador novo;
            strcpy(novo.nome, nome);
            printf("Idade: ");
            scanf("%d", &novo.idade);
            printf("Nivel: ");
            scanf("%d", &novo.nivel);
            getchar();
            novo.pontuacao = 0;
            novo.ativo = 1;
            inserirOrdenado(novo);
            // Buscar novamente índice do novo jogador
            idx = buscarPorNome(nome);
            if (idx == -1) {
                printf("Erro ao cadastrar novo jogador.\n");
                return;
            }
        } else {
            printf("Voltando ao menu.\n");
            return;
        }
    }

    // Jogador existe -> inicia o jogo para esse jogador
    jogoTraducaoParaJogador(idx);
}

// -----------------------------
// MAIN E MENUS
// -----------------------------
int main() {
    int op;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Jogo de Tradução (atribui pontos ao jogador)\n");
        printf("2 - Gerenciamento de Jogadores\n");
        printf("3 - Buscar jogador e ver pontuacao\n");
        printf("4 - Imprimir tabela de pontuacao (ranking)\n");
        printf("5 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &op) != 1) {
            // entrada inválida -> limpar e continuar
            while (getchar() != '\n');
            op = 0;
        }
        getchar(); // limpa buffer

        if (op == 1) {
            iniciarJogoMenu();
        }
        else if (op == 2) {
            int op2;
            do {
                printf("\n--- Gerenciamento de Jogadores ---\n");
                printf("1 - Cadastrar\n");
                printf("2 - Listar\n");
                printf("3 - Atualizar\n");
                printf("4 - Remover\n");
                printf("5 - Voltar\n");
                printf("Escolha: ");
                if (scanf("%d", &op2) != 1) {
                    while (getchar() != '\n');
                    op2 = 0;
                }
                getchar();

                switch (op2) {
                    case 1: cadastrarJogador(); break;
                    case 2: listarJogadores(); break;
                    case 3: atualizarJogador(); break;
                    case 4: removerJogador(); break;
                    case 5: break;
                    default: if (op2 != 0) printf("Opção inválida!\n");
                }

            } while (op2 != 5);
        }
        else if (op == 3) {
            buscarMostrarPontuacao();
        }
        else if (op == 4) {
            imprimirRanking();
        }
        else if (op == 5) {
            printf("Saindo...\n");
        }
        else {
            if (op != 0) printf("Opção inválida!\n");
        }

    } while (op != 5);

    return 0;
}
