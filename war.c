#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_TERRITORIO 2
#define TAM_STRING 100


struct Territorio
{
    char nome[TAM_STRING];
    char cor_exercito[TAM_STRING];
    int qntd_tropas;
};


int main() {
    struct Territorio mapa[MAX_TERRITORIO];

    printf("====================================\n");
    printf("\nVamos Cadastrar os 5 Territórios\n");
    for (int i = 0; i < MAX_TERRITORIO; i++) {
        printf("\n---- Cadastrando Território %d ---\n", i + 1);
        printf("Digite o nome do territorio %d: ", i + 1);
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; 

        printf("Digite a cor do exercito do territorio %d: ", i + 1);
        fgets(mapa[i].cor_exercito, TAM_STRING, stdin);
        mapa[i].cor_exercito[strcspn(mapa[i].cor_exercito, "\n")] = 0; 

        printf("Digite a quantidade de tropas do territorio %d: ", i + 1);
        scanf("%d", &mapa[i].qntd_tropas);
        getchar(); 
    }

    // Exibir informações dos territórios
    printf("\n===========================\n");
    printf("\nMAPA DO MUNDO ESTADO ATUAL\n");
    printf("\n===========================\n");

    for (int i = 0; i < MAX_TERRITORIO; i++) {
        printf("\nTERRITÓRIO %d \n", i +1);
        printf("-Nome: %s\n", mapa[i].nome);
        printf("-Cor do Exercito: %s\n", mapa[i].cor_exercito);
        printf("-Quantidade de Tropas: %d\n", mapa[i].qntd_tropas);
    }

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
