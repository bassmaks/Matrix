#include <check.h>

#include "s21_matrix.h"

START_TEST(test_s21_eq) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  int result1 = s21_create_matrix(2, 3, &matrix_00);
  int result2 = s21_create_matrix(2, 3, &matrix_01);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[0][2] = 3e-5;
  matrix_00.matrix[1][0] = -1e19;
  matrix_00.matrix[1][1] = 0.0;
  matrix_00.matrix[1][2] = 1.1234567;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_01.matrix[i][j] = matrix_00.matrix[i][j];
    }
  }
  matrix_01.matrix[1][2] = 1.12345679;
  int result = s21_eq_matrix(&matrix_00, &matrix_01);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);
  s21_remove_matrix(&matrix_00);
  s21_remove_matrix(&matrix_01);

  matrix_t matrix_02;
  result = s21_create_matrix(0, 4, &matrix_02);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_02);

  matrix_t matrix_03;
  result = s21_create_matrix(3, -1, &matrix_03);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_03);

  matrix_t *matrix_04 = NULL;
  result = s21_create_matrix(3, 4, matrix_04);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(matrix_04);
}
END_TEST

START_TEST(test_s21_eq_err) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  int result1 = s21_create_matrix(2, 3, &matrix_00);
  int result2 = s21_create_matrix(2, 3, &matrix_01);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[0][2] = 3e-5;
  matrix_00.matrix[1][0] = -1e19;
  matrix_00.matrix[1][1] = 0.0;
  matrix_00.matrix[1][2] = 1.1234567;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_01.matrix[i][j] = matrix_00.matrix[i][j];
    }
  }
  matrix_01.matrix[1][2] = 1.1234568;
  int result = s21_eq_matrix(&matrix_00, &matrix_01);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);
  s21_remove_matrix(&matrix_00);

  matrix_t matrix_02;
  int result3 = s21_create_matrix(1, 4, &matrix_02);
  ck_assert_int_eq(result3, 0);
  int result4 = s21_eq_matrix(&matrix_00, &matrix_02);
  ck_assert_int_eq(result4, 0);
  s21_remove_matrix(&matrix_01);
  s21_remove_matrix(&matrix_02);
}
END_TEST

START_TEST(test_s21_sum) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;
  int result1 = s21_create_matrix(3, 2, &matrix_00);
  int result2 = s21_create_matrix(3, 2, &matrix_01);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0 / 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  matrix_01.matrix[0][0] = 451.4866;
  matrix_01.matrix[0][1] = -24.564;
  matrix_01.matrix[1][0] = 3456e-5;
  matrix_01.matrix[1][1] = -.045461e19;
  matrix_01.matrix[2][0] = 0.0;
  matrix_01.matrix[2][1] = 1123.4567;

  int result = s21_sum_matrix(&matrix_00, &matrix_01, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  s21_remove_matrix(&matrix_00);
  s21_remove_matrix(&matrix_01);

  ck_assert_double_eq(res.matrix[0][0], 453.3526);
  ck_assert_double_eq(res.matrix[0][1], 24539.436);
  ck_assert_double_eq(res.matrix[1][0], 0.03459);
  ck_assert_double_eq(res.matrix[1][1], 954539e13);
  ck_assert_double_nan(res.matrix[2][0]);
  ck_assert_double_eq(res.matrix[2][1], 1124.5801566999999);

  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_s21_sum_err) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;

  int result1 = s21_create_matrix(3, 2, &matrix_00);
  int result2 = s21_create_matrix(2, 2, &matrix_01);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  int result = s21_sum_matrix(&matrix_00, &matrix_01, &res);
  ck_assert_int_eq(result, 2);

  s21_remove_matrix(&matrix_00);

  int result3 = s21_sum_matrix(&matrix_00, &matrix_01, &res);
  ck_assert_int_eq(result3, 1);

  s21_remove_matrix(&matrix_01);
}
END_TEST

