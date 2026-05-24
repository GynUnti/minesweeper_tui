#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int printMatrix(int n, int m, char matrix[n][m]);
void shuffle(int array[], int arrayLength);

int main(void) {
  int n, m;
  int bombNum;
  printf("Please enter the board's dimension (n m): ");
  scanf("%d%d", &n, &m);
  char matrix[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      matrix[i][j] = ' ';
    }
  }
  int bombs[n*m];
  for (int i = 0; i < n*m; i++) {
    bombs[i] = i;
  }
  shuffle(bombs, n*m);
  printf("\nPlease enter number of bombs (<%d): ", n*m);
  scanf("%d", &bombNum);
  for (int i = 0; i < bombNum; i++) {
    // bombs[i] = n*x + y
    int y = bombs[i] % n;
    int x = bombs[i] / n;
    matrix[x][y] = 'x';
  }
  printMatrix(n, m, matrix);
  return 0;
}

int printMatrix(int n, int m, char matrix[n][m]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("|%1c", matrix[i][j]);
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
