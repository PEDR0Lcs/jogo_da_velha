#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Fun��o para exibir o tabuleiro
void exibirTabuleiro(char* tabuleiro) {
    printf("  0 1 2\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i);
        for (int j = 0; j < 3; j++) {
            printf("%c ", *(tabuleiro + i * 3 + j));
        }
        printf("\n");
    }
    printf("\n");
}

// Fun��o para verificar se algu�m ganhou
int verificarGanhador(char* tabuleiro, char jogador) {
    for (int i = 0; i < 3; i++) {
        if ((*(tabuleiro + i * 3) == jogador && *(tabuleiro + i * 3 + 1) == jogador && *(tabuleiro + i * 3 + 2) == jogador) ||
            (*(tabuleiro + i) == jogador && *(tabuleiro + i + 3) == jogador && *(tabuleiro + i + 6) == jogador)) {
            return 1; // Ganhou
        }
    }

    if ((*(tabuleiro) == jogador && *(tabuleiro + 4) == jogador && *(tabuleiro + 8) == jogador) ||
        (*(tabuleiro + 2) == jogador && *(tabuleiro + 4) == jogador && *(tabuleiro + 6) == jogador)) {
        return 1; // Ganhou
    }

    return 0; // N�o ganhou
}

// Fun��o para verificar se o tabuleiro est� cheio (empate)
int tabuleiroCheio(char* tabuleiro) {
    for (int i = 0; i < 9; i++) {
        if (*(tabuleiro + i) == ' ')
            return 0; // N�o est� cheio
    }
    return 1; // Est� cheio
}

int main() {
	setlocale(0, "Portuguese");
	
    char* tabuleiro = (char*)malloc(9 * sizeof(char));
    for (int i = 0; i < 9; i++) {
        *(tabuleiro + i) = ' ';
    }

    char jogadorAtual = 'X';

    while (1) {
        // Exibir tabuleiro
        exibirTabuleiro(tabuleiro);

        // Obter a jogada do jogador
        int linha, coluna;
        printf("Jogador %c, fa�a sua jogada (linha e coluna): ", jogadorAtual);
        scanf("%d %d", &linha, &coluna);

        // Verificar se a posi��o � v�lida
        if (linha < 0 || linha >= 3 || coluna < 0 || coluna >= 3 || *(tabuleiro + linha * 3 + coluna) != ' ') {
            printf("Jogada inv�lida. Tente novamente.\n");
            continue;
        }

        // Realizar a jogada
        *(tabuleiro + linha * 3 + coluna) = jogadorAtual;

        // Verificar se o jogador venceu
        if (verificarGanhador(tabuleiro, jogadorAtual)) {
            exibirTabuleiro(tabuleiro);
            printf("Parab�ns, jogador %c! Voc� venceu!\n", jogadorAtual);
            break;
        }

        // Verificar empate
        if (tabuleiroCheio(tabuleiro)) {
            exibirTabuleiro(tabuleiro);
            printf("Empate! O jogo acabou.\n");
            break;
        }

        // Trocar o jogador
        jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
    }

    free(tabuleiro); // Liberar a mem�ria alocada dinamicamente

    return 0;
}