START_TEST(test_s21_sub) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;
  int result1 = s21_create_matrix(3, 2, &matrix_00);
  int result2 = s21_create_matrix(3, 2, &matrix_01);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  matrix_01.matrix[0][0] = 451.4866;
  matrix_01.matrix[0][1] = -24.564;
  matrix_01.matrix[1][0] = 3456e-5;
  matrix_01.matrix[1][1] = -.045461e19;
  matrix_01.matrix[2][0] = 1 / 0.0;
  matrix_01.matrix[2][1] = 1123.4567;

  int result = s21_sub_matrix(&matrix_00, &matrix_01, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  s21_remove_matrix(&matrix_00);
  s21_remove_matrix(&matrix_01);

  ck_assert_double_eq(res.matrix[0][0], -449.6206);
  ck_assert_double_eq(res.matrix[0][1], 24588.564);
  ck_assert_double_eq(res.matrix[1][0], -0.03453);
  ck_assert_double_eq(res.matrix[1][1], 1.045461e19);
  ck_assert_double_eq(res.matrix[2][0], -1 / 0.0);
  ck_assert_double_eq(res.matrix[2][1], -1122.3332433);

  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_s21_sub_err) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;

  int result1 = s21_create_matrix(3, 2, &matrix_00);
  int result2 = s21_create_matrix(2, 2, &matrix_01);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  int result = s21_sub_matrix(&matrix_00, &matrix_01, &res);
  ck_assert_int_eq(result, 2);

  s21_remove_matrix(&matrix_00);

  int result3 = s21_sub_matrix(&matrix_00, &matrix_01, &res);
  ck_assert_int_eq(result3, 1);

  s21_remove_matrix(&matrix_01);
}
END_TEST

START_TEST(test_s21_mul_num) {
  matrix_t matrix_00;
  double number = 0.1456e6;
  matrix_t res;
  int result1 = s21_create_matrix(3, 2, &matrix_00);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = -24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = -1e19;
  matrix_00.matrix[2][0] = 1 / 0.0;
  matrix_00.matrix[2][1] = 0 / 0.0;

  int result = s21_mult_number(&matrix_00, number, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);

  s21_remove_matrix(&matrix_00);

  ck_assert_double_eq(res.matrix[0][0], 271689.60000000003);
  ck_assert_double_eq(res.matrix[0][1], -3576518400);
  ck_assert_double_eq(res.matrix[1][0], 4.368);
  ck_assert_double_eq(res.matrix[1][1], -1.456e+24);
  ck_assert_double_eq(res.matrix[2][0], 1 / 0.0);
  ck_assert_double_nan(res.matrix[2][1]);

  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_s21_mul_num_err) {
  matrix_t matrix_00;
  matrix_t res;
  double number = 8478;

  int result1 = s21_create_matrix(3, 0, &matrix_00);
  ck_assert_int_eq(result1, 1);

  int result = s21_mult_number(&matrix_00, number, &res);
  ck_assert_int_eq(result, 1);

  s21_remove_matrix(&matrix_00);
}
END_TEST

START_TEST(test_s21_mul_mat) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;
  int result1 = s21_create_matrix(3, 2, &matrix_00);
  int result2 = s21_create_matrix(2, 3, &matrix_01);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  matrix_01.matrix[0][0] = 451.4866;
  matrix_01.matrix[0][1] = -24.564;
  matrix_01.matrix[0][2] = 3456e-5;
  matrix_01.matrix[1][0] = -.045461e19;
  matrix_01.matrix[1][1] = 56;
  matrix_01.matrix[1][2] = 1123.4567;

  int result = s21_mult_matrix(&matrix_00, &matrix_01, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  s21_remove_matrix(&matrix_00);
  s21_remove_matrix(&matrix_01);

  ck_assert_double_eq(res.matrix[0][0], -1.116704004e+22);
  ck_assert_double_eq(res.matrix[0][1], 1375538.163576);
  ck_assert_double_eq(res.matrix[0][2], 27596590.443288956);
  ck_assert_double_eq(res.matrix[1][0], -4.5461e+36);
  ck_assert_double_eq(res.matrix[1][1], 5.6e+20);
  ck_assert_double_eq(res.matrix[1][2], 1.1234567e+22);
  ck_assert_double_eq(res.matrix[2][0], -510734650387000000);
  ck_assert_double_eq(res.matrix[2][1], 62.9135752);
  ck_assert_double_eq(res.matrix[2][2], 1262.15495677489);

  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_s21_mul_mat_err) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;

  int result1 = s21_create_matrix(3, 2, &matrix_00);
  int result2 = s21_create_matrix(3, 2, &matrix_01);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  int result = s21_mult_matrix(&matrix_00, &matrix_01, &res);
  ck_assert_int_eq(result, 2);

  s21_remove_matrix(&matrix_00);

  int result3 = s21_mult_matrix(&matrix_00, &matrix_01, &res);
  ck_assert_int_eq(result3, 1);

  s21_remove_matrix(&matrix_01);
}
END_TEST

