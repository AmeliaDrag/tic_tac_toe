#ifndef GAME_H
#define GAME_H
#include <stdbool.h>
typedef enum {
    MODE_NONE,
    MODE_PVP,
    MODE_PVE
} GameMode;

extern char board[3][3];
extern char currentPlayer;
extern bool gameOver;

void initGame();
void setGameMode(GameMode mode);
char checkWinner();

#endif
