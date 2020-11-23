#include <stdio.h>
#include <stdlib.h>

char jogo[3][3]; // matriz do jogo
char jogador1[50], jogador2[50]; // nome dos jogadores

void inicializarMatriz() { // matriz
    int i,j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            jogo[i][j] = ' ';
        }
    }
}
int eValido(char letra) { // validar os marcadores
    if(letra == 'x' || letra == '0')
        return 1;
    else
        return 0;
}
int coordenadaEhValida(int x, int y) { // validar as posições
    if(x >= 0 && x < 3) {
        if(y >= 0 && y < 3)
            return 1;
    }
    return 0;
}
int posicaVazia(int x, int y) {
    if(jogo[x][y] != 'x' && jogo[x][y] != '0')
        return 1;
    return 0;
}
int ganhouLinhas() { // validar linha completa ganhadora
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(jogo[i][j]) && jogo[i][j] == jogo[i][j+1])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}
int ganhouColunas() { // validar coluna completa ganhadora
    int i, j, igual = 1;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(eValido(jogo[j][i]) && jogo[j][i] == jogo[j+1][i])
                igual++;
        }
        if(igual == 3)
            return 1;
        igual = 1;
    }
    return 0;
}
int ganhoudiagPrincipal() { // validar diagonal completa ganhadora
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(jogo[i][i]) && jogo[i][i] == jogo[i+1][i+1])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}
int ganhoudiagSecundaria() { // validar diagonal completa ganhadora
    int i, igual = 1;
    for(i = 0; i < 2; i++) {
        if(eValido(jogo[i][3-i-1]) && jogo[i][3-i-1] == jogo[i+1][3-i-2])
            igual++;
    }
    if(igual == 3)
        return 1;
    else
        return 0;
}
void imprimir() { // matriz desenhada
    int lin, col;
    printf("\n\t    0  1  2\n");
    for(lin = 0; lin < 3; lin++) {
        printf("\t%d ", lin);
        for(col = 0; col < 3; col++) {
            if(col < 2)
                printf(" %c |", jogo[lin][col]);
            else
                printf(" %c ", jogo[lin][col]);
        }
        if(lin < 2)
            printf("\n\t   ---------\n");
    }
}
void jogar() {
    int x, y, valida, jogadas = 0, ganhou = 0, ordem = 1;
    do {
        do {
            imprimir();
            printf("\nDigite a coordenada que deseja jogar (linha - ) espaco (coluna | ): ");
            scanf("%d%d", &x, &y);
            valida = coordenadaEhValida(x, y);
            if(valida == 1)
                valida += posicaVazia(x, y);
        } while(valida != 2);
        if(ordem == 1)
            jogo[x][y] = 'x';
        else
            jogo[x][y] = '0';
        jogadas++;
        ordem++;
        if(ordem == 3)
            ordem = 1;
        ganhou += ganhouLinhas();
        ganhou += ganhouColunas();
        ganhou += ganhoudiagPrincipal();
        ganhou += ganhoudiagSecundaria();
    } while(ganhou == 0 && jogadas < 9);
    if(ganhou != 0) {
        imprimir();
        if(ordem - 1 == 1)
            printf("\nParabens. Voce venceu %s\n", jogador1);
        else
            printf("\nParabens. Voce venceu %s\n", jogador2);
    } else
        printf("\nQue feio. Ninguem venceu!\n\n");
}
int main() {
    int op;
    printf ("Regras do jogo\n");
	printf ("O tabuleiro e uma matriz de tres linhas por tres colunas.\n");
	printf ("Dois jogadores escolhem uma marcacao cada um, um circulo (O) e um xis (X).\n");
	printf ("Os jogadores jogam alternadamente, uma marcacao por vez, numa lacuna que esteja vazia.\n"); 
	printf ("Quando um jogador conquista o objetivo, costuma-se riscar os tres simbolos.\n\n");
    printf ("Para iniciar digite (nome do primeiro jogar) enter (nome do segundo jogador)\n");
	printf("Jogador 1 digite seu nome: ");
    fgets (jogador1, 50, stdin);
    printf ("Jogador 2 digite seu nome: ");
    fgets (jogador2, 50, stdin);

    do {
        inicializarMatriz();
        jogar();
        printf("Deseja jogar novamente?\n1 - Sim\n2 - Nao\n");
        scanf("%d", &op);
    } while(op == 1);
    return 0;
}
