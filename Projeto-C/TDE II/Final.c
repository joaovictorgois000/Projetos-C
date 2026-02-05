#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_JOGADORES 50

// -----------------------------
// ESTRUTURAS
// -----------------------------
typedef struct Atividade
{
    char portugues[200];
    char ingles[200];
    struct Atividade *next;
} Atividade;

typedef struct
{
    char nome[50];
    int idade;
    int nivel;
    int pontuacao;
    int ativo;
} Jogador;

// -----------------------------
// VARIÁVEIS GLOBAIS
// -----------------------------
Jogador jogadores[MAX_JOGADORES];
int total = 0;
Atividade *listaAtividades = NULL;

// -----------------------------
// UTILITÁRIOS (comparação case-insensitive)
// -----------------------------
void toLowerCopy(const char *src, char *dst, size_t dstsize)
{
    if (dstsize == 0) return;
    size_t i;
    for (i = 0; src[i] && i < dstsize - 1; i++)
        dst[i] = (char)tolower((unsigned char)src[i]);
    dst[i] = '\0';
}

// Trim (remover espaços iniciais/finais) e transformar em minusculas in-place
void trimLower(char *s)
{
    // remover espaços iniciais
    int start = 0;
    while (s[start] && isspace((unsigned char)s[start]))
        start++;

    // mover para o início e minúsculas
    int i = start, j = 0;
    while (s[i])
    {
        s[j++] = (char)tolower((unsigned char)s[i++]);
    }
    s[j] = '\0';

    // remover espaços finais
    while (j > 0 && isspace((unsigned char)s[j - 1]))
    {
        s[--j] = '\0';
    }
}

// Comparação case-insensitive: retorna <0 se a<b, 0 se iguais, >0 se a>b
int cmpNames(const char *a, const char *b)
{
    char A[200], B[200];
    toLowerCopy(a, A, sizeof(A));
    toLowerCopy(b, B, sizeof(B));
    // trim spaces ends (to be consistent)
    trimLower(A);
    trimLower(B);
    return strcmp(A, B);
}

// -----------------------------
// LISTA DINÂMICA DE ATIVIDADES
// -----------------------------
Atividade *criarAtividade(const char *pt, const char *en)
{
    Atividade *novo = (Atividade *)malloc(sizeof(Atividade));
    if (!novo)
    {
        printf("Erro: memoria insuficiente ao criar atividade.\n");
        exit(1);
    }
    strncpy(novo->portugues, pt, sizeof(novo->portugues) - 1);
    novo->portugues[sizeof(novo->portugues) - 1] = '\0';
    strncpy(novo->ingles, en, sizeof(novo->ingles) - 1);
    novo->ingles[sizeof(novo->ingles) - 1] = '\0';
    novo->next = NULL;
    return novo;
}

// Insere no fim (mantém a ordem das atividades iniciais)
void inserirAtividadeFim(const char *pt, const char *en)
{
    Atividade *novo = criarAtividade(pt, en);
    if (!listaAtividades)
    {
        listaAtividades = novo;
        return;
    }
    Atividade *p = listaAtividades;
    while (p->next) p = p->next;
    p->next = novo;
}

void listarAtividades()
{
    if (!listaAtividades)
    {
        printf("\nNenhuma atividade cadastrada.\n");
        return;
    }
    printf("\n--- Lista de Atividades ---\n");
    Atividade *p = listaAtividades;
    int i = 1;
    while (p)
    {
        printf("%d) PT: %s\n   EN: %s\n", i, p->portugues, p->ingles);
        p = p->next;
        i++;
    }
}

// Remove primeira ocorrência que tenha portugues igual (comparacao exata)
void removerAtividade(const char *pt)
{
    if (!listaAtividades)
    {
        printf("Lista de atividades vazia.\n");
        return;
    }
    Atividade *p = listaAtividades, *ant = NULL;
    while (p)
    {
        if (strcmp(p->portugues, pt) == 0)
        {
            if (ant) ant->next = p->next;
            else listaAtividades = p->next;
            free(p);
            printf("Atividade removida!\n");
            return;
        }
        ant = p;
        p = p->next;
    }
    printf("Atividade não encontrada (texto em português nao corresponde exatamente).\n");
}

