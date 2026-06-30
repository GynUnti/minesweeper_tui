#include "headers.h"


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
  int* bombPlace = (int*)malloc(total * sizeof(int));
  srand(time(NULL));
  for (int i = 0; i < total; i++) bombPlace[i] = i;

  /* scramble the bomb placements */
  /* i = 0 will cause division by 0 */
  for (int i = total-1; i > 0; i--) {
   int random = rand() % i;
   int temp = bombPlace[i];
   bombPlace[i] = bombPlace[random];
   bombPlace[random] = temp;
  }

  /* Place bombs, avoiding the initial cell */
  for (int placed = 0, j = 0; placed < bombs; j++) {
    int r = bombPlace[j] / cols;
    int c = bombPlace[j] % cols;
    if (r == firstRow && c == firstCol) continue;
    g->board[r][c] = 'x'; /* Place bomb */
    placed++;
  }
  free(bombPlace); /* Free bomb placements array */
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
          if (g->board[r+i][c+j] == 'x') n++;
        }
      }
      if (n == 0) g->board[r][c] = ' ';
      else g->board[r][c] = n + '0';
    }
  }
}

/* Expand visible board once user choose a cell */
void domainExpansion(Game *g, WINDOW* visibleBoard, int r, int c) {
  int rows = g->rows;
  int cols = g->cols;
  if (r < 0 || r >= rows || c < 0 || c >= cols) return;
  char cell = g->board[r][c];
  if (cell == 'x') return;
  if (g->visible[r][c] != '#' && g->visible[r][c] != 'f') return;
  g->visible[r][c] = cell;
  /* Update Visible board
   * So technically this function is both logic and UI
   */
  printCell(g, visibleBoard, r, c);
  
  g->freeCellsLeft--;
  
  /* Expand recursively if the cell have no bomb near it */
  if (cell == ' ') {
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0) continue;
        domainExpansion(g, visibleBoard, r+i, c+j);
      }
    }
  }
}

/* Flag Toggle function */
void flagToggle(Game *g, int r, int c) {
  int rows = g->rows;
  int cols = g->cols; 
  if (r >= rows || c >= cols) {
    printf("cell out of range\n");
    return;
  }
  if (g->visible[r][c] == '#') {
    g->visible[r][c] = 'f';
  }
  else if (g->visible[r][c] == 'f') {
    g->visible[r][c] = '#';
  }
}

void winCheck(Game* g, int r, int c) {
  if (g->freeCellsLeft == 0) g->state = STATE_WON;
  else if (g->board[r][c] == 'x') g->state = STATE_LOST;
}

