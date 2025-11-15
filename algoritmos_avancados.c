#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma sala
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Protótipos das funções
Sala* criarSala(const char* nome);
void conectarSalas(Sala* pai, Sala* esquerda, Sala* direita);
void explorarSalas(Sala* salaAtual);
void liberarArvore(Sala* raiz);

int main() {
    printf("🕵️ Detective Quest - Nível Novato\n");
    printf("=== Exploração da Mansão Misteriosa ===\n\n");
    
    // 🌱 Criando todas as salas da mansão
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* salaJantar = criarSala("Sala de Jantar");
    Sala* escritorio = criarSala("Escritório Secreto");
    Sala* cozinha = criarSala("Cozinha");
    Sala* jardimInverno = criarSala("Jardim de Inverno");
    Sala* sotao = criarSala("Sótão Assombrado");
    Sala* porao = criarSala("Porão Escuro");
    
    // 🔗 Conectando as salas para formar a árvore binária
    // Estrutura da árvore:
    //              Hall de Entrada
    //             /              \
    //     Biblioteca          Sala de Jantar
    //    /          \        /           \
    // Escritório  Sótão  Cozinha     Jardim de Inverno
    //                          \
    //                         Porão
    
    conectarSalas(hallEntrada, biblioteca, salaJantar);
    conectarSalas(biblioteca, escritorio, sotao);
    conectarSalas(salaJantar, cozinha, jardimInverno);
    conectarSalas(cozinha, NULL, porao);  // Porão só acessível através da cozinha
    
    // 🎮 Iniciando a exploração a partir do Hall de Entrada
    explorarSalas(hallEntrada);
    
    // 🧹 Liberando a memória alocada para a árvore
    liberarArvore(hallEntrada);
    
    printf("\n=== Fim da Investigação ===\n");
    return 0;
}

// Cria uma nova sala com o nome especificado
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro: Não foi possível alocar memória para a sala!\n");
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// Conecta salas filhas à sala pai
void conectarSalas(Sala* pai, Sala* esquerda, Sala* direita) {
    pai->esquerda = esquerda;
    pai->direita = direita;
}

// Função principal de exploração da mansão
void explorarSalas(Sala* salaAtual) {
    char opcao;
    
    while (salaAtual != NULL) {
        printf("\n📍 Você está na: %s\n", salaAtual->nome);
        
        // Verifica se é uma sala folha (sem saídas)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("🚫 Esta é uma sala sem saída. Fim do caminho!\n");
            printf("Voltando para o caminho anterior...\n");
            return;
        }
        
        // Mostra opções disponíveis
        printf("\nPara onde deseja ir?\n");
        if (salaAtual->esquerda != NULL) {
            printf("(e) Esquerda → %s\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("(d) Direita → %s\n", salaAtual->direita->nome);
        }
        printf("(s) Sair da exploração\n");
        
        printf("\nEscolha: ");
        scanf(" %c", &opcao);
        
        switch(opcao) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("❌ Não há passagem à esquerda!\n");
                }
                break;
                
            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("❌ Não há passagem à direita!\n");
                }
                break;
                
            case 's':
            case 'S':
                printf("👋 Saindo da exploração...\n");
                return;
                
            default:
                printf("❌ Opção inválida! Use 'e', 'd' ou 's'.\n");
        }
    }
}

// Libera a memória alocada para a árvore (pós-order)
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}
