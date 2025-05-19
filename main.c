#include <ncurses.h>
#include <stdio.h>
#include "game.h"
#include "interface.h"
#include "scores.h"
#include "ai.h"

//#include<stdbool>
extern bool gameOver; //accesam o functie deja existenta, nu o mai declaram odata pentru ca exista intr un alt fisier. extern spune ca deja exista intr un alt loc
extern char currentPlayer;

int main() {
  int mode = 0; //1=PVSP SI 2=PVSAI

  // alegerea modului de joc la început, asta e practic doar afisarea meniului nu si implementarea sa, implementarea e in interface.c
  printf("Select game mode:\n");
  printf("1. Player vs Player\n");
  printf("2. Player vs AI\n");
  printf("Enter choice: ");
  scanf("%d", &mode); //citeste modul introdus

  initInterface();   // Initializeaza ncurses
  loadScores();      // Încarcă scorurile din fișier

  int running = 1; //valoarea 1 inseamna da, adica ruleaza jocul
  while (running) {
    initGame();        // InitializeazA tabla de joc
    gameOver = false; //daca un singur meci s a incheiata

    // bucla principală pentru un meci
    while (!gameOver) { // Cat timp jocul nu s a terminat
      clear();
      drawGameScreen();         // Deseneaza tabla
      int ch = getch();         // Citeste o tastă
      handleInput(ch, mode);    // trimite modul de joc si muta caracterul

      char winner = checkWinner();   // Verifica dacă cineva a castigat
      if (winner != ' ') { // Daca cineva a win
        clear();
        drawGameScreen();

        if (winner == 'X' || winner == 'O') {
          mvprintw(8, 0, "Jucatorul %c a castigat!\n", winner);
        }
	else {
          mvprintw(8, 0, "Egalitate!\n"); //mvprintw este una din functiile ncurses care se refera la move cursor print window
        }

        refresh(); // functie ncurses care actualizeaza ecranul cu toate modificarile pe care le ai facut in memorie
        updateScore(winner == ' ' ? 'D' : winner); // update scor; D de la draw pt remiză
        saveScores();
        mvprintw(10, 0, "Apasa enter  pentru a continua...");
        getch();  // Asteapta apasarea unei taste
        break;
      }

      // verificare remiză (dacă nu mai sunt celule libere)
      int filled = 1; // presupunem ca tabla e umpluta 
      for (int i = 0; i < 3 && filled; i++) { // parcurgem tabla, pentru conditia && filled inseamna ca daca gaseste deja un spatiu gol, numai are rost sa cautam mai departe
        for (int j = 0; j < 3; j++) {
          if (board[i][j] == ' ') {
            filled = 0; //tabla nu este complet goala si iesim din buvla prin break
            break;
          }
        }
      }
      if (filled) { //daca e umpluta 
        clear(); //functie specifica in ncurses
        drawGameScreen();
        mvprintw(8, 0, "Egalitate!"); // este in if de la checkWinner gen daca tabla e plina, dar nu a castigat nimeni
        refresh();
        updateScore('D');
        saveScores();
        mvprintw(10, 0, "Apasa enter pentru a continua...");
        getch();
        break;
      }
    }

    // întrebăm dacă vrei să joci din nou
    clear(); // curata tot. stergi tot pentru a reincepe desenarea de la 0.
    mvprintw(5, 0, "Vrei sa joci din nou? (y/n): ");
    refresh(); //aplici efectiv ce ai scris in mvprintw.
    int answer = getch();
    if (answer != 'y' && answer != 'Y') {
      running = 0; // se opreste
    }
  }

  endInterface();    // Închide ncurses
  return 0;
}
