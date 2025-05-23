#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"game.h"
//variabilele globale/setupul initial.
char board[3][3];
char currentPlayer = 'X'; // tot timpul incepem cu x
bool gameOver = false; // initializam cu false, daca jocul NU s a terminat practcic e fals.
GameMode currentMode= MODE_NONE; // TREBUIE DEFINIT GLOBAL
void initGame() {
    currentPlayer = 'X';
    gameOver = false;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}
// i sunt randurile, 0,1,2 le initializeaza
// j sunt coloanele 0,1,2 le initializeaza
//board [0][0] pana la [2][2] sunt goale
// tot ce tine de desen su scris fac dupa ce aflu cum se foloseste sdl.
// okay, o sa am nevoie de un enum in care o sa scriu in ce mod e jocul pt a face functia de click.
void setGameMode(GameMode mode) {
    currentMode = mode;
}

char checkWinner() {
    // Verifica liniile din matrice
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            return board[i][0]; // castigator pe linie
        }
    }

    // Verifica toate coloanele
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != ' ' &&
            board[0][j] == board[1][j] &&
            board[1][j] == board[2][j]) {
            return board[0][j]; // castigator pe coloană
        }
    }

    // Verifica diagonala principala
    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        return board[0][0]; // win pt cn e pe diag principala
    }

    // Verifica diagonala 2
    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        return board[0][2]; // castiga cn e pe diagonala 2
    }

    // Niciun winner xoxo.
    return ' ';
}

