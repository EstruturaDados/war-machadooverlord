#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// funcao para sortear e dar uma missao
void atribuirMissao(char* destino, char* missoes[], int total) {
    int sorteio;
    sorteio = rand() % total;
    strcpy(destino, missoes[sorteio]);
}

// funcao para mostrar a missao
void exibirMissao(char* missao) {
    printf("\n=== SUA MISSAO ===\n");
    printf("%s\n", missao);
    printf("==================\n\n");
}

// funcao para verificar se cumpriu a missao
int verificarMissao(char* missao, Territorio* mapa, int total, char* corJogador) {
    int i;
    int contTerritorios = 0;
    int temVerde = 0;
    
    // conta quantos territorios o jogador tem
    for (i = 0; i < total; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            contTerritorios = contTerritorios + 1;
        }
        
        // verifica se ainda tem exercito verde
        if (strcmp(mapa[i].cor, "Verde") == 0) {
            temVerde = 1;
        }
    }
    
    // verifica qual e a missao
    if (strstr(missao, "Destruir o exercito Verde") != NULL) {
        if (temVerde == 0) {
            return 1; // missao cumprida
        }
    }
    
    if (strstr(missao, "Conquistar 3 territorios") != NULL) {
        if (contTerritorios >= 3) {
            return 1; // missao cumprida
        }
    }
    
    return 0; // missao nao cumprida
}

// funcao para atacar
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtaque, dadoDefesa;
    
    dadoAtaque = (rand() % 6) + 1;
    dadoDefesa = (rand() % 6) + 1;
    
    printf("\nDado do atacante: %d\n", dadoAtaque);
    printf("Dado do defensor: %d\n", dadoDefesa);
    
    // empate favorece atacante
    if (dadoAtaque >= dadoDefesa) {
        printf("Atacante ganhou!\n");
        defensor->tropas = defensor->tropas - 1;
        
        if (defensor->tropas == 0) {
            printf("Territorio conquistado!\n");
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            atacante->tropas = atacante->tropas - 1;
        }
    } else {
        printf("Defensor resistiu!\n");
        atacante->tropas = atacante->tropas - 1;
    }
}

// funcao para mostrar o mapa
void exibirMapa(Territorio* mapa, int total) {
    int i;
    
    printf("\n== ! ==\n");
    printf("MAPA DOS TERRITORIOS\n");
    printf("== ! ==\n\n");
    
    for (i = 0; i < total; i++) {
        printf("%d - %s (%s) - %d tropas\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

// funcao para inicializar os territorios automaticamente
void inicializarTerritorios(Territorio* mapa, int total) {
    char* nomes[] = {"Brasil", "Argentina", "Peru", "Chile", "Colombia"};
    char* cores[] = {"Azul", "Verde", "Vermelho", "Amarelo", "Verde"};
    int i;
    
    for (i = 0; i < total; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = (rand() % 3) + 2; // 2 a 4 tropas
    }
    
    // garante que o jogador comeca com o primeiro territorio
    strcpy(mapa[0].cor, "Azul");
}

// funcao para liberar memoria
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    Territorio* mapa;
    char* missao;
    char* missoes[5];
    int numTerritorios = 5;
    int opcao;
    int continuar = 1;
    int atk, def;
    char corJogador[10] = "Azul";
    
    srand(time(NULL));
    
    // define as missoes possiveis
    missoes[0] = "Destruir o exercito Verde";
    missoes[1] = "Conquistar 3 territorios";
    missoes[2] = "Destruir o exercito Verde";
    missoes[3] = "Conquistar 3 territorios";
    missoes[4] = "Conquistar 3 territorios";
    
    printf("=== BEM-VINDO AO WAR ===\n\n");
    printf("=== Machado Overlord - Luciano ===\n\n");
    
    // aloca memoria para os territorios
    mapa = (Territorio*) calloc(numTerritorios, sizeof(Territorio));
    
    // aloca memoria para a missao
    missao = (char*) malloc(100 * sizeof(char));
    
    // inicializa os territorios automaticamente
    inicializarTerritorios(mapa, numTerritorios);
    
    // sorteia uma missao
    atribuirMissao(missao, missoes, 5);
    
    printf("Voce comanda o exercito %s\n", corJogador);
    exibirMissao(missao);
    
    printf("Pressione ENTER para comecar...");
    getchar();
    
    // loop do jogo
    while (continuar == 1) {
        exibirMapa(mapa, numTerritorios);
        
        printf("== MENU ==\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            printf("\nQual territorio vai atacar? ");
            scanf("%d", &atk);
            
            printf("Qual territorio vai ser atacado? ");
            scanf("%d", &def);
            
            // transforma em indice
            atk = atk - 1;
            def = def - 1;
            
            // verifica se e valido
            if (atk < 0 || atk >= numTerritorios || def < 0 || def >= numTerritorios) {
                printf("Numero invalido!\n");
                continue;
            }
            
            // nao pode atacar seu territorio
            if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
                printf("Nao pode atacar seu territorio!\n");
                continue;
            }
            
            // precisa ter tropas
            if (mapa[atk].tropas < 2) {
                printf("Precisa ter pelo menos 2 tropas!\n");
                continue;
            }
            
            atacar(&mapa[atk], &mapa[def]);
            
        } else if (opcao == 2) {
            printf("\n--- VERIFICANDO MISSAO ---\n");
            
            if (verificarMissao(missao, mapa, numTerritorios, corJogador) == 1) {
                printf("\n*** PARABENS! VOCE VENCEU! ***\n");
                printf("Missao cumprida!\n");
                continuar = 0;
            } else {
                printf("Missao ainda nao cumprida. Continue jogando!\n");
            }
            
        } else if (opcao == 0) {
            continuar = 0;
        }
    }
    
    printf("\nAte logo!\n");
    
    // libera memoria
    liberarMemoria(mapa, missao);
    
    return 0;
}