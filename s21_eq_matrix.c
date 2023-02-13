#include "s21_matrix.h"

/*
Две матрицы A, B совпадают |A = B|,
если совпадают их размеры и соответствующие элементы равны,
то есть при всех i, j A(i,j) = B(i,j).
вплоть до 7 знака после запятой включительно.
*/

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A && B && A->rows > 0 && B->rows > 0 && A->columns > 0 &&
      B->columns > 0 && A->matrix && B->matrix && A->rows == B->rows &&
      A->columns == B->columns) {
    for (int i = 0; i < A->rows && res; i++) {
      for (int j = 0; j < A->columns && res; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) res = FAILURE;
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}
