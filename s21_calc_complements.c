#include "s21_matrix.h"

/*
Минором M(i,j) называется определитель (n-1)-го порядка,
полученный вычёркиванием из матрицы A i-й строки и j-го столбца.
Алгебраическим дополнением элемента матрицы
является значение минора умноженное на -1^(i+j).
*/

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A->rows < 1 || A->columns < 1) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++) {
        minor_m(i, j, A, &(result->matrix[i][j]));
        result->matrix[i][j] *= pow(-1, i + j);
      }
  }
  return res;
}

void minor_m(int row, int column, matrix_t *A, double *result) {
  matrix_t B;
  s21_create_matrix(A->rows - 1, A->columns - 1, &B);
  for (int x = 0, i = 0; i < A->rows; i++) {
    if (i != row) {
      for (int y = 0, j = 0; j < A->columns; j++)
        if (j != column) B.matrix[x][y++] = A->matrix[i][j];
      x++;
    }
  }
  s21_determinant(&B, result);
  s21_remove_matrix(&B);
}