// Edita a primeira atividade cuja parte em portugues seja exatamente igual ao fornecido
void editarAtividade(const char *pt)
{
    if (!listaAtividades)
    {
        printf("Lista de atividades vazia.\n");
        return;
    }
    Atividade *p = listaAtividades;
    while (p)
    {
        if (strcmp(p->portugues, pt) == 0)
        {
            printf("Atividade encontrada.\n");
            printf("Novo texto em português (enter para manter): ");
            char novoPT[200];
            if (!fgets(novoPT, sizeof(novoPT), stdin))
                novoPT[0] = '\0';
            novoPT[strcspn(novoPT, "\n")] = 0;
            if (strlen(novoPT) > 0)
                strncpy(p->portugues, novoPT, sizeof(p->portugues) - 1);

            printf("Novo texto em inglês (enter para manter): ");
            char novoEN[200];
            if (!fgets(novoEN, sizeof(novoEN), stdin))
                novoEN[0] = '\0';
            novoEN[strcspn(novoEN, "\n")] = 0;
            if (strlen(novoEN) > 0)
                strncpy(p->ingles, novoEN, sizeof(p->ingles) - 1);

            printf("Atividade atualizada!\n");
            return;
        }
        p = p->next;
    }
    printf("Atividade não encontrada (texto em português nao corresponde exatamente).\n");
}

void liberarAtividades()
{
    Atividade *p = listaAtividades;
    while (p)
    {
        Atividade *tmp = p->next;
        free(p);
        p = tmp;
    }
    listaAtividades = NULL;
}

// -----------------------------
// FUNÇÕES DO JOGO DE TRADUÇÃO (usando lista dinâmica)
// -----------------------------
void jogoTraducaoParaJogador(int idxJogador)
{
    if (idxJogador < 0 || idxJogador >= total)
    {
        printf("Índice de jogador invalido.\n");
        return;
    }

    if (!listaAtividades)
    {
        printf("Nenhuma atividade cadastrada para o jogo.\n");
        return;
    }

    printf("\n==== JOGO DE TRADUÇÃO (Jogador: %s) ====\n", jogadores[idxJogador].nome);
    printf("Para cada resposta correta, o jogador ganha +1 ponto.\n");
    printf("Digite a tradução em inglês (sem abreviações). Não se preocupe com maiúsculas.\n");
    printf("Para retornar ao menu a qualquer momento e salvar seus pontos desta sessão, digite: menu\n\n");

    Atividade *p = listaAtividades;
    char resposta[300];
    int pontosSessao = 0;

    while (p)
    {
        printf("Traduza: %s\n", p->portugues);
        printf("Sua resposta: ");
        if (!fgets(resposta, sizeof(resposta), stdin))
            resposta[0] = '\0';
        resposta[strcspn(resposta, "\n")] = 0;

        char respLow[300], corretoLow[300];
        strncpy(respLow, resposta, sizeof(respLow) - 1);
        respLow[sizeof(respLow) - 1] = '\0';
        strncpy(corretoLow, p->ingles, sizeof(corretoLow) - 1);
        corretoLow[sizeof(corretoLow) - 1] = '\0';

        trimLower(respLow);
        trimLower(corretoLow);

        if (strcmp(respLow, "menu") == 0)
        {
            jogadores[idxJogador].pontuacao += pontosSessao;
            printf("\nVoltando ao menu... %s ganhou %d ponto(s) nesta sessão (salvo).\n", jogadores[idxJogador].nome, pontosSessao);
            printf("Pontuação total atual de %s: %d\n", jogadores[idxJogador].nome, jogadores[idxJogador].pontuacao);
            return;
        }

        if (strcmp(respLow, corretoLow) == 0)
        {
            printf("✔ Correto!\n\n");
            pontosSessao++;
        }
        else
        {
            printf("✘ Errado! Resposta correta: %s\n\n", p->ingles);
        }

        p = p->next;
    }

    jogadores[idxJogador].pontuacao += pontosSessao;
    printf("Fim da sessão. %s ganhou %d ponto(s) nesta sessão.\n", jogadores[idxJogador].nome, pontosSessao);
    printf("Pontuação total atual de %s: %d\n", jogadores[idxJogador].nome, jogadores[idxJogador].pontuacao);
}

// -----------------------------
// GERENCIAMENTO DE JOGADORES (inserção ordenada, busca binária, CRUD)
// -----------------------------
void inserirOrdenado(Jogador novo)
{
    if (total >= MAX_JOGADORES)
    {
        printf("Limite de jogadores atingido!\n");
        return;
    }

    int i = total - 1;
    while (i >= 0 && cmpNames(jogadores[i].nome, novo.nome) > 0)
    {
        jogadores[i + 1] = jogadores[i];
        i--;
    }

    jogadores[i + 1] = novo;
    total++;
    printf("Jogador cadastrado com sucesso!\n");
}

