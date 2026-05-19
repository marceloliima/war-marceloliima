#include <stdio.h>
#include <string.h>

// ===============================
// CONSTANTES DO PROGRAMA
// ===============================
#define MAX_TERRITORIOS 5
#define TAM_STRING 50

// ===============================
// STRUCT TERRITORIO
// Armazena os dados de cada território
// ===============================
struct Territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// ===============================
// FUNÇÃO PARA LIMPAR O BUFFER
// Remove caracteres restantes do teclado
// ===============================
void limparBufferEntrada() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

// ===============================
// FUNÇÃO PRINCIPAL
// ===============================
int main() {

    // Vetor de territórios
    struct Territorio territorios[MAX_TERRITORIOS];

    int totalTerritorios = 0;
    int opcao;

    // ===============================
    // MENU PRINCIPAL
    // ===============================
    do {

        printf("\n=====================================\n");
        printf("      SISTEMA WAR - TERRITORIOS\n");
        printf("=====================================\n");

        // Só mostra cadastro se ainda houver espaço
        if (totalTerritorios < MAX_TERRITORIOS) {
            printf("1 - Cadastrar territorios\n");
        }

        printf("2 - Listar territorios\n");
        printf("0 - Sair\n");

        printf("-------------------------------------\n");
        printf("Escolha uma opcao: ");

        // Validação da entrada numérica
        if (scanf("%d", &opcao) != 1) {

            printf("\nEntrada invalida!\n");

            limparBufferEntrada();

            opcao = -1;

            continue;
        }

        limparBufferEntrada();

        // ===============================
        // PROCESSAMENTO DAS OPÇÕES
        // ===============================
        switch (opcao) {

            // ===========================
            // CADASTRO DE TERRITÓRIOS
            // ===========================
            case 1:

                printf("\n===== CADASTRO DE TERRITORIOS =====\n");

                while (totalTerritorios < MAX_TERRITORIOS) {

                    printf("\nTerritorio %d\n", totalTerritorios + 1);

                    // -------------------
                    // Nome
                    // -------------------
                    printf("Digite o nome do territorio: ");

                    fgets(
                        territorios[totalTerritorios].nome,
                        TAM_STRING,
                        stdin
                    );

                    // Remove o ENTER do fgets
                    territorios[totalTerritorios]
                        .nome[strcspn(
                            territorios[totalTerritorios].nome,
                            "\n"
                        )] = '\0';

                    // -------------------
                    // Cor
                    // -------------------
                    printf("Digite a cor do exercito: ");

                    fgets(
                        territorios[totalTerritorios].cor,
                        TAM_STRING,
                        stdin
                    );

                    // Remove o ENTER do fgets
                    territorios[totalTerritorios]
                        .cor[strcspn(
                            territorios[totalTerritorios].cor,
                            "\n"
                        )] = '\0';

                    // -------------------
                    // Tropas
                    // -------------------
                    printf("Digite a quantidade de tropas: ");

                    while (scanf(
                        "%d",
                        &territorios[totalTerritorios].tropas
                    ) != 1) {

                        printf("Valor invalido! Digite um numero: ");

                        limparBufferEntrada();
                    }

                    limparBufferEntrada();

                    totalTerritorios++;

                    printf(
                        "Territorio cadastrado com sucesso!\n"
                    );

                    // Pergunta se deseja continuar
                    if (totalTerritorios < MAX_TERRITORIOS) {

                        char continuar;

                        printf(
                            "\nDeseja cadastrar outro territorio? (s/n): "
                        );

                        scanf("%c", &continuar);

                        limparBufferEntrada();

                        if (
                            continuar == 'n' ||
                            continuar == 'N'
                        ) {
                            break;
                        }
                    }
                }

                printf("\nPressione ENTER para continuar...");
                getchar();

                break;

            // ===========================
            // LISTAGEM DOS TERRITÓRIOS
            // ===========================
            case 2:

                printf("\n===== MAPA DE TERRITORIOS =====\n");

                if (totalTerritorios == 0) {

                    printf(
                        "\nNenhum territorio cadastrado.\n"
                    );

                } else {

                    for (
                        int i = 0;
                        i < totalTerritorios;
                        i++
                    ) {

                        printf("\n---------------------------------\n");

                        printf(
                            "Territorio %d\n",
                            i + 1
                        );

                        printf(
                            "Nome   : %s\n",
                            territorios[i].nome
                        );

                        printf(
                            "Cor    : %s\n",
                            territorios[i].cor
                        );

                        printf(
                            "Tropas : %d\n",
                            territorios[i].tropas
                        );
                    }

                    printf("\n---------------------------------\n");
                }

                printf("\nPressione ENTER para continuar...");
                getchar();

                break;

            // ===========================
            // SAIR
            // ===========================
            case 0:

                printf("\nEncerrando o sistema...\n");

                break;

            // ===========================
            // OPÇÃO INVÁLIDA
            // ===========================
            default:

                printf("\nOpcao invalida!\n");

                printf("\nPressione ENTER para continuar...");
                getchar();

                break;
        }

    } while (opcao != 0);

    return 0;
}
