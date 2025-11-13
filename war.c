#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIO 3
#define TAM_STRING 100

struct Territorio
{
    char nome[TAM_STRING];
    char cor_exercito[TAM_STRING];
    int qntd_tropas;
};

/* Prototypes */
struct Territorio* alocarMapa(void);
void inicializarTerritorios(struct Territorio* mapa);
void liberarMemoria(struct Territorio* mapa);
void exibirMenuPrincipal(void);
void exibirMapa(const struct Territorio* mapa);
void exibirMissao(int id_missao);
void faseDeAtaque(struct Territorio* mapa);
void simularAtaque(struct Territorio* mapa, int atacante, int defensor);
int sortearMissao(void);
int verificarVitoria(const struct Territorio* mapa, int id_missao);
void limparBufferEntrada(void);

int main(void) {
    srand((unsigned)time(NULL));
    struct Territorio* mapa = alocarMapa();

    inicializarTerritorios(mapa);

    int id_missao = sortearMissao();
    int opcao = 0;
    int venceu = 0;

    while (!venceu) {
        exibirMenuPrincipal();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            printf("Opção inválida.\n");
            continue;
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                exibirMapa(mapa);
                break;
            case 2:
                exibirMissao(id_missao);
                break;
            case 3:
                faseDeAtaque(mapa);
                break;
            case 4:
                if (verificarVitoria(mapa, id_missao)) {
                    printf("Parabéns! Você cumpriu a missão %d.\n", id_missao);
                    venceu = 1;
                } else {
                    printf("Missão %d ainda não cumprida.\n", id_missao);
                }
                break;
            case 5:
                printf("Saindo do jogo...\n");
                vencer:
                liberarMemoria(mapa);
                return 0;
            default:
                printf("Opção inválida.\n");
                break;
        }

        if (verificarVitoria(mapa, id_missao)) {
            printf("Parabéns! Você cumpriu a missão %d.\n", id_missao);
            break;
        }
    }

    liberarMemoria(mapa);
    return 0;
}


struct Territorio* alocarMapa(void) {
    struct Territorio* mapa = (struct Territorio*)calloc(MAX_TERRITORIO, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa.\n");
        exit(1);
    }
    return mapa;
}

void inicializarTerritorios(struct Territorio* mapa){
    printf("====================================\n");
    printf("Vamos Cadastrar os %d Territórios\n", MAX_TERRITORIO);
    for (int i = 0; i < MAX_TERRITORIO; i++) {
        printf("---- Cadastrando Território %d ---\n", i + 1);
        printf("Digite o nome do território %d: ", i + 1);
        if (fgets(mapa[i].nome, TAM_STRING, stdin) == NULL) mapa[i].nome[0] = '\0';
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Digite a cor do exército do território %d: ", i + 1);
        if (fgets(mapa[i].cor_exercito, TAM_STRING, stdin) == NULL) mapa[i].cor_exercito[0] = '\0';
        mapa[i].cor_exercito[strcspn(mapa[i].cor_exercito, "\n")] = 0;

        do {
            printf("Digite a quantidade de tropas do território %d (>=1): ", i + 1);
            if (scanf("%d", &mapa[i].qntd_tropas) != 1) {
                limparBufferEntrada();
                mapa[i].qntd_tropas = 0;
            } else {
                limparBufferEntrada();
            }
        } while (mapa[i].qntd_tropas < 1);
    }
}
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).

void liberarMemoria(struct Territorio* mapa){
    free(mapa);
}
// Libera a memória previamente alocada para o mapa usando free.

void exibirMenuPrincipal(){
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1. Exibir Mapa\n");
    printf("2. Exibir Missão\n");
    printf("3. Fase de Ataque\n");
    printf("4. Verificar Vitória\n");
    printf("5. Sair do Jogo\n");
    printf("==========================\n");
}
// Imprime na tela o menu de ações disponíveis para o jogador.

void exibirMapa(const struct Territorio* mapa){
    printf("\n===========================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("===========================\n");
    printf("%-3s %-20s %-20s %-8s\n", "ID", "TERRITÓRIO", "COR DO EXÉRCITO", "TROPAS");
    for (int i = 0; i < MAX_TERRITORIO; i++) {
        printf("%-3d %-20s %-20s %-8d\n", i, mapa[i].nome, mapa[i].cor_exercito, mapa[i].qntd_tropas);
    }
}

// Mostra o estado atual de todos os territórios no mapa.

void exibirMissao(int id_missao){
    printf("\n===== MISSÃO ATUAL =====\n");
    printf("Missão ID: %d\n", id_missao);

    switch (id_missao) {
        case 1:
            printf("Destruir o exército vermelho.\n");
            break;
        case 2:
            printf("Conquistar 3 territórios.\n");
            break;
        case 3:
            printf("Destruir o exército azul.\n");
            break;
        case 4:
            printf("Conquistar 4 territórios.\n");
            break;
        default:
            printf("Missão desconhecida.\n");
            break;
    }
    printf("=========================\n");
}
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

void faseDeAtaque(struct Territorio* mapa){
    int territorio_atacante = -1, territorio_defensor = -1;
    printf("\n===== FASE DE ATAQUE =====\n");
    exibirMapa(mapa);
    printf("Escolha o território atacante (0-%d): ", MAX_TERRITORIO - 1);
    if (scanf("%d", &territorio_atacante) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); return; }
    printf("Escolha o território defensor (0-%d): ", MAX_TERRITORIO - 1);
    if (scanf("%d", &territorio_defensor) != 1) { limparBufferEntrada(); printf("Entrada inválida.\n"); return; }
    limparBufferEntrada();

    if (territorio_atacante < 0 || territorio_atacante >= MAX_TERRITORIO ||
        territorio_defensor < 0 || territorio_defensor >= MAX_TERRITORIO) {
        printf("Território inválido.\n");
        return;
    }
    if (territorio_atacante == territorio_defensor) {
        printf("Atacante e defensor devem ser territórios diferentes.\n");
        return;
    }
    if (mapa[territorio_atacante].qntd_tropas < 2) {
        printf("Território atacante precisa ter pelo menos 2 tropas para atacar.\n");
        return;
    }

    simularAtaque(mapa, territorio_atacante, territorio_defensor);
}
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.

