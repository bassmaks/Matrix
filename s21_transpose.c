#include "s21_matrix.h"

/*
Транспонирование матрицы А заключается в замене строк
этой матрицы ее столбцами с сохранением их номеров.
*/

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A->rows < 1 || A->columns < 1) {
    res = 1;
    // } else if (A->rows != result->columns || A->columns != result->rows) {
    //   res = 2;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++)
        result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return res;
}
