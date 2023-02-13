# Matrix

Реализация библиотеки matrix.h.


  > В данном проекте я реализовал свою библиотеку для обработки числовых матриц на языке программирования Си. Матрицы являются одной из базовых структур данных в программировании, например, они применяются для представления табличных значений, для вычислительных задач и нейронных сетей. 

## Историческая справка

Первые упоминания о матрицах (или как их тогда называли - "волшебных квадратах") были обнаружены на территории древнего Китая. \
Свою известность они получили в середине XVIII века благодаря труду знаменитого математика Габриэля Крамера, опубликовавшего свой труд - "Введение в анализ алгебраических кривых", в котором описывался принципиально новый алгоритм решения систем линейных уравнений. \
Вскоре после него были опубликованы работы Карла Фридриха Гаусса о "классическом" методе решения линейных уравнений, теорема Гамильтона-Кели, работы Карла Вейерштрасса, Георга Фробениуса и других выдающихся ученых. \
И только в 1850 году Джеймс Джозеф Сильвестр в своей работе вводит термин "Матрица".

## Матрица

Матрица - это набор чисел, расположенных в фиксированном количестве строк и столбцов.

Матрица A - прямоугольная таблица чисел, расположенных в m строках и n столбцах

```
    1 2 3
A = 4 5 6
    7 8 9
```

```
     1  2  3  4
В =  5  6  7  8
     9 10 11 12
```

Получить нужный элемент можно при помощи индексов, так
A[1,1] = 1, где первый индекс - номер строки, второй - номер столбца.

Матрица А будет иметь элементы с следующими индексами:

```
    (1,1) (1,2) (1,3)
A = (2,1) (2,2) (2,3)
    (3,1) (3,2) (3,3)
```

Порядок матрицы — это число ее строк или столбцов. \
Главная диагональ квадратной матрицы — это диагональ, идущая из левого верхнего в правый нижний угол. \
Прямоугольная матрица (В) — это матрица, у которой число строк не равно числу столбцов. \
Квадратная матрица (А) — это матрица у которой число строк равно числу столбцов.

Матрица-столбец — это матрица, у которой всего один столбец:

```
    (1,1)
A = (2,1)
    (n,1)
```

Матрица-строка — это матрица, у которой всего одна строка:

```
A = (1,1) (1,2) (1,m)
```
Tip: матрицу-столбец и матрицу-строку ещё часто называют векторами.

Диагональная матрица — это квадратная матрица, у которой все элементы, кроме, быть может, стоящих на главной диагонали, равны нулю. \
Единичная матрица — это диагональная матрица, у которой все диагональные элементы равны единице:

```
    1 0 0
A = 0 1 0
    0 0 1
```

Треугольная матрица — это квадратная матрица, у которой все элементы, расположенные по одну сторону главной диагонали, равны нулю.

```
    1 2 3
A = 0 4 5
    0 0 6
```

### Структура матрицы на языке C:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

## Операции над матрицами

Все операции (кроме сравнения матриц) должны возвращать результирующий код:  
- 0 - OK
- 1 - Ошибка, некорректная матрица   
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

### Создание матриц (create_matrix)

```c
int s21_create_matrix(int rows, int columns, matrix_t *result);
```

### Очистка матриц (remove_matrix)

```c
void s21_remove_matrix(matrix_t *A);
```

### Сравнение матриц (eq_matrix)

```c
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```

Две матрицы A, B совпадают |A = B|, если совпадают их размеры и соответствующие элементы равны, то есть при всех i, j A(i,j) = B(i,j).

Сравнение должно происходить вплоть до 7 знака после запятой включительно.

### Сложение (sum_matrix) и вычитание матриц (sub_matrix)

```c
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

Суммой двух матриц A = m × n и B = m × n одинаковых размеров называется матрица C = m × n = A + B тех же размеров, элементы которой определяются равенствами C(i,j) = A(i,j) + B(i,j).

Разностью двух матриц A = m × n и B = m × n одинаковых размеров называется матрица C = m × n = A - B тех же размеров, элементы которой определяются равенствами C(i,j) = A(i,j) - B(i,j).

```
            1 2 3   1 0 0   2 2 3
С = A + B = 0 4 5 + 2 0 0 = 2 4 5
            0 0 6   3 4 1   3 4 7
```

### Умножение матрицы на число (mult_number). Умножение двух матриц (mult_matrix)

```c
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

Произведением матрицы A = m × n на число λ называется матрица B = m × n = λ × A, элементы которой определяются равенствами B = λ × A(i,j).

```
                1 2 3   2 4 6   
B = 2 × A = 2 × 0 4 2 = 0 8 4 
                2 3 4   4 6 8   
```

Произведением матрицы A = m × k на матрицу B = k × n называется матрица C = m × n = A × B размера m × n, элементы которой определяются равенством C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + … + A(i,k) × B(k,j).

