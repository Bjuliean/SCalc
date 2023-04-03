#ifndef CALC_ENGINE_H
#define CALC_ENGINE_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s21_inf 1.0 / 0.0
#define s21_nan 0.0 / 0.0

typedef struct s_stack {
  char action[255];
  struct s_stack *next;
} t_stack;

#define RAD_TO_DEG 57.3

void postfix(char *label);
void push_front_stack(t_stack **stack, char *set_action);
void killstack(t_stack *stack);
void del_stack_element(t_stack **stack);
bool is_digit(char *c, int i);
void add_digit(char *label, char *str, size_t *i, int *counter);
void get_action(char *action_buffer, char *label, size_t *i,
                int *current_block);
int get_priority_value(char *action_buffer);
bool is_simple_action(char c);
bool is_less_or_equal_priority(t_stack **stack, char *action_buffer);
void translate_action_to_exit(t_stack **stack, char *exit,
                              int *arr_counter_exit);
void get_answer(char *label);
int apply_action(double *buf1, double buf2, char *act);
int apply_function(double *buf2, char *act);
int clear_label(char *label);
void swap_uno(char *label);
int check_for_correct_actions(char *label);
t_stack *create_node(char *set_action);
void calculation(char *label);
int dblen(double a);
void an_credit(double *coef, double *m, double *total_payment,
               double *per_month, double *sum, double *over, double *bet,
               double *cr);
void df_credit(double *min_pay, double *total_payment, double *Q, double *S,
               double *payed, double *min, double *max, double *Y, double *over,
               double *bet, double *per_month);
void deposit(double *term, double *added, double *dep_sum, double *bet,
             double *total_sum, double *added_buf, double *adds,
             double *adds_buf, int *adds_indx, int *cuts_indx, double *cuts,
             double *cuts_buf);
void deposit_cap(double *term, int *cap_indx, double *total_sum, double *bet,
                 double *added_buf, int *adds_indx, double *adds,
                 int *cuts_indx, double *cuts_buf, double *cuts,
                 double *adds_buf);
#endif  // CALC_ENGINE_H