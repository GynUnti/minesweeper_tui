#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define MAX_ROW 100
#define MAX_COL 100
#define STATE_ONGOING 0
#define STATE_WON 1
#define STATE_LOST 2

void initSize(Game *g);
void first_cell(Game *g);
void place_bombs(Game *g);


