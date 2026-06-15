#include "headers.h"

void initSize(Game *g) {
  printf("\nPlease enter number of rows and columns.");
  printf("\nRows (1-100): ");
  scanf("%d", &(g->rows));
  printf("\nColumns (1-100): ");
  scanf("%d", &(g->cols));
  printf("\nPlease enter number of bombs (1-%d): ", g->rows * g->cols - 1);
  scanf("%d", &(g->bombs));
  g->freeCellsLeft = g->rows * g->cols - g-> bombs;
  g->state = STATE_ONGOING; /* Start the game */
}

void initBoard(Game *g) {
  int rows = g->rows;
  int cols = g->cols;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      g->visible[r][c] = '#';
    }
  }
  g->firstMove = true;
}

void placeBomb(Game *g, int firstRow, int firstCol) {
  int rows = g->rows;
  int cols = g->cols;
  int bombs = g->bombs;
  int total = rows*cols;
  /*
   * Create an array of bomb placements for all position, shuffle it, and pick 
   * the first *bombs* number of bomb placements (exclude the first cell) to place the bombs
   */
  int* bombPlace = (int*)malloc((unsigned)total * sizeof(int));
  srand(time(NULL));
  for (int i = 0; i < total; i++) bombPlace[i] = i;
  for (int i = total-1; i >= 0; i--) {
   int random = rand() % i;
   int temp = bombPlace[i];
   bombPlace[i] = bombPlace[random];
   bombPlace[random] = temp;
  }
  for (int i = 0, j = 0; i < bombs; i++, j++) {
    int r = bombPlace[j] / cols;
    int c = bombPlace[j] % cols;
    if (r == firstRow && c == firstCol) {
      i--;
      continue;
    }
    g->board[r][c] = 'x'; /* Place bomb */
    free(bombPlace); /* Free bomb placements array */
  }
}

void numGen(Game *g) {
  int rows = g->rows;
  int cols = g->cols;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      int n = 0;
      if (g->board[r][c] == 'x') continue;
      for (int i = -1; i <=1; i++) {
        for (int j = -1; j <= 1; j++) {
          if (i==0 && j==0) continue;
          if (r+i < 0 || r+i >= rows || c+j <0 || c+j >= cols) continue;
          if (g->board[r+i][c+j] = 'x') n++;
        }
      }
      if (n == 0) g->board[r][c] = ' ';
      else g->board[r][c] = n + '0';
    }
  }
}

void domainExpansion(Game *g, int r, int c) {
  int rows = g->rows;
  int cols = g->cols;
  if (r < 0 || r >= rows || c < 0 || c >= cols) return;
  char cell = g->board[r][c];
  if (cell == 'x') return;
  if (g->visible[r][c] != '#') return;
  g->visible[r][c] = cell;
  g->freeCellsLeft--;
  
  /* Expand recursively if the cell have no bomb near it */
  if (cell == ' ') {
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0) continue;
        domainExpansion(g, r+i, c+j);
      }
    }
  }
}