```
            1 4    1 -1  1    9 11 17   
C = A × B = 2 5  × 2  3  4 = 12 13 22 
            3 6              15 15 27
```

Компоненты матрицы С вычисляются следующим образом:

```
C(1,1) = A(1,1) × B(1,1) + A(1,2) × B(2,1) = 1 × 1 + 4 × 2 = 1 + 8 = 9
C(1,2) = A(1,1) × B(1,2) + A(1,2) × B(2,2) = 1 × (-1) + 4 × 3 = (-1) + 12 = 11
C(1,3) = A(1,1) × B(1,3) + A(1,2) × B(2,3) = 1 × 1 + 4 × 4 = 1 + 16 = 17
C(2,1) = A(2,1) × B(1,1) + A(2,2) × B(2,1) = 2 × 1 + 5 × 2 = 2 + 10 = 12
C(2,2) = A(2,1) × B(1,2) + A(2,2) × B(2,2) = 2 × (-1) + 5 × 3 = (-2) + 15 = 13
C(2,3) = A(2,1) × B(1,3) + A(2,2) × B(2,3) = 2 × 1 + 5 × 4 = 2 + 20 = 22
C(3,1) = A(3,1) × B(1,1) + A(3,2) × B(2,1) = 3 × 1 + 6 × 2 = 3 + 12 = 15
C(3,2) = A(3,1) × B(1,2) + A(3,2) × B(2,2) = 3 × (-1) + 6 × 3 = (-3) + 18 = 15
C(3,3) = A(3,1) × B(1,3) + A(3,2) × B(2,3) = 3 × 1 + 6 × 4 = 3 + 24 = 27			
```

### Транспонирование матрицы (transpose)

```c
int s21_transpose(matrix_t *A, matrix_t *result);
```

Транспонирование матрицы А заключается в замене строк этой матрицы ее столбцами с сохранением их номеров.

```
          1 4   1 2 3
A = A^T = 2 5 = 4 5 6
          3 6
```

### Минор матрицы и матрица алгебраических дополнений (calc_complements)

```c
int s21_calc_complements(matrix_t *A, matrix_t *result);
```

Минором M(i,j) называется определитель (n-1)-го порядка, полученный вычёркиванием из матрицы A i-й строки и j-го столбца.

Для матрицы:

```
    1 2 3
A = 0 4 2
    5 2 1
```

Минором первого элемента первой строки будет:

```
M(1,1) = 4 2
         2 1

|M| = 4 - 4 = 0
```

Матрица миноров будет иметь вид:

```
     0 -10 -20
M = -4 -14  -8
    -8   2   4
```

Алгебраическим дополнением элемента матрицы  является значение минора умноженное на -1^(i+j).

Матрица алгебраических дополнений будет иметь вид:

```
      0  10 -20
M. =  4 -14   8
     -8  -2   4
```

### Определитель матрицы (determinant)

```c
int s21_determinant(matrix_t *A, double *result);
```

Определитель (детерминант) - это число, которое ставят в соответствие каждой квадратной матрице и вычисляют из элементов по специальным формулам. \
Tip: определитель может быть вычислен только для квадратной матрицы.

Определитель матрицы равен сумме произведений элементов строки (столбца) на соответствующие алгебраические дополнения.

Поиск определителя для матрицы A по первой строке:

```
    1 2 3
A = 4 5 6
    7 8 9
	
|A| = 1 × 5 6 - 2 × 4 6 + 3 × 4 5 = 1 × (5 × 9 - 8 × 6) - 2 × (4 × 9 - 6 × 7) + 3 × (4 × 8 - 7 × 5)
          8 9       7 9       7 8
|A| = 1 × (45 - 48) - 2 × (36 - 42) + 3 × (32 - 35) = -3 + 12 + (-9) = 0
|A| = 0
```

### Обратная матрица (inverse_matrix)

```c
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```

Матрицу A в степени -1 называют обратной к квадратной матрице А, если произведение этих матриц равняется единичной матрице.

Обратной матрицы не существует, если определитель равен 0.

Обратная матрица находится по формуле $`A^{-1}=\frac{1} {|A|} × A_*^T`$

Дана матрица:

```
     2  5  7
A =  6  3  4
     5 -2 -3
```

Поиск определителя:

``` |A| = -1 ```

Определитель |A| != 0 -> обратная матрица существует.

Построение матрицы миноров:

```
    -1 -38 -27
М = -1 -41 -29
    -1 -34 -24
```

Матрица алгебраических дополнений будет равна:

```
     -1  38 -27
М. =  1 -41  29
     -1  34 -24
```

Транспонированная матрица алгебраических дополнений будет равна:

```
        -1   1  -1
М^T. =  38 -41  34
       -27  29 -24
```
