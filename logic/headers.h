#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define MAX_ROW 100
#define MAX_COL 100
#define STATE_ONGOING 0
#define STATE_WON 1
#define STATE_LOST 2

typedef struct {
  int rows, cols, bombs;
  char board[MAX_ROW][MAX_COL]; /* true board "hidden" */
  char visible[MAX_ROW][MAX_COL]; /* visible board for user */
  int freeCellsLeft; /* free non-bomb cells left, 0 left means user won */
  int state; /* STATE_ONGOING, STATE_WON, STATE_LOST */
  bool firstMove; /* true until first cell is chosen */
} Game;

void initSize(Game *g);
void initBoard(Game *g);
void placeBomb(Game *g, int firstRow, int FirstCol);
void numGen(Game *g);
void domainExpansion(Game *g, int r, int c);

