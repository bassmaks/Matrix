#ifndef _SRC_S21_MATRIX_H
#define _SRC_S21_MATRIX_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1  // Сравнение матриц
#define FAILURE 0  //  Сравнение матриц

/*
0 - OK
1 - Ошибка, некорректная матрица
2 - Ошибка вычисления (несовпадающие размеры матриц;
матрица, для которой нельзя провести вычисления и т.д.)
*/

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

//  Создание матриц (create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result);

//  Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t *A);

//  Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B);

//  Сложение (sum_matrix) и вычитание матриц (sub_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

//  Умножение матрицы на число (mult_number)
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

//  Умножение двух матриц (mult_matrix)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

//  Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result);

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result);

//  Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void minor_m(int row, int column, matrix_t *A, double *result);

#endif  // _SRC_S21_MATRIX_H