START_TEST(test_s21_trans) {
  matrix_t matrix_00;
  matrix_t res;
  int result1 = s21_create_matrix(3, 2, &matrix_00);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  int result = s21_transpose(&matrix_00, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);

  s21_remove_matrix(&matrix_00);

  ck_assert_double_eq(res.matrix[0][0], 1.866);
  ck_assert_double_eq(res.matrix[0][1], 3e-5);
  ck_assert_double_eq(res.matrix[0][2], 0.0);
  ck_assert_double_eq(res.matrix[1][0], 24564);
  ck_assert_double_eq(res.matrix[1][1], 1e19);
  ck_assert_double_eq(res.matrix[1][2], 1.1234567);

  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_s21_trans_err) {
  matrix_t matrix_00;
  matrix_t res;
  int result1 = s21_create_matrix(0, 2, &matrix_00);

  int result = s21_transpose(&matrix_00, &res);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(result1, 1);

  s21_remove_matrix(&matrix_00);
}
END_TEST

START_TEST(test_s21_comp) {
  matrix_t matrix_00;
  matrix_t res;
  int result1 = s21_create_matrix(3, 3, &matrix_00);
  matrix_00.matrix[0][0] = 1;
  matrix_00.matrix[0][1] = 2;
  matrix_00.matrix[0][2] = 3;
  matrix_00.matrix[1][0] = 0;
  matrix_00.matrix[1][1] = 4;
  matrix_00.matrix[1][2] = 2;
  matrix_00.matrix[2][0] = 5;
  matrix_00.matrix[2][1] = 2;
  matrix_00.matrix[2][2] = 1;

  int result = s21_calc_complements(&matrix_00, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);

  s21_remove_matrix(&matrix_00);

  ck_assert_double_eq(res.matrix[0][0], 0);
  ck_assert_double_eq(res.matrix[0][1], 10);
  ck_assert_double_eq(res.matrix[0][2], -20);
  ck_assert_double_eq(res.matrix[1][0], 4);
  ck_assert_double_eq(res.matrix[1][1], -14);
  ck_assert_double_eq(res.matrix[1][2], 8);
  ck_assert_double_eq(res.matrix[2][0], -8);
  ck_assert_double_eq(res.matrix[2][1], -2);
  ck_assert_double_eq(res.matrix[2][2], 4);

  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_s21_det_01) {
  matrix_t matrix_00;
  double res = 0;
  int result1 = s21_create_matrix(1, 1, &matrix_00);
  matrix_00.matrix[0][0] = -0.456789e12;

  int result = s21_determinant(&matrix_00, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);

  s21_remove_matrix(&matrix_00);

  ck_assert_double_eq(res, -0.456789e12);
}
END_TEST

START_TEST(test_s21_det_02) {
  matrix_t matrix_00;
  double res = 0;
  int result1 = s21_create_matrix(4, 4, &matrix_00);
  matrix_00.matrix[0][0] = -4;
  matrix_00.matrix[0][1] = -2;
  matrix_00.matrix[0][2] = -7;
  matrix_00.matrix[0][3] = 8;
  matrix_00.matrix[1][0] = 2;
  matrix_00.matrix[1][1] = 7;
  matrix_00.matrix[1][2] = 4;
  matrix_00.matrix[1][3] = 9;
  matrix_00.matrix[2][0] = 2;
  matrix_00.matrix[2][1] = 0;
  matrix_00.matrix[2][2] = 6;
  matrix_00.matrix[2][3] = -3;
  matrix_00.matrix[3][0] = 6;
  matrix_00.matrix[3][1] = 4;
  matrix_00.matrix[3][2] = -10;
  matrix_00.matrix[3][3] = -4;

  int result = s21_determinant(&matrix_00, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);

  s21_remove_matrix(&matrix_00);

  ck_assert_double_eq(res, -1926);
}
END_TEST

