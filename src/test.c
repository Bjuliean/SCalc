#include <check.h>

#include "calc_engine.h"

START_TEST(test_plus) {
  char str[256] = "1.25+3.45";
  calculation(str);
  ck_assert_str_eq("4.700000", str);
}
END_TEST

START_TEST(test_minus) {
  char str[256] = "1.25-3.45";
  calculation(str);
  ck_assert_str_eq("-2.200000", str);
}
END_TEST

START_TEST(test_mult) {
  char str[256] = "1.25*3.45";
  calculation(str);
  ck_assert_str_eq("4.312500", str);
}
END_TEST

START_TEST(test_mult2) {
  char str[256] = "3*(4+7)";
  calculation(str);
  ck_assert_str_eq("33.000000", str);
}
END_TEST

START_TEST(test_div) {
  char str[256] = "1.25/3.45";
  calculation(str);
  ck_assert_str_eq("0.362319", str);
}
END_TEST

START_TEST(test_mod) {
  char str[256] = "1.25mod3.45";
  calculation(str);
  ck_assert_str_eq("1.000000", str);
}
END_TEST

START_TEST(test_pow) {
  char str[256] = "1.25^3.45";
  calculation(str);
  ck_assert_str_eq("2.159432", str);
}
END_TEST

START_TEST(test_brackets) {
  char str[256] = "(5.23+1.25)*(0.25+0.001)";
  calculation(str);
  ck_assert_str_eq("1.626480", str);
}
END_TEST

START_TEST(test_sin) {
  char str[256] = "sin((5.23+1.25)*(0.25+0.001))";
  calculation(str);
  ck_assert_str_eq("0.998450", str);
}
END_TEST

START_TEST(test_cos) {
  char str[256] = "cos((5.23+1.25)*(0.25+0.001))";
  calculation(str);
  ck_assert_str_eq("-0.055655", str);
}
END_TEST

START_TEST(test_tan) {
  char str[256] = "tan((5.23+1.25)*(0.25+0.001))";
  calculation(str);
  ck_assert_str_eq("-17.940020", str);
}
END_TEST

START_TEST(test_asin) {
  char str[256] = "asin(7/7.7)";
  calculation(str);
  ck_assert_str_eq("1.141097", str);
}
END_TEST

START_TEST(test_acos) {
  char str[256] = "acos(7/7.7)";
  calculation(str);
  ck_assert_str_eq("0.429699", str);
}
END_TEST

START_TEST(test_atan) {
  char str[256] = "atan(7/7.7)";
  calculation(str);
  ck_assert_str_eq("0.737815", str);
}
END_TEST

START_TEST(test_sqrt) {
  char str[256] = "sqrt(1357-245)";
  calculation(str);
  ck_assert_str_eq("33.346664", str);
}
END_TEST

START_TEST(test_ln) {
  char str[256] = "ln(1357-245)";
  calculation(str);
  ck_assert_str_eq("7.013915", str);
}
END_TEST

START_TEST(test_log) {
  char str[256] = "log(1357-245)";
  calculation(str);
  ck_assert_str_eq("3.046105", str);
}
END_TEST

START_TEST(test_combo) {
  char str[256] = "log(32+1)*7/11*432*(sin(2)*12-45+4)/2";
  calculation(str);
  ck_assert_str_eq("-6280.257908", str);
}
END_TEST

START_TEST(test_combo_func) {
  char str[256] = "cos(sin(tan(-0.005)))";
  calculation(str);
  ck_assert_str_eq("0.999988", str);
}
END_TEST

START_TEST(test_credit) {
  double sum = 0, per_month = 0, over = 0;
  double a = 0, b = 0, c = 18, d = 5, e = 700000;
  an_credit(&a, &b, &c, &per_month, &sum, &over, &d, &e);
  ck_assert_double_eq(ceil(sum), 728035);
  ck_assert_double_eq(ceil(per_month), 40447);
  ck_assert_double_eq(ceil(over), 28035);
}
END_TEST

START_TEST(test_credit2) {
  double min = 700000, max = 0, payed = 0, over = 0;
  double a = 700000 / 18, b = 18, c = 0, d = 0, e = 700000, f = 5, g = 0;
  df_credit(&a, &b, &c, &d, &payed, &min, &max, &e, &over, &f, &g);
  ck_assert_double_eq(min, 39050.1);
  ck_assert_double_eq(ceil(max), 41805);
  ck_assert_double_eq(ceil(payed), 727693);
  ck_assert_double_eq(ceil(over), 27693);
}
END_TEST

START_TEST(test_deposit) {
  double dep_sum = 700000, term = 24 * 30, bet = 8, total_sum = dep_sum;
  double added = 0, added_buf = 0, adds = 0, adds_buf = 0, cuts = 0,
         cuts_buf = 0;
  int adds_indx = 1, cuts_indx = 1;
  deposit(&term, &added, &dep_sum, &bet, &total_sum, &added_buf, &adds,
          &adds_buf, &adds_indx, &cuts_indx, &cuts, &cuts_buf);
  ck_assert_double_eq(ceil(added_buf), 112001);
  ck_assert_double_eq(ceil(total_sum), 812000);
}
END_TEST

START_TEST(test_deposit2) {
  double dep_sum = 700000, term = 24 * 30, bet = 8, total_sum = dep_sum;
  double added_buf = 0, adds = 0, adds_buf = 0, cuts = 0, cuts_buf = 0;
  int adds_indx = 1, cuts_indx = 1, cap_indx = 30;
  deposit_cap(&term, &cap_indx, &total_sum, &bet, &added_buf, &adds_indx, &adds,
              &cuts_indx, &cuts_buf, &cuts, &adds_buf);
  ck_assert_double_eq(ceil(added_buf), 119236);
  ck_assert_double_eq(ceil(total_sum), 819236);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_plus);
  tcase_add_test(tc1_1, test_minus);
  tcase_add_test(tc1_1, test_mult);
  tcase_add_test(tc1_1, test_mult2);
  tcase_add_test(tc1_1, test_div);
  tcase_add_test(tc1_1, test_mod);
  tcase_add_test(tc1_1, test_pow);
  tcase_add_test(tc1_1, test_brackets);
  tcase_add_test(tc1_1, test_sin);
  tcase_add_test(tc1_1, test_cos);
  tcase_add_test(tc1_1, test_tan);
  tcase_add_test(tc1_1, test_asin);
  tcase_add_test(tc1_1, test_acos);
  tcase_add_test(tc1_1, test_atan);
  tcase_add_test(tc1_1, test_sqrt);
  tcase_add_test(tc1_1, test_ln);
  tcase_add_test(tc1_1, test_log);
  tcase_add_test(tc1_1, test_combo);
  tcase_add_test(tc1_1, test_combo_func);
  tcase_add_test(tc1_1, test_credit);
  tcase_add_test(tc1_1, test_credit2);
  tcase_add_test(tc1_1, test_deposit);
  tcase_add_test(tc1_1, test_deposit2);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return (0);
}