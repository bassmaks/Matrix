#include "s21_matrix.h"

/*
Определитель матрицы равен сумме произведений
элементов строки (столбца) на соответствующие
алгебраические дополнения.
*/

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  if (A->rows < 1 || A->columns < 1) {
    res = 1;
  } else if (A->rows != A->columns) {
    res = 2;
  } else if (A->rows == 1 && A->columns == 1) {
    *result = A->matrix[0][0];
  } else {
    matrix_t B;
    double det = 0;
    s21_calc_complements(A, &B);
    for (int j = 0; j < A->columns; j++)
      det += A->matrix[0][j] * B.matrix[0][j];
    *result = det;
    s21_remove_matrix(&B);
  }
  return res;
}
