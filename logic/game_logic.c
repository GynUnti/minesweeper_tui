#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int printMatrix(int n, int m, char matrix[n][m]);
void shuffle(int array[], int arrayLength);
void expand(int x, int y, int n, int m, char matrix[n+3][m+2], char visibleMatrix[n+2][m+2]);

// MAIN FUNCTION
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
  for (int i = 0; i <= m+1; i++) {
    matrix[0][i] = matrix[n+1][i] = '0';
  }
  for (int i = 1; i <= n; i++) {
    matrix[i][0] = matrix[i][m+1] = '0';
  }
  // Generate bombs position array. Based on the number of bombs user choose, we only choose the first n position to put the bomb in matrix 
  int* bombs = malloc(n*m * sizeof(int));
  for (int i = 0; i < n*m; i++) {
    bombs[i] = i+1;
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
  for (int i = 0; count < bombNum; i++) {
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
  free(bombs); // free memory, no longer use bombs[]

  /* ****************************************** *
   * Insert the number of bombs around a square *
   * (not at the edges, because we only count   *
   * the inner n x m matrix)                    *
   * ****************************************** */
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
      matrix[i][j] = nearBombs + 48; /* '0' in ASCII is 48 */
    }
  }

  /* *********************************** *
   * Create a matrix for visible to user.*
   * This matrix will expand the visible *
   * square depends on user's input.     *
   * *********************************** */
  char visibleMatrix[n+2][m+2]; 
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      visibleMatrix[i][j] = '#';
    }
  }

  /* ********************************** *
   * Run loop for the user to enter x y *
   * until they reach a bomb.           *
   * ********************************** */

  while (matrix[x][y] != 'x') {
    expand(x,y,n,m,matrix,visibleMatrix);
    printMatrix(n,m,visibleMatrix);
    printf("Choose your next coordination (x y): ");
    scanf("%d%d", &x, &y);
  }

  // Print of matrix (will change to the VISIBLE matrix for player, which only shows the squares that user has choosen
  printMatrix(n, m, matrix);
  printf("You Lose!");
  return 0;
}

// PRINT MATRIX FUNCTION
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

// SHUFFLE FUNCTION
void shuffle(int array[], int arrayLength) {
  srand( time(NULL) );
  for (int i = 0; i < arrayLength; i++) {
    int swapIndex = rand() % arrayLength;
    int temp = array[i];
    array[i] = array[swapIndex];
    array[swapIndex] = temp;
  }
}

// EXPAND VISIBLE SQUARES FUNCTION
void expand(int x, int y, int n, int m, char matrix[n+2][m+2], char visibleMatrix[n+2][m+2]) {
  if (visibleMatrix[x][y] != '#') return; 
  visibleMatrix[x][y] = matrix[x][y];
  if (matrix[x][y] != ' ') 
    return;
  expand(x-1,y-1,n,m,matrix,visibleMatrix);
  expand(x,y-1,n,m,matrix,visibleMatrix);
  expand(x+1,y-1,n,m,matrix,visibleMatrix);
  expand(x-1,y,n,m,matrix,visibleMatrix);
  expand(x+1,y,n,m,matrix,visibleMatrix);
  expand(x-1,y+1,n,m,matrix,visibleMatrix);
  expand(x,y+1,n,m,matrix,visibleMatrix);
  expand(x+1,y+1,n,m,matrix,visibleMatrix);
  return;
}
