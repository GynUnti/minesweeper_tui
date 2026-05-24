#include <stdio.h>
#include <stdlib.h>

int printMatrix(int n, int m, char matrix[n][m]);

int main(void) {
  int n, m;
  n = 30;
  m = 30;
  char matrix[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      matrix[i][j] = 0;
    }
  }
  printMatrix(n, m, matrix);
  return 0;
}

int printMatrix(int n, int m, char matrix[n][m]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("|%1d", matrix[i][j]);
    }
    printf("|\n");
  }
  return 0;
}
