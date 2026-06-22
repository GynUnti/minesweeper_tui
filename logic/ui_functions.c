#include "headers.h"

void tuiInit(void) {
  initscr();
  cbreak();
}

void gameSetup(Game* g) {
  clear();
  int xMax, yMax;
  int winWid = 30, winHei = 7;
  getmaxyx(stdscr, yMax, xMax);
  WINDOW* win = newwin(winHei, winWid, (yMax-winHei)/2, (xMax-winWid)/2);
  refresh();
  box(win, 0, 0);
  mvwprintw(win, 2, 2, "Rows number (1-%d): ", MAX_ROW);
  wrefresh(win);
  wscanw(win, "%d", &(g->rows));
  mvwprintw(win, 3, 2, "Columns number (1-%d): ", MAX_COL);
  wrefresh(win);
  wscanw(win, "%d", &(g->cols));  
  mvwprintw(win, 4, 2, "Bombs number (1-%d): ", g->rows * g->cols - 1);
  wrefresh(win);
  wscanw(win, "%d", &(g->bombs)); 
  g->freeCellsLeft = g->rows * g->cols - g-> bombs;
  g->state = STATE_ONGOING; /* Start the game */
  clear();
}

void printBoard(Game* g) {
  clear();
  int rows = g->rows;
  int cols = g->cols;
  printw("%5s", "");
  for (int i = 0; i < cols; i++) {
    printw("|%2d", i);
  }
  printw("|\n");
  for (int r = 0; r < rows; r++) {
    printw("%5d", r);
    for (int c = 0; c < cols; c++) {
      printw("|%2c", g->visible[r][c]);
    }
    printw("|\n");
  }
}

void printAll(Game* g) {
  int rows = g->rows;
  int cols = g->cols;
  printw("%5s", "");
  for (int i = 0; i < cols; i++) {
    printw("|%2d", i);
  }
  printw("|\n");
  for (int r = 0; r < rows; r++) {
    printw("%5d", r);
    for (int c = 0; c < cols; c++) {
      printw("|%2c", g->board[r][c]);
    }
    printw("|\n");
  }
}
