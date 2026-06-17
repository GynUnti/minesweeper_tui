#include "headers.h"

void printBoard(Game *g);

// MAIN FUNCTION
int main(void) {
  Game g;
  initSize(&g);
  initBoard(&g);
  while (g.state == STATE_ONGOING) {
    int r, c;
    printBoard(&g);
    printf("Pick your cell (r, c): ");
    scanf("%d%d", &r, &c);
    if (g.firstMove) {
      placeBomb(&g, r, c);
      numGen(&g);
      g.firstMove = false;
    }
    if (g.board[r][c] == 'x') {
      printf("You Lose!");
      return 0;
    }
    domainExpansion(&g, r, c);
    if (g.freeCellsLeft == 0) {
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
