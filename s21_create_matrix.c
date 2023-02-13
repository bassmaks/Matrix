#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (rows < 1 || columns < 1) {
    res = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    // if (result->matrix != NULL) {
    for (int i = 0; i < result->rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
    // }
  }
  return res;
}
