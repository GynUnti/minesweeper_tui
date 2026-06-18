#include "headers.h"

void printBoard(Game *g);
void printAll(Game *g);

// MAIN FUNCTION
int main(void) {
  Game g;
  initSize(&g);
  initBoard(&g);
  while (g.state == STATE_ONGOING) {
    int r, c;
    char flag;
    printBoard(&g);
    printf("Pick your cell (r, c) (add f for flag): ");
    scanf("%d%d", &r, &c);
    while ((flag = getchar()) != '\n') {
      if (flag == 'f') break;
    }
    if (flag == 'f') {
      flagToggle(&g, r, c);
      continue;
    }
    if (g.firstMove) {
      placeBomb(&g, r, c);
      numGen(&g);
      g.firstMove = false;
    }
    domainExpansion(&g, r, c);
    if (g.board[r][c] == 'x') {
      printAll(&g);
      printf("You Lose!");
      return 0;
    }
    if (g.freeCellsLeft == 0) {
      printAll(&g);
      printf("You Won!");
      return 0;
    }
  }
  return 0;
}

void printBoard(Game* g) {
  int rows = g->rows;
  int cols = g->cols;
  printf("%5s", "");
  for (int i = 0; i < cols; i++) {
    printf("|%2d", i);
  }
  printf("|\n");
  for (int r = 0; r < rows; r++) {
    printf("%5d", r);
    for (int c = 0; c < cols; c++) {
      printf("|%2c", g->visible[r][c]);
    }
    printf("|\n");
  }
}

void printAll(Game* g) {
  int rows = g->rows;
  int cols = g->cols;
  printf("%5s", "");
  for (int i = 0; i < cols; i++) {
    printf("|%2d", i);
  }
  printf("|\n");
  for (int r = 0; r < rows; r++) {
    printf("%5d", r);
    for (int c = 0; c < cols; c++) {
      printf("|%2c", g->board[r][c]);
    }
    printf("|\n");
  }
}
