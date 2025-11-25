#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtaque, dadoDefesa;
    
    // sorteia os dados
    dadoAtaque = (rand() % 6) + 1;
    dadoDefesa = (rand() % 6) + 1;
    
    printf("\nDado do atacante: %d\n", dadoAtaque);
    printf("Dado do defensor: %d\n", dadoDefesa);
    
    // ve quem ganhou (empate favorece atacante)
    if (dadoAtaque >= dadoDefesa) {
        printf("Atacante ganhou!\n");
        defensor->tropas = defensor->tropas - 1;
        
        // se o defensor perdeu todas as tropas
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

// funcao para mostrar os territorios
void mostrarMapa(Territorio* mapa, int total) {
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

int main() {
    Territorio* mapa;
    int quantidade;
    int i;
    int continuar = 1;
    int opcao;
    int atk, def;
    
    srand(time(NULL));
    
    printf("=== BEM-VINDO AO WAR ===\n\n");
    printf("=== Machado Overlord - Luciano ===\n\n");
    
    printf("Quantos territorios? ");
    scanf("%d", &quantidade);
    
    // aloca a memoria
    mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));
    
    printf("\nVamos cadastrar!\n\n");
    
    // cadastra os territorios
    for (i = 0; i < quantidade; i++) {
        printf("Territorio %d\n", i + 1);
        
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        
        printf("Cor: ");
        scanf("%s", mapa[i].cor);
        
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("\n");
    }
    
    // loop do jogo
    while (continuar == 1) {
        mostrarMapa(mapa, quantidade);
        
        printf("O que fazer?\n");
        printf("1 - Atacar\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            printf("\nQual territorio vai atacar? ");
            scanf("%d", &atk);
            
            printf("Qual territorio vai ser atacado? ");
            scanf("%d", &def);
            
            // transforma em indice (comeca do 0)
            atk = atk - 1;
            def = def - 1;
            
            // verifica se e valido
            if (atk < 0 || atk >= quantidade || def < 0 || def >= quantidade) {
                printf("Numero invalido!\n");
                continue;
            }
            
            // nao pode atacar o proprio territorio
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
            
        } else if (opcao == 0) {
            continuar = 0;
        }
    }
    
    printf("\nAte mais!\n");
    
    // libera a memoria
    free(mapa);
    
    return 0;
}