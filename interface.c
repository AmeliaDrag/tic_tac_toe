#include<ncurses.h>
#include "interface.h"
#include"game.h"
#include"ai.h"
#include"scores.h"
int randulSelectat=0;
int coloanaSelectata=0;
//functii standard din documentatia officiala a bibliotecii ncurses
void initInterface() {
    initscr();   // pornește modul special ncurses
    noecho();  // nu afișa tastele apăsate
    cbreak();    // nu aștepta Enter după fiecare tastă
    keypad(stdscr, TRUE); // activează tastele săgeți
    curs_set(0);// ascunde cursorul terminalului
    start_color();  // activează modul color
    init_pair(1, COLOR_RED, COLOR_BLACK);     // X rosu
    init_pair(2, COLOR_CYAN, COLOR_BLACK);    // O cyan
    init_pair(3, COLOR_WHITE, COLOR_BLUE);    // fundal evidentiat

}
void endInterface() {
    endwin();  // stop la modul ncurses revine terminalul la normalll
}
//desenarea tablei:
//mvprintw(y,x, "text") = mergi pana la pozitia y,x si scri textul
//attron= evindeteaza/ e un efect vizual
//attroff = dezactiveaza efectul vizual
//attron(A_REVERSE)= INVERSEAZA CULOAREA textului gen fundal negru text alb in fundal alb text negru or smth
// puteam folosi si bold, blick, dim etc
void drawGameScreen() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == randulSelectat && j == coloanaSelectata)
                attron(COLOR_PAIR(3)); // fundal evidențiat

            char c = board[i][j];
            if (c == 'X') {
                attron(COLOR_PAIR(1));
                mvprintw(i * 2, j * 4, " %c ", c);
                attroff(COLOR_PAIR(1));
            } else if (c == 'O') {
                attron(COLOR_PAIR(2));
                mvprintw(i * 2, j * 4, " %c ", c);
                attroff(COLOR_PAIR(2));
            } else {
                mvprintw(i * 2, j * 4, "   ");
            }

            if (i == randulSelectat && j == coloanaSelectata)
                attroff(COLOR_PAIR(3)); // oprește fundalul

            if (j < 2)
                mvprintw(i * 2, j * 4 + 3, "|");
        }
        if (i < 2)
            mvprintw(i * 2 + 1, 0, "---+---+---");
    }
    //A_REVERSE - functie care face caracterele albe pe fundal negru.
    mvprintw(8, 0, "Scor - X: %d  O: %d  Remiza: %d", scoreX, scoreO, draws);
    refresh();
}

// ch e caracaterul pus. key_up e sageata in sus s tot asa
void handleInput(int ch, int mode) {
  if (ch == KEY_UP && randulSelectat > 0) randulSelectat--;
  if (ch == KEY_DOWN && randulSelectat < 2) randulSelectat++;
  if (ch == KEY_LEFT && coloanaSelectata > 0) coloanaSelectata--;
  if (ch == KEY_RIGHT && coloanaSelectata < 2) coloanaSelectata++;
  if (ch == '\n') { // ENTER
    if (board[randulSelectat][coloanaSelectata] == ' ') {
      board[randulSelectat][coloanaSelectata] = currentPlayer;
      currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
      if (mode == 2 && currentPlayer == 'O') { // dacă joci PVSAI si e randul lui O
	aiMakeMove();  // ai face mutare
        currentPlayer = 'X'; // apoi e iar randul tau
      }
    }
  }
}

