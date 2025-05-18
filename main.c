#include <ncurses.h>
#include "game.h"
#include "interface.h"
#include "scores.h"
#include"ai.h"
//#include<stdbool>

extern bool gameOver;
extern char currentPlayer;

int main() {
  int mode=0; //1=PVSP SI 2=PVSAI
  printf("Select game mode:\n");
  printf("1. Player vs Player\n");
  printf("2. Player vs AI\n");
  printf("Enter choice: ");
  scanf("%d", &mode);
  initInterface();   // Initializeaza ncurses
  initGame();        // InitializeazA tabla de joc
  loadScores();
   while (!gameOver) { // Cat timp jocul nu s a terminat
     clear();
     drawGameScreen();         // Deseneaza tabla
     int ch = getch();         // Citeste o tastă
     handleInput(ch, mode);          // trimite modul de joc si muta caracterul

     char winner = checkWinner();   // Verifica dacă cineva a castigat
     if (winner != ' ') { // Daca cineva a win  sau e remiza
       clear();
       drawGameScreen();

       if (winner == 'X' || winner == 'O') {
         mvprintw(8, 0, "Jucatorul %c a castigat!", winner);
       } else {
         mvprintw(8, 0, "Egalitate!");
       }
       refresh();
       updateScore(winner);
       saveScores();
       getch();  // Asteapta apasarea unei taste
       break;
     }
   }
   endInterface();    // Închide ncurses
   return 0;
}
