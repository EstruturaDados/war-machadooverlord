#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[5];
    int i;
    
    printf("=== BEM-VINDO AO WAR ===\n\n");
    printf("=== Machado Overlord - Luciano ===\n\n");
    printf("Vamos cadastrar 5 territorios para comecar o jogo!\n\n");
    
    for (i = 0; i < 5; i++) {
        printf("--- Territorio %d ---\n", i + 1);
        
        printf("Digite o nome do territorio: ");
        scanf("%s", mapa[i].nome);
        
        printf("Digite a cor do exercito: ");
        scanf("%s", mapa[i].cor);
        
        printf("Digite o numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("\n");
    }
    
    printf("\n== ! ==\n");
    printf("MAPA DOS TERRITORIOS CADASTRADOS\n");
    printf("== ! ==\n\n");
    
    printf("%-20s %-12s %s\n", "TERRITORIO", "EXERCITO", "TROPAS");
    printf("-- ! --\n");
    
    for (i = 0; i < 5; i++) {
        printf("%-20s %-12s %d\n", 
               mapa[i].nome, 
               mapa[i].cor, 
               mapa[i].tropas);
    }
    
    printf("\n== ! ==\n");
    printf("Cadastro concluido!\n");
    
    return 0;
}