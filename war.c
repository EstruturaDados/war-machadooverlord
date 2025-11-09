#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

//Constantes Globais
#define NUM_TERRITORIOS 42
#define NUM_MISSOES 6
#define MAX_STRING 50

//Estrutura de Dados
typedef struct {
    char nome[MAX_STRING];
    char corExercito[MAX_STRING];
    int numeroTropas;
} Territorio;

//Protótipos das Funções

//Funções de setup e gerenciamento de memória
Territorio* alocarMapa(void);
void inicializarTerritorios(Territorio* mapa);
void liberarMemoria(Territorio* mapa);

//Funções de interface com o usuário
void exibirMenuPrincipal(void);
void exibirMapa(const Territorio* mapa);
void exibirMissao(int missaoId);

//Funções de lógica principal do jogo
void faseDeAtaque(Territorio* mapa, const char* corJogador);
int simularAtaque(Territorio* mapa, int origem, int destino, const char* corJogador);
int sortearMissao(void);
int verificarVitoria(const Territorio* mapa, int missaoId, const char* corJogador);

//Função utilitária
void limparBufferEntrada(void);

//Função Principal (main)
int main() {
    //Setup
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand((unsigned int)time(NULL));
    
    Territorio* mapa = alocarMapa();
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
    inicializarTerritorios(mapa);
    
    char corJogador[MAX_STRING] = "Azul";
    int missaoId = sortearMissao();
    int opcao;
    int jogoAtivo = 1;
    
    printf("\n=== BEM-VINDO AO WAR ===\n");
    printf("Você comanda o exército %s\n", corJogador);
    printf("Pressione ENTER para começar...");
    getchar();
    
    //Game Loop
    do {
        printf("\n\n==================== ESTADO DO JOGO ====================\n\n");
        exibirMapa(mapa);
        printf("\n");
        exibirMissao(missaoId);
        exibirMenuPrincipal();
        
        printf("\nEscolha: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }
        limparBufferEntrada();
        
        switch (opcao) {
            case 1:
                printf("\n--- FASE DE ATAQUE ---\n");
                faseDeAtaque(mapa, corJogador);
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
                
            case 2:
                printf("\n--- VERIFICANDO VITÓRIA ---\n");
                if (verificarVitoria(mapa, missaoId, corJogador)) {
                    printf("\n*** PARABÉNS! VOCÊ VENCEU! ***\n");
                    printf("Missão cumprida com sucesso!\n");
                    jogoAtivo = 0;
                } else {
                    printf("Missão ainda não cumprida. Continue jogando!\n");
                }
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
                
            case 0:
                printf("\nEncerrando jogo...\n");
                jogoAtivo = 0;
                break;
                
            default:
                printf("Opção inválida!\n");
                break;
        }
        
    } while (jogoAtivo);
    
    //Limpeza
    liberarMemoria(mapa);
    
    return 0;
}

//Implementação das Funções

Territorio* alocarMapa(void) {
    return (Territorio*)calloc(NUM_TERRITORIOS, sizeof(Territorio));
}

void inicializarTerritorios(Territorio* mapa) {
    const char* nomes[NUM_TERRITORIOS] = {
        "Brasil", "Argentina", "Peru", "Venezuela", "Colombia", "Mexico",
        "California", "Nova York", "Alasca", "Vancouver", "Mackenzie", "Groenlandia",
        "Islandia", "Inglaterra", "Suecia", "Alemanha", "Franca", "Polonia",
        "Espanha", "Argelia", "Egito", "Sudao", "Congo", "Africa do Sul",
        "Madagascar", "Oriente Medio", "Aral", "Omsk", "Dudinka", "Siberia",
        "Tchita", "Mongolia", "Vladivostok", "China", "India", "Japao",
        "Vietna", "Borneu", "Sumatra", "Nova Guine", "Australia", "Perth"
    };
    
    const char* cores[NUM_TERRITORIOS] = {
        "Azul", "Verde", "Amarelo", "Verde", "Amarelo", "Vermelho",
        "Vermelho", "Vermelho", "Preto", "Preto", "Preto", "Branco",
        "Branco", "Branco", "Branco", "Roxo", "Roxo", "Roxo",
        "Roxo", "Rosa", "Rosa", "Rosa", "Rosa", "Rosa",
        "Rosa", "Laranja", "Laranja", "Laranja", "Laranja", "Laranja",
        "Marrom", "Marrom", "Marrom", "Marrom", "Marrom", "Cinza",
        "Cinza", "Cinza", "Cinza", "Cinza", "Cinza", "Cinza"
    };
    
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].corExercito, cores[i]);
        mapa[i].numeroTropas = (rand() % 4) + 2;
    }
    
    // Garante alguns territórios para o jogador
    for (int i = 0; i < 5; i++) {
        strcpy(mapa[i].corExercito, "Azul");
        mapa[i].numeroTropas = (rand() % 3) + 3;
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

void exibirMenuPrincipal(void) {
    printf("\n========== MENU ==========\n");
    printf("[1] Atacar\n");
    printf("[2] Verificar Vitória\n");
    printf("[0] Sair\n");
    printf("==========================\n");
}

void exibirMapa(const Territorio* mapa) {
    printf("%-4s %-20s %-12s %s\n", "ID", "Território", "Exército", "Tropas");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%-4d %-20s %-12s %d\n", 
               i, 
               mapa[i].nome, 
               mapa[i].corExercito, 
               mapa[i].numeroTropas);
    }
}

void exibirMissao(int missaoId) {
    printf("=== SUA MISSÃO ===\n");
    
    switch (missaoId) {
        case 0:
            printf("Destruir o exército VERMELHO\n");
            break;
        case 1:
            printf("Destruir o exército VERDE\n");
            break;
        case 2:
            printf("Destruir o exército AMARELO\n");
            break;
        case 3:
            printf("Conquistar 24 territórios\n");
            break;
        case 4:
            printf("Conquistar 18 territórios com 2+ tropas\n");
            break;
        case 5:
            printf("Conquistar 15 territórios\n");
            break;
    }
}

void faseDeAtaque(Territorio* mapa, const char* corJogador) {
    int origem, destino;
    
    printf("\nSeus territórios:\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(mapa[i].corExercito, corJogador) == 0) {
            printf("  [%d] %s (%d tropas)\n", i, mapa[i].nome, mapa[i].numeroTropas);
        }
    }
    
    printf("\nTerritório de origem: ");
    scanf("%d", &origem);
    limparBufferEntrada();
    
    printf("\nTerritórios inimigos:\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(mapa[i].corExercito, corJogador) != 0) {
            printf("  [%d] %s - %s (%d tropas)\n", 
                   i, mapa[i].nome, mapa[i].corExercito, mapa[i].numeroTropas);
        }
    }
    
    printf("\nTerritório de destino: ");
    scanf("%d", &destino);
    limparBufferEntrada();
    
    int resultado = simularAtaque(mapa, origem, destino, corJogador);
    
    if (resultado == 1) {
        printf("\nTerritório conquistado!\n");
    } else if (resultado == 0) {
        printf("\nAtaque repelido!\n");
    }
}

int simularAtaque(Territorio* mapa, int origem, int destino, const char* corJogador) {
    // Validações
    if (origem < 0 || origem >= NUM_TERRITORIOS || destino < 0 || destino >= NUM_TERRITORIOS) {
        printf("Erro: Território inválido!\n");
        return -1;
    }
    
    if (strcmp(mapa[origem].corExercito, corJogador) != 0) {
        printf("Erro: Território de origem não é seu!\n");
        return -1;
    }
    
    if (strcmp(mapa[destino].corExercito, corJogador) == 0) {
        printf("Erro: Não pode atacar seu próprio território!\n");
        return -1;
    }
    
    if (mapa[origem].numeroTropas < 2) {
        printf("Erro: Tropas insuficientes (mínimo 2)!\n");
        return -1;
    }
    
    // Simula combate com dados
    int dadosAtacante = mapa[origem].numeroTropas - 1;
    if (dadosAtacante > 3) dadosAtacante = 3;
    
    int dadosDefensor = mapa[destino].numeroTropas;
    if (dadosDefensor > 3) dadosDefensor = 3;
    
    int resultadoAtaque[3], resultadoDefesa[3];
    
    // Rola dados do atacante
    for (int i = 0; i < dadosAtacante; i++) {
        resultadoAtaque[i] = (rand() % 6) + 1;
    }
    
    // Rola dados do defensor
    for (int i = 0; i < dadosDefensor; i++) {
        resultadoDefesa[i] = (rand() % 6) + 1;
    }
    
    for (int i = 0; i < dadosAtacante - 1; i++) {
        for (int j = i + 1; j < dadosAtacante; j++) {
            if (resultadoAtaque[j] > resultadoAtaque[i]) {
                int temp = resultadoAtaque[i];
                resultadoAtaque[i] = resultadoAtaque[j];
                resultadoAtaque[j] = temp;
            }
        }
    }
    
    for (int i = 0; i < dadosDefensor - 1; i++) {
        for (int j = i + 1; j < dadosDefensor; j++) {
            if (resultadoDefesa[j] > resultadoDefesa[i]) {
                int temp = resultadoDefesa[i];
                resultadoDefesa[i] = resultadoDefesa[j];
                resultadoDefesa[j] = temp;
            }
        }
    }
    
    // Exibe resultados
    printf("\nDados do Atacante: ");
    for (int i = 0; i < dadosAtacante; i++) {
        printf("%d ", resultadoAtaque[i]);
    }
    
    printf("\nDados do Defensor: ");
    for (int i = 0; i < dadosDefensor; i++) {
        printf("%d ", resultadoDefesa[i]);
    }
    printf("\n");
    
    // Compara resultados
    int perdasAtacante = 0, perdasDefensor = 0;
    int comparacoes = (dadosAtacante < dadosDefensor) ? dadosAtacante : dadosDefensor;
    
    for (int i = 0; i < comparacoes; i++) {
        if (resultadoAtaque[i] > resultadoDefesa[i]) {
            perdasDefensor++;
        } else {
            perdasAtacante++;
        }
    }
    
    printf("Atacante perde: %d tropa(s)\n", perdasAtacante);
    printf("Defensor perde: %d tropa(s)\n", perdasDefensor);
    
    mapa[origem].numeroTropas -= perdasAtacante;
    mapa[destino].numeroTropas -= perdasDefensor;
    
    // Verifica conquista
    if (mapa[destino].numeroTropas <= 0) {
        strcpy(mapa[destino].corExercito, corJogador);
        mapa[destino].numeroTropas = 1;
        mapa[origem].numeroTropas--;
        return 1;
    }
    
    return 0;
}

int sortearMissao(void) {
    return rand() % NUM_MISSOES;
}

int verificarVitoria(const Territorio* mapa, int missaoId, const char* corJogador) {
    int territoriosJogador = 0;
    int territoriosAlvo = 0;
    int territoriosCom2Tropas = 0;
    
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(mapa[i].corExercito, corJogador) == 0) {
            territoriosJogador++;
            if (mapa[i].numeroTropas >= 2) {
                territoriosCom2Tropas++;
            }
        }
    }
    
    switch (missaoId) {
        case 0:
            for (int i = 0; i < NUM_TERRITORIOS; i++) {
                if (strcmp(mapa[i].corExercito, "Vermelho") == 0) {
                    territoriosAlvo++;
                }
            }
            return (territoriosAlvo == 0);
            
        case 1:
            for (int i = 0; i < NUM_TERRITORIOS; i++) {
                if (strcmp(mapa[i].corExercito, "Verde") == 0) {
                    territoriosAlvo++;
                }
            }
            return (territoriosAlvo == 0);
            
        case 2:
            for (int i = 0; i < NUM_TERRITORIOS; i++) {
                if (strcmp(mapa[i].corExercito, "Amarelo") == 0) {
                    territoriosAlvo++;
                }
            }
            return (territoriosAlvo == 0);
            
        case 3:
            return (territoriosJogador >= 24);
            
        case 4:
            return (territoriosCom2Tropas >= 18);
            
        case 5:
            return (territoriosJogador >= 15);
    }
    
    return 0;
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}