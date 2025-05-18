#ifndef SCORES_H
#define SCORES_H

extern int scoreX;
extern int scoreO;
extern int draws;

void updateScore(char winner);
void resetScores();
void saveScores();
void loadScores();

#endif

