#include<stdio.h>
#include <stdlib.h>
#include <time.h> // srand
#include "game.h" // verifica daca e pe modul de ai
extern char board[3][3]; // extern pentru ca aceasta variabila exista undeva, nu o declat aici, doar o anunt. extern se foloseste cand apare intr un fisier. c si vrei sa o folosesti intr un alt fisier .c nu in unul .h.
void aiMakeMove() {
    int options[9][2];
    int count = 0;
    //9 celule goale
    // fiecare pozitie are 2 coordonate. randul i si coloana j
    // Găsește toate celulele goale
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
	      options[count][0] = i; // randurile goale
	      options[count][1] = j;// coloanele goale
                count++;
            }

    // Dacă există celule goale, alege una aleator
    if (count > 0) {
        srand((unsigned int)time(NULL));
        int r = rand() % count;
        int row = options[r][0];
        int col = options[r][1];
        board[row][col] = 'O';  // AI joacă cu O
    }
}