static int cmp_desc(const void* a, const void* b) {
    return (*(int*)b) - (*(int*)a);
}

void simularAtaque(struct Territorio* mapa, int territorio_atacante, int territorio_defensor){
    int tropas_atacante = mapa[territorio_atacante].qntd_tropas;
    int tropas_defensor = mapa[territorio_defensor].qntd_tropas;

    int dados_atacante = tropas_atacante > 3 ? 3 : tropas_atacante - 1;
    if (dados_atacante < 1) dados_atacante = 1;
    int dados_defensor = tropas_defensor >= 2 ? 2 : 1;

    int *ataque = malloc(dados_atacante * sizeof(int));
    int *defesa = malloc(dados_defensor * sizeof(int));

    for (int i = 0; i < dados_atacante; i++) ataque[i] = (rand() % 6) + 1;
    for (int i = 0; i < dados_defensor; i++) defesa[i] = (rand() % 6) + 1;

    qsort(ataque, dados_atacante, sizeof(int), cmp_desc);
    qsort(defesa, dados_defensor, sizeof(int), cmp_desc);

    int comparacoes = dados_atacante < dados_defensor ? dados_atacante : dados_defensor;
    int perdas_atk = 0, perdas_def = 0;

    for (int i = 0; i < comparacoes; i++) {
        if (ataque[i] > defesa[i]) {
            perdas_def++;
        } else {
            perdas_atk++;
        }
    }

    mapa[territorio_atacante].qntd_tropas -= perdas_atk;
    mapa[territorio_defensor].qntd_tropas -= perdas_def;

    printf("Resultado do combate: atacante perdeu %d, defensor perdeu %d\n", perdas_atk, perdas_def);

    if (mapa[territorio_defensor].qntd_tropas <= 0) {
        printf("Território %s conquistado por %s!\n", mapa[territorio_defensor].nome, mapa[territorio_atacante].cor_exercito);
        // Move uma tropa do atacante para o defensor (mínimo 1)
        mapa[territorio_defensor].qntd_tropas = 1;
        mapa[territorio_atacante].qntd_tropas -= 1;
        // Atualiza cor do exército do território conquistado
        strncpy(mapa[territorio_defensor].cor_exercito, mapa[territorio_atacante].cor_exercito, TAM_STRING - 1);
        mapa[territorio_defensor].cor_exercito[TAM_STRING - 1] = '\0';
    }
    
    free(ataque);
    free(defesa);
}
// Executa a lógica de uma batalha entre dois territórios.

int sortearMissao(void){
    int id_missao = (rand() % 4) + 1; // Gera um número aleatório entre 1 e 4
    return id_missao;
}
// Sorteia e retorna um ID de missão aleatório para o jogador.

int verificarVitoria(const struct Territorio* mapa, int id_missao){
    if (id_missao == 1) { // Destruir exército vermelho
        for (int i = 0; i < MAX_TERRITORIO; i++) {
            if (strcmp(mapa[i].cor_exercito, "vermelho") == 0 || strcmp(mapa[i].cor_exercito, "Vermelho") == 0) {
                return 0;
            }
        }
        return 1;
    } else if (id_missao == 3) { // Destruir exército azul
        for (int i = 0; i < MAX_TERRITORIO; i++) {
            if (strcmp(mapa[i].cor_exercito, "azul") == 0 || strcmp(mapa[i].cor_exercito, "Azul") == 0) {
                return 0;
            }
        }
        return 1;
    } else if (id_missao == 2) { // Conquistar 3 territórios
        // Conta territórios do jogador — aqui assumimos que jogador é dono de cor na posição 0 (exemplo)
        const char* minha_cor = mapa[0].cor_exercito;
        int count = 0;
        for (int i = 0; i < MAX_TERRITORIO; i++) if (strcmp(mapa[i].cor_exercito, minha_cor) == 0) count++;
        return count >= 3;
    } else if (id_missao == 4) { // Conquistar 4 territórios
        const char* minha_cor = mapa[0].cor_exercito;
        int count = 0;
        for (int i = 0; i < MAX_TERRITORIO; i++) if (strcmp(mapa[i].cor_exercito, minha_cor) == 0) count++;
        return count >= 4;
    }
    return 0;
}
// Verifica se o jogador cumpriu os requisitos de sua missão atual.

void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Função utilitária para limpar o buffer de entrada do teclado (stdin).