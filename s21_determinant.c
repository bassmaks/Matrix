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
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    matrix_t B;
    s21_create_matrix(A->rows, A->columns + A->columns - 1, &B);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns + A->columns - 1; j++) {
        if (j < A->columns) B.matrix[i][j] = A->matrix[i][j];
        if (j >= A->columns) B.matrix[i][j] = A->matrix[i][j - A->columns];
      }
    }
    double maind, secd;
    diagon(B, &maind);
    *result = maind;
    matrix_t C;
    s21_create_matrix(B.rows, B.columns, &C);
    mirror(&B, &C);
    diagon(C, &secd);
    *result -= secd;
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
  }
  return res;
}

void mirror(matrix_t *Enter, matrix_t *Exit) {
  s21_create_matrix(Enter->rows, Enter->columns, Exit);
  for (int i = 0; i < Enter->rows; i++) {
    for (int j = 0; j < Enter->columns; j++)
      Exit->matrix[i][j] = Enter->matrix[i][Enter->columns - j - 1];
  }
}

// перемножение и сложение диагоналей
void diagon(matrix_t A, double *res) {
  *res = 0;
  for (int k = 0; k < (A.columns + 1) / 2; k++) {
    double maind = 1;
    for (int i = 0; i < A.rows; i++) {
      for (int j = 0; j < A.columns; j++) {
        if (i + k == j) maind *= A.matrix[i][j];
      }
    }
    *res += maind;
  }
}
