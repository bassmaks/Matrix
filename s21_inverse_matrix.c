#include "s21_matrix.h"

/*
Матрицу A в степени -1 называют обратной к квадратной матрице А,
если произведение этих матриц равняется единичной матрице.
Обратной матрицы не существует, если определитель равен 0.
*/

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  double det;
  if (A->rows < 1 || A->columns < 1) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else {
    matrix_t B;
    s21_create_matrix(A->rows, A->columns, result);
    s21_create_matrix(A->rows, A->columns, &B);
    s21_determinant(A, &det);
    if (det == 0) res = 1;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_determinant(A, &det);
        B.matrix[i][j] = det * pow(-1, i + j);
      }
    }
    s21_transpose(&B, result);
    s21_remove_matrix(&B);
  }
  return res;
}
