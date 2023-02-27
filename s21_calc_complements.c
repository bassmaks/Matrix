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
    matrix_t B;
    double det;
    s21_create_matrix(A->rows - 1, A->rows - 1, &B);
    s21_create_matrix(A->rows, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->rows; j++) {
        minor_m(A, &B, i, j);
        s21_determinant(&B, &det);
        result->matrix[i][j] = det * pow(-1, i + j);
      }
    }
    s21_remove_matrix(&B);
  }
  return res;
}

// Получение матрицы без i-й строки и j-го столбца
void minor_m(matrix_t *Enter, matrix_t *Exit, int row, int column) {
  s21_create_matrix(Enter->rows - 1, Enter->columns - 1, Exit);
  int offsetRow = 0;  // Смещение индекса строки в матрице
  int offsetCol = 0;  // Смещение индекса столбца в матрице
  for (int i = 0; i < Enter->rows - 1; i++) {
    // Пропустить row-ую строку
    if (i == row) {
      offsetRow = 1;  // Как только встретили строку, которую надо
                      // пропустить, делаем смещение для исходной матрицы
    }
    offsetCol = 0;  // Обнулить смещение столбца
    for (int j = 0; j < Enter->columns - 1; j++) {
      // Пропустить col-ый столбец
      if (j == column) {
        offsetCol = 1;  // Встретили нужный столбец, проускаем его смещением
      }

      Exit->matrix[i][j] = Enter->matrix[i + offsetRow][j + offsetCol];
    }
  }
}