START_TEST(test_s21_inv) {
  matrix_t matrix_00;
  matrix_t res;
  int result1 = s21_create_matrix(3, 3, &matrix_00);
  matrix_00.matrix[0][0] = 2;
  matrix_00.matrix[0][1] = 5;
  matrix_00.matrix[0][2] = 7;
  matrix_00.matrix[1][0] = 6;
  matrix_00.matrix[1][1] = 3;
  matrix_00.matrix[1][2] = 4;
  matrix_00.matrix[2][0] = 5;
  matrix_00.matrix[2][1] = -2;
  matrix_00.matrix[2][2] = -3;

  int result = s21_inverse_matrix(&matrix_00, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);

  s21_remove_matrix(&matrix_00);

  ck_assert_double_eq(res.matrix[0][0], 1);
  ck_assert_double_eq(res.matrix[0][1], -1);
  ck_assert_double_eq(res.matrix[0][2], 1);
  ck_assert_double_eq(res.matrix[1][0], -38);
  ck_assert_double_eq(res.matrix[1][1], 41);
  ck_assert_double_eq(res.matrix[1][2], -34);
  ck_assert_double_eq(res.matrix[2][0], 27);
  ck_assert_double_eq(res.matrix[2][1], -29);
  ck_assert_double_eq(res.matrix[2][2], 24);

  s21_remove_matrix(&res);
}
END_TEST

START_TEST(test_s21_inv_err) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;
  int result1 = s21_create_matrix(3, 3, &matrix_00);
  int result2 = s21_create_matrix(2, 3, &matrix_01);

  matrix_00.matrix[0][0] = 1;
  matrix_00.matrix[0][1] = 2;
  matrix_00.matrix[0][2] = 3;
  matrix_00.matrix[1][0] = 4;
  matrix_00.matrix[1][1] = 5;
  matrix_00.matrix[1][2] = 6;
  matrix_00.matrix[2][0] = 7;
  matrix_00.matrix[2][1] = 8;
  matrix_00.matrix[2][2] = 9;

  int result = s21_inverse_matrix(&matrix_00, &res);
  int result3 = s21_inverse_matrix(&matrix_01, &res);

  ck_assert_int_eq(result, 2);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);
  ck_assert_int_eq(result3, 2);

  s21_remove_matrix(&matrix_00);
}
END_TEST

int main() {
  int number_failed = 0;
  Suite *s = suite_create("s21_matrix");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s);

  tcase_add_test(tc_core, test_s21_eq);
  tcase_add_test(tc_core, test_s21_eq_err);
  tcase_add_test(tc_core, test_s21_sum);
  tcase_add_test(tc_core, test_s21_sum_err);
  tcase_add_test(tc_core, test_s21_sub);
  tcase_add_test(tc_core, test_s21_sub_err);
  tcase_add_test(tc_core, test_s21_mul_num);
  tcase_add_test(tc_core, test_s21_mul_num_err);
  tcase_add_test(tc_core, test_s21_mul_mat);
  tcase_add_test(tc_core, test_s21_mul_mat_err);
  tcase_add_test(tc_core, test_s21_trans);
  tcase_add_test(tc_core, test_s21_trans_err);
  tcase_add_test(tc_core, test_s21_comp);
  tcase_add_test(tc_core, test_s21_det_01);
  tcase_add_test(tc_core, test_s21_det_02);
  tcase_add_test(tc_core, test_s21_inv);
  tcase_add_test(tc_core, test_s21_inv_err);

  suite_add_tcase(s, tc_core);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
