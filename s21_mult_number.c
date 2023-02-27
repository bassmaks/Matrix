#include "s21_matrix.h"

/*
Произведением матрицы A = m × n на число λ
называется матрица B = m × n = λ × A,
элементы которой определяются равенствами B = λ × A(i,j).
*/

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 2;
  if (A->matrix == NULL) {
    res = 1;
  } else if (A->rows < 1 || A->columns < 1) {
    res = 1;
  } else {
    res = 0;
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return res;
}
