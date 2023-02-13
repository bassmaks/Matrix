#include "s21_matrix.h"

/*
Произведением матрицы A = m × k на матрицу B = k × n
называется матрица C = m × n = A × B размера m × n,
элементы которой определяются равенством
C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + … + A(i,k) × B(k,j).
*/

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1) {
    res = 1;
  } else if (A->columns != B->rows) {
    res = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < B->rows; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return res;
}
