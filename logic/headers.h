#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define MAX_ROW 100
#define MAX_COL 100
#define STATE_ONGOING 0
#define STATE_WON 1
#define STATE_LOST 2

/* define color pair naming convention */
#define CP_HIDDEN 0
#define CP_EMPTY 1
#define CP_BOMB 2
#define CP_FLAG 3
#define CP_N1 4
#define CP_N2 5
#define CP_N3 6
#define CP_N4 7
#define CP_N5 8
#define CP_N6 9
#define CP_N7 10
#define CP_N8 11


typedef struct {
  int rows, cols, bombs;
  char board[MAX_ROW][MAX_COL]; /* true board "hidden" */
  char visible[MAX_ROW][MAX_COL]; /* visible board for user */
  int freeCellsLeft; /* free non-bomb cells left, 0 left means user won */
  int state; /* STATE_ONGOING, STATE_WON, STATE_LOST */
  bool firstMove; /* true until first cell is chosen */
} Game;

/*
 * logic functions
 */
void initBoard(Game *g);
void placeBomb(Game *g, int firstRow, int FirstCol);
void numGen(Game *g);
void domainExpansion(Game *g, int r, int c);
void flagToggle(Game *g, int r, int c);
void winCheck(Game* g, int r, int c);

/*
 * ui functions
 */
void tuiInit(void);
void initColors(void);
int colorAttrAssign(char c);
void gameSetup(Game* g);
void printBoard(Game* g);
void printAll(Game* g);