// Busca binária case-insensitive
int buscarPorNome(const char *nome)
{
    int ini = 0, fim = total - 1;

    while (ini <= fim)
    {
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

void cadastrarJogador()
{
    Jogador j;
    printf("\n--- Cadastro de Jogador ---\n");
    printf("Nome: ");
    if (scanf(" %[^\n]s", j.nome) != 1) j.nome[0] = '\0';
    printf("Idade: ");
    if (scanf("%d", &j.idade) != 1) j.idade = 0;
    printf("Nivel: ");
    if (scanf("%d", &j.nivel) != 1) j.nivel = 0;
    j.pontuacao = 0; // inicia em zero
    j.ativo = 1;
    getchar(); // limpa buffer
    inserirOrdenado(j);
}

void listarJogadores()
{
    if (total == 0)
    {
        printf("\nNenhum jogador cadastrado!\n");
        return;
    }
    printf("\n--- Lista de Jogadores (ordem alfabetica) ---\n");
    for (int i = 0; i < total; i++)
    {
        if (jogadores[i].ativo)
        {
            printf("%d - %s | Idade: %d | Nivel: %d | Pontos: %d\n",
                   i, jogadores[i].nome, jogadores[i].idade, jogadores[i].nivel, jogadores[i].pontuacao);
        }
    }
}

void removerJogador()
{
    char nome[50];
    printf("Nome do jogador a remover: ");
    if (scanf(" %[^\n]s", nome) != 1) { getchar(); return; }
    getchar();
    int idx = buscarPorNome(nome);
    if (idx == -1)
    {
        printf("Jogador não encontrado!\n");
        return;
    }
    for (int i = idx; i < total - 1; i++)
        jogadores[i] = jogadores[i + 1];
    total--;
    printf("Jogador removido!\n");
}

void atualizarJogador()
{
    char nome[50];
    printf("Nome do jogador a atualizar: ");
    if (scanf(" %[^\n]s", nome) != 1) { getchar(); return; }
    getchar();

    int idx = buscarPorNome(nome);
    if (idx == -1)
    {
        printf("Jogador não encontrado!\n");
        return;
    }

    Jogador j = jogadores[idx]; // pega valores atuais (inclui pontuação)
    printf("Novo nome (enter para manter '%s'): ", jogadores[idx].nome);
    char novoNome[50];
    if (!fgets(novoNome, sizeof(novoNome), stdin))
        novoNome[0] = '\0';
    novoNome[strcspn(novoNome, "\n")] = 0;
    if (strlen(novoNome) > 0)
        strncpy(j.nome, novoNome, sizeof(j.nome) - 1);

    printf("Nova idade (atual %d, digite -1 para manter): ", jogadores[idx].idade);
    int novaIdade;
    if (scanf("%d", &novaIdade) == 1)
    {
        if (novaIdade != -1)
            j.idade = novaIdade;
    }
    printf("Novo nivel (atual %d, digite -1 para manter): ", jogadores[idx].nivel);
    int novoNivel;
    if (scanf("%d", &novoNivel) == 1)
    {
        if (novoNivel != -1)
            j.nivel = novoNivel;
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

// Busca de jogador e exibição da pontuação
void buscarMostrarPontuacao()
{
    char nome[50];
    printf("Digite o nome do jogador para buscar: ");
    if (scanf(" %[^\n]s", nome) != 1) { getchar(); return; }
    getchar();
    int idx = buscarPorNome(nome);
    if (idx == -1)
    {
        printf("Jogador '%s' nao existe.\n", nome);
    }
    else
    {
        printf("Jogador encontrado: %s\n", jogadores[idx].nome);
        printf("Pontuação total: %d\n", jogadores[idx].pontuacao);
    }
}

// -----------------------------
// RANKING POR PONTUACAO
// -----------------------------
int cmpPontuacaoDesc(const void *a, const void *b)
{
    const Jogador *pa = (const Jogador *)a;
    const Jogador *pb = (const Jogador *)b;
    if (pa->pontuacao != pb->pontuacao)
        return (pb->pontuacao - pa->pontuacao); // descendente
    // empate por pontuação: ordenar alfabeticamente (case-insensitive)
    return cmpNames(pa->nome, pb->nome);
}

void imprimirRanking()
{
    if (total == 0)
    {
        printf("\nNenhum jogador cadastrado!\n");
        return;
    }

    // Criar cópia apenas com jogadores ativos
    int copiaCount = 0;
    Jogador *copia = malloc(sizeof(Jogador) * total);
    if (!copia)
    {
        printf("Erro de memória ao criar cópia para ranking.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (jogadores[i].ativo)
        {
            copia[copiaCount++] = jogadores[i];
        }
    }

    // Ordenar a cópia por pontuação (desc)
    qsort(copia, copiaCount, sizeof(Jogador), cmpPontuacaoDesc);

    // Exibir ranking
    printf("\n=== RANKING POR PONTUAÇÃO ===\n");
    printf("%-4s %-25s %-8s %-6s\n", "Pos", "Nome", "Pontos", "Nivel");
    for (int i = 0; i < copiaCount; i++)
    {
        printf("%-4d %-25s %-8d %-6d\n", i + 1, copia[i].nome, copia[i].pontuacao, copia[i].nivel);
    }

    free(copia);
}

// -----------------------------
// INICIAR JOGO POR JOGADOR (menu auxiliar)
// -----------------------------
void iniciarJogoMenu()
{
    char nome[50];
    printf("Digite o nome do jogador que vai jogar: ");
    if (scanf(" %[^\n]s", nome) != 1) { getchar(); return; }
    getchar();

    int idx = buscarPorNome(nome);
    if (idx == -1)
    {
        printf("Jogador não encontrado. Deseja cadastrar '%s'? (s/n): ", nome);
        char resp = getchar();
        getchar();
        if (resp == 's' || resp == 'S')
        {
            Jogador novo;
            strncpy(novo.nome, nome, sizeof(novo.nome) - 1);
            novo.nome[sizeof(novo.nome) - 1] = '\0';
            printf("Idade: ");
            if (scanf("%d", &novo.idade) != 1) novo.idade = 0;
            printf("Nivel: ");
            if (scanf("%d", &novo.nivel) != 1) novo.nivel = 0;
            getchar();
            novo.pontuacao = 0;
            novo.ativo = 1;
            inserirOrdenado(novo);
            // Buscar novamente índice do novo jogador
            idx = buscarPorNome(nome);
            if (idx == -1)
            {
                printf("Erro ao cadastrar novo jogador.\n");
                return;
            }
        }
        else
        {
            printf("Voltando ao menu.\n");
            return;
        }
    }

    // Jogador existe -> inicia o jogo para esse jogador
    jogoTraducaoParaJogador(idx);
}

// -----------------------------
// CARREGAR ATIVIDADES INICIAIS
// -----------------------------
void carregarAtividadesIniciais()
{
    // Inserir em ordem para manter a mesma ordem do array original
    inserirAtividadeFim("professor", "teacher");
    inserirAtividadeFim("enfermeira", "nurse");
    inserirAtividadeFim("queijo", "cheese");
    inserirAtividadeFim("leite", "milk");
    inserirAtividadeFim("escola", "school");
    inserirAtividadeFim("eu gosto de estudar ingles.", "i like to study english");
    inserirAtividadeFim("fernanda esta feliz", "fernanda is happy");
    inserirAtividadeFim("ela tem 10 anos", "she is 10 years old");
    inserirAtividadeFim("hoje esta fazendo muito frio", "it is very cold today");
    inserirAtividadeFim("caio esta com medo daquele cachorro", "caio is scared of that dog");
    inserirAtividadeFim("ele e meu irmao", "he is my brother");
    inserirAtividadeFim("eu estou com fome", "i am hungry");
    inserirAtividadeFim("voce gosta de musica?", "do you like music?");
    inserirAtividadeFim("eles estao jogando futebol", "they are playing soccer");
    inserirAtividadeFim("nos vamos ao mercado agora", "we are going to the market now");
    inserirAtividadeFim("minha mae trabalha no hospital", "my mother works at the hospital");
    inserirAtividadeFim("amanha sera um dia importante", "tomorrow will be an important day");
    inserirAtividadeFim("eu nao entendi o que voce disse", "i did not understand what you said");
    inserirAtividadeFim("voce pode me ajudar com isso?", "can you help me with this?");
    inserirAtividadeFim("o cachorro dorme na sala", "the dog sleeps in the living room");
    inserirAtividadeFim("o livro estava em cima da mesa", "the book was on the table");
    inserirAtividadeFim("eu preciso estudar para a prova", "i need to study for the test");
    inserirAtividadeFim("ela vai viajar semana que vem", "she is going to travel next week");
    inserirAtividadeFim("estou esperando meu amigo chegar", "i am waiting for my friend to arrive");
    inserirAtividadeFim("hoje acordei muito cedo", "i woke up very early today");
    inserirAtividadeFim("eles compraram uma casa nova", "they bought a new house");
    inserirAtividadeFim("eu acho esse filme muito engraçado", "i think this movie is very funny");
    inserirAtividadeFim("voce pode repetir por favor?", "can you repeat please?");
    inserirAtividadeFim("estamos aprendendo ingles juntos", "we are learning english together");
    inserirAtividadeFim("minha escola fica perto de casa", "my school is close to my home");
    inserirAtividadeFim("o tempo hoje esta muito agradavel", "the weather today is very pleasant");
}

// -----------------------------
// MAIN E MENUS
// -----------------------------
int main()
{
    // carrega atividades padrão
    carregarAtividadesIniciais();

    int op;
    do
    {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Jogo de Tradução (atribui pontos ao jogador)\n");
        printf("2 - Gerenciamento de Jogadores\n");
        printf("3 - Gerenciamento de Atividades\n");
        printf("4 - Imprimir tabela de pontuacao (ranking)\n");
        printf("5 - Buscar jogador e ver pontuacao\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &op) != 1)
        {
            // entrada inválida -> limpar e continuar
            while (getchar() != '\n') ;
            op = 0;
        }
        getchar(); // limpa buffer

        if (op == 1)
        {
            iniciarJogoMenu();
        }
        else if (op == 2)
        {
            int op2;
            do
            {
                printf("\n--- Gerenciamento de Jogadores ---\n");
                printf("1 - Cadastrar\n");
                printf("2 - Listar\n");
                printf("3 - Atualizar\n");
                printf("4 - Remover\n");
                printf("5 - Voltar\n");
                printf("Escolha: ");
                if (scanf("%d", &op2) != 1)
                {
                    while (getchar() != '\n') ;
                    op2 = 0;
                }
                getchar();

                switch (op2)
                {
                case 1:
                    cadastrarJogador();
                    break;
                case 2:
                    listarJogadores();
                    break;
                case 3:
                    atualizarJogador();
                    break;
                case 4:
                    removerJogador();
                    break;
                case 5:
                    break;
                default:
                    if (op2 != 0) printf("Opção inválida!\n");
                }

            } while (op2 != 5);
        }
        else if (op == 3)
        {
            int a;
            do
            {
                printf("\n--- Gerenciamento de Atividades ---\n");
                printf("1 - Inserir Atividade\n");
                printf("2 - Listar Atividades\n");
                printf("3 - Editar Atividade (procurar pelo texto em português exato)\n");
                printf("4 - Remover Atividade (procurar pelo texto em português exato)\n");
                printf("5 - Voltar\n");
                printf("Escolha: ");
                if (scanf("%d", &a) != 1)
                {
                    while (getchar() != '\n') ;
                    a = 0;
                }
                getchar();

                if (a == 1)
                {
                    char pt[200], en[200];
                    printf("Português: ");
                    if (!fgets(pt, sizeof(pt), stdin)) pt[0] = '\0';
                    pt[strcspn(pt, "\n")] = 0;
                    printf("Inglês: ");
                    if (!fgets(en, sizeof(en), stdin)) en[0] = '\0';
                    en[strcspn(en, "\n")] = 0;
                    inserirAtividadeFim(pt, en);
                    printf("Atividade inserida.\n");
                }
                else if (a == 2)
                {
                    listarAtividades();
                }
                else if (a == 3)
                {
                    char pt[200];
                    printf("Digite o texto em português da atividade a editar (exato): ");
                    if (!fgets(pt, sizeof(pt), stdin)) pt[0] = '\0';
                    pt[strcspn(pt, "\n")] = 0;
                    editarAtividade(pt);
                }
                else if (a == 4)
                {
                    char pt[200];
                    printf("Digite o texto em português da atividade a remover (exato): ");
                    if (!fgets(pt, sizeof(pt), stdin)) pt[0] = '\0';
                    pt[strcspn(pt, "\n")] = 0;
                    removerAtividade(pt);
                }

            } while (a != 5);
        }
        else if (op == 4)
        {
            imprimirRanking();
        }
        else if (op == 5)
        {
            buscarMostrarPontuacao();
        }
        else if (op == 6)
        {
            printf("Saindo...\n");
        }
        else
        {
            if (op != 0) printf("Opção inválida!\n");
        }

    } while (op != 6);

    // liberar memoria antes de sair
    liberarAtividades();

    return 0;
}
