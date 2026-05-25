#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int printMatrix(int n, int m, char matrix[n][m]);
void shuffle(int array[], int arrayLength);

int main(void) {
  int n, m;
  int bombNum;
  
  //Enter board dimension
  printf("Please enter the board's dimension (n m): ");
  scanf("%d%d", &n, &m);
  // Generate board with all blank
  char matrix[n+2][m+2]; // This will create a n+2 x m+2 matrix. The one we actually use is the inner n x m
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      matrix[i][j] = ' ';
    }
  }
  // Generate bombs position array. Based on the number of bombs user choose, we only choose the first n position to put the bomb in matrix 
  int bombs[n*m];
  for (int i = 1; i <= n*m; i++) {
    bombs[i] = i;
  }
  shuffle(bombs, n*m); // Shuffle bomb positions
  printf("\nPlease enter number of bombs (<%d): ", n*m);
  scanf("%d", &bombNum);

  // Prompt to choose the first position, which the bomb will not be put in
  int x, y; // x y are the coordinates that user chooses
  printf("\nChoose your first square (x y) with x < %d; y < %d: ", n, m);
  scanf("%d%d", &x, &y);
  
  // Place the bombs in the matrix
  int count = 0;
  for (int i = 1; count <= bombNum; i++) {
    // bombs[i] = m*x + y
    int yTemp = bombs[i] % m;
    int xTemp = (bombs[i] / m) + 1;
    if (yTemp == 0) {
      yTemp = m; 
      xTemp--;
    }
    if (xTemp != x || yTemp != y) {
      matrix[xTemp][yTemp] = 'x';
      count++;
    }
  }

  // Insert the number of bombs around a square (not at the edges, because we only count the inner n x m matrix)
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (matrix[i][j] == 'x') continue;
      int nearBombs = 0;
      if (matrix[i-1][j-1] == 'x') nearBombs++;
      if (matrix[i-1][j] == 'x') nearBombs++;
      if (matrix[i-1][j+1] == 'x') nearBombs++;
      if (matrix[i][j-1] == 'x') nearBombs++;
      if (matrix[i][j+1] == 'x') nearBombs++;
      if (matrix[i+1][j-1] == 'x') nearBombs++;
      if (matrix[i+1][j] == 'x') nearBombs++;
      if (matrix[i+1][j+1] == 'x') nearBombs++;
      if (nearBombs == 0) continue;
      matrix[i][j] = nearBombs + 48; // '0' in ASCII is 48
    }
  }

  // Print of matrix (will change to the VISIBLE matrix for player, which only shows the squares that user has choosen
  printMatrix(n, m, matrix);
  return 0;
}

int printMatrix(int n, int m, char matrix[n+2][m+2]) {
  printf("|%2c", ' ');
  for (int j = 1; j <= m; j++) {
    printf("|%2d", j);
  }
  printf("|\n");
  for (int i = 1; i <= n; i++) {
    printf("|%2d", i);
    for (int j = 1; j <= m; j++) {
      printf("|%2c", matrix[i][j]);
    }
    printf("|\n");
  }
  return 0;
}

void shuffle(int array[], int arrayLength) {
  srand( time(NULL) );
  for (int i = 0; i < arrayLength; i++) {
    int swapIndex = rand() % arrayLength;
    int temp = array[i];
    array[i] = array[swapIndex];
    array[swapIndex] = temp;
  }
}
