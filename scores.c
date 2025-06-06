#include <stdio.h>
#include "scores.h"

// Definim aici variabilele globale
int scoreX = 0;
int scoreO = 0;
int draws = 0;

//functia carea actualizeaza scorurile in functie de jucator
void updateScore(char winner) {
    if (winner == 'X') {
        scoreX++;
    } else if (winner == 'O') {
        scoreO++;
    } else if (winner == 'D') { // remiză
        draws++;
    }
}

// functia care resetează scorurile la 0
void resetScores() {
    scoreX = 0;
    scoreO = 0;
    draws = 0;
}

// functia care salv in scores.txt
void saveScores() {
    FILE *file = fopen("scores.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d %d %d\n", scoreX, scoreO, draws);
        fclose(file);
    }
}
void loadScores() {
    FILE *file = fopen("scores.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d %d %d", &scoreX, &scoreO, &draws);
        fclose(file);
    }
}
