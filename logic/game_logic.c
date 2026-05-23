#include <stdio.h>
#include <stdlib.h>

int printMatrix(char**);

int main(void) {
  int n, m;
  n = 30;
  m = 30;
  char** matrix = calloc(30*30, sizeof(char));
  printMatrix(matrix);
  return 0;
}

int printMatrix(char** matrix) {
  int n = sizeof(matrix);
  int m = sizeof(matrix[0]);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("|%2c|", matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}
