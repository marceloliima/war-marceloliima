#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =====================================================
// CONSTANTES DO SISTEMA
// =====================================================
#define MAX_TERRITORIOS 5
#define TAM_STRING 50

// =====================================================
// STRUCT TERRITORIO
// Representa cada território do jogo
// =====================================================
struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// =====================================================
// FUNÇÃO PARA LIMPAR BUFFER
// =====================================================
void limparBufferEntrada() {

    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

// =====================================================
// FUNÇÃO PARA PAUSAR O SISTEMA
// =====================================================
void pausarSistema() {

    printf("\nPressione ENTER para continuar...");
    getchar();
}

// =====================================================
// FUNÇÃO PARA EXIBIR MENU
// =====================================================
void mostrarMenu() {

    printf("\n=================================================\n");
    printf("             WAR - NIVEL AVENTUREIRO\n");
    printf("=================================================\n");

    printf("1 - Cadastrar territorios\n");
    printf("2 - Listar territorios\n");
    printf("3 - Simular batalha\n");
    printf("4 - Reforcar tropas\n");
    printf("5 - Buscar territorio\n");
    printf("0 - Sair\n");

    printf("-------------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// =====================================================
// FUNÇÃO DE CADASTRO
// =====================================================
void cadastrarTerritorios(
    struct Territorio *territorios,
    int totalTerritorios
) {

    printf("\n========== CADASTRO DE TERRITORIOS ==========\n");

    for (int i = 0; i < totalTerritorios; i++) {

        printf("\nTerritorio %d\n", i + 1);

        // Nome
        printf("Nome do territorio: ");

        fgets(
            territorios[i].nome,
            TAM_STRING,
            stdin
        );

        territorios[i].nome[
            strcspn(territorios[i].nome, "\n")
        ] = '\0';

        // Cor
        printf("Cor do exercito: ");

        fgets(
            territorios[i].cor,
            TAM_STRING,
            stdin
        );

        territorios[i].cor[
            strcspn(territorios[i].cor, "\n")
        ] = '\0';

        // Tropas
        printf("Quantidade de tropas: ");

        while (
            scanf("%d", &territorios[i].tropas) != 1 ||
            territorios[i].tropas <= 0
        ) {

            printf("Valor invalido! Digite novamente: ");

            limparBufferEntrada();
        }

        limparBufferEntrada();

        printf("Territorio cadastrado com sucesso!\n");
    }
}

// =====================================================
// FUNÇÃO PARA LISTAR TERRITÓRIOS
// =====================================================
void listarTerritorios(
    const struct Territorio *territorios,
    int totalTerritorios
) {

    printf("\n============== MAPA ATUAL ==============\n");

    for (int i = 0; i < totalTerritorios; i++) {

        printf("\n----------------------------------------\n");

        printf("ID: %d\n", i + 1);

        printf("Territorio : %s\n", territorios[i].nome);

        printf("Exercito   : %s\n", territorios[i].cor);

        printf("Tropas     : %d\n", territorios[i].tropas);
    }

    printf("\n----------------------------------------\n");
}

// =====================================================
// FUNÇÃO DE REFORÇO DE TROPAS
// =====================================================
void reforcarTropas(
    struct Territorio *territorios,
    int totalTerritorios
) {

    int id;
    int reforco;

    listarTerritorios(territorios, totalTerritorios);

    printf("\nDigite o ID do territorio: ");

    scanf("%d", &id);

    limparBufferEntrada();

    if (id < 1 || id > totalTerritorios) {

        printf("Territorio invalido!\n");

        return;
    }

    printf("Quantidade de tropas adicionais: ");

    scanf("%d", &reforco);

    limparBufferEntrada();

    if (reforco <= 0) {

        printf("Quantidade invalida!\n");

        return;
    }

    territorios[id - 1].tropas += reforco;

    printf(
        "\n%s recebeu %d tropas!\n",
        territorios[id - 1].nome,
        reforco
    );
}

// =====================================================
// FUNÇÃO PARA BUSCAR TERRITÓRIO
// =====================================================
void buscarTerritorio(
    const struct Territorio *territorios,
    int totalTerritorios
) {

    char busca[TAM_STRING];
    int encontrado = 0;

    printf("\nDigite o nome do territorio: ");

    fgets(busca, TAM_STRING, stdin);

    busca[strcspn(busca, "\n")] = '\0';

    printf("\n========== RESULTADO ==========\n");

    for (int i = 0; i < totalTerritorios; i++) {

        if (strcmp(busca, territorios[i].nome) == 0) {

            printf("\nTerritorio encontrado!\n");

            printf("Nome     : %s\n", territorios[i].nome);

            printf("Exercito : %s\n", territorios[i].cor);

            printf("Tropas   : %d\n", territorios[i].tropas);

            encontrado = 1;
        }
    }

    if (!encontrado) {

        printf("\nTerritorio nao encontrado.\n");
    }
}

// =====================================================
// FUNÇÃO DE BATALHA
// =====================================================
void simularBatalha(
    struct Territorio *territorios,
    int totalTerritorios
) {

    int atacante;
    int defensor;

    int dadoAtaque;
    int dadoDefesa;

    listarTerritorios(territorios, totalTerritorios);

    printf("\n========== SIMULADOR DE BATALHA ==========\n");

    printf("Escolha o territorio atacante (ID): ");

    scanf("%d", &atacante);

    limparBufferEntrada();

    printf("Escolha o territorio defensor (ID): ");

    scanf("%d", &defensor);

    limparBufferEntrada();

    // Validações
    if (
        atacante < 1 ||
        atacante > totalTerritorios ||
        defensor < 1 ||
        defensor > totalTerritorios
    ) {

        printf("\nID invalido!\n");

        return;
    }

    if (atacante == defensor) {

        printf("\nUm territorio nao pode atacar ele mesmo!\n");

        return;
    }

    if (territorios[atacante - 1].tropas <= 1) {

        printf(
            "\nO territorio atacante precisa ter mais de 1 tropa!\n"
        );

        return;
    }

    // Sorteio dos dados
    dadoAtaque = rand() % 6 + 1;
    dadoDefesa = rand() % 6 + 1;

    printf("\n=========== RESULTADO DA BATALHA ===========\n");

    printf(
        "\n%s atacou %s\n",
        territorios[atacante - 1].nome,
        territorios[defensor - 1].nome
    );

    printf(
        "\nDado ataque : %d",
        dadoAtaque
    );

    printf(
        "\nDado defesa : %d\n",
        dadoDefesa
    );

    // Regra do jogo
    if (dadoAtaque >= dadoDefesa) {

        printf("\nO atacante venceu a batalha!\n");

        territorios[defensor - 1].tropas--;

        // Conquista
        if (territorios[defensor - 1].tropas <= 0) {

            printf(
                "\n%s conquistou %s!\n",
                territorios[atacante - 1].nome,
                territorios[defensor - 1].nome
            );

            strcpy(
                territorios[defensor - 1].cor,
                territorios[atacante - 1].cor
            );

            territorios[defensor - 1].tropas = 1;
        }

    } else {

        printf("\nO defensor venceu a batalha!\n");

        territorios[atacante - 1].tropas--;
    }

    printf("\n========== MAPA ATUALIZADO ==========\n");

    listarTerritorios(territorios, totalTerritorios);
}

// =====================================================
// FUNÇÃO PRINCIPAL
// =====================================================
int main() {

    // Inicializa números aleatórios
    srand(time(NULL));

    // Alocação dinâmica
    struct Territorio *territorios;

    territorios = calloc(
        MAX_TERRITORIOS,
        sizeof(struct Territorio)
    );

    // Verificação da memória
    if (territorios == NULL) {

        printf("Erro ao alocar memoria!\n");

        return 1;
    }

    int opcao;

    // =================================================
    // LOOP PRINCIPAL
    // =================================================
    do {

        mostrarMenu();

        // Validação da opção
        if (scanf("%d", &opcao) != 1) {

            printf("\nEntrada invalida!\n");

            limparBufferEntrada();

            opcao = -1;

            continue;
        }

        limparBufferEntrada();

        switch (opcao) {

            // Cadastro
            case 1:

                cadastrarTerritorios(
                    territorios,
                    MAX_TERRITORIOS
                );

                pausarSistema();

                break;

            // Listagem
            case 2:

                listarTerritorios(
                    territorios,
                    MAX_TERRITORIOS
                );

                pausarSistema();

                break;

            // Batalha
            case 3:

                simularBatalha(
                    territorios,
                    MAX_TERRITORIOS
                );

                pausarSistema();

                break;

            // Reforço
            case 4:

                reforcarTropas(
                    territorios,
                    MAX_TERRITORIOS
                );

                pausarSistema();

                break;

            // Busca
            case 5:

                buscarTerritorio(
                    territorios,
                    MAX_TERRITORIOS
                );

                pausarSistema();

                break;

            // Sair
            case 0:

                printf("\nEncerrando sistema...\n");

                break;

            // Opção inválida
            default:

                printf("\nOpcao invalida!\n");

                pausarSistema();

                break;
        }

    } while (opcao != 0);

    // Liberação da memória
    free(territorios);

    return 0;
}
