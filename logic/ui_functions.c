#include "headers.h"

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
