#include "calc_engine.h"

// int main(void) {
//   char cstr[255] = "3/x";

// for(double i = -10; i <= 10; i++) {
//     char temp[255] = {0};
//     char new_arr[255] = {0};
//     int z = 0;
//     sprintf(temp, "%lf", i);
//     for(size_t i = 0; i < strlen(cstr); i++) {
//         if(cstr[i] == 'x') {
//             if(cstr[i - 1] >= '0' && cstr[i - 1] <= '9') {
//                 new_arr[z] = '*';
//                 z++;
//             }
//                 for(size_t y = 0; y < strlen(temp); y++) {
//                     new_arr[z] = temp[y];
//                     z++;
//                 }
//             if(cstr[i + 1] == '(' || (cstr[i + 1] >= '0' && cstr[i + 1] <= '9')) {
//                 new_arr[z] = '*';
//                 z++;
//             }
//         } else {
//             new_arr[z] = cstr[i];
//             z++;
//         }
//     }
//   clear_label(new_arr);
//   printf("cleared %s\n", new_arr);
//   postfix(new_arr);
//   printf("fixed %s\n", new_arr);
// }

// }

void deposit_cap(double *term, int *cap_indx, double *total_sum, double *bet,
                 double *added_buf, int *adds_indx, double *adds,
                 int *cuts_indx, double *cuts_buf, double *cuts,
                 double *adds_buf) {
  for (int i = 1; i <= *term; i++) {
    if (i % *cap_indx == 0) {
      *added_buf = *added_buf + (*total_sum * ((*bet / 100 / 365) * *cap_indx));
      *total_sum = *total_sum + (*total_sum * ((*bet / 100 / 365) * *cap_indx));
    }
    if (i % *adds_indx == 0 && i != *term) {
      *total_sum = *total_sum + *adds;
    }
    if (i % *cuts_indx == 0 && i != *term) {
      if (*total_sum >= *cuts) {
        *total_sum = *total_sum - *cuts;
        *cuts_buf = *cuts_buf + *cuts;
      } else {
        *total_sum = 0;
        *cuts_buf = 0;
        *adds_buf = 0;
        break;
      }
    }
  }
}

void deposit(double *term, double *added, double *dep_sum, double *bet,
             double *total_sum, double *added_buf, double *adds,
             double *adds_buf, int *adds_indx, int *cuts_indx, double *cuts,
             double *cuts_buf) {
  for (int i = 1; i <= *term; i++) {
    if (i % 30 == 0) {
      *added = *dep_sum * (*bet / 100 / 12);
      *total_sum = *total_sum + *added;
      *added_buf = *added_buf + *added;
    }
    if (i % *adds_indx == 0 && i != *term) {
      *dep_sum = *dep_sum + *adds;
      *adds_buf = *adds_buf + *adds;
    }
    if (i % *cuts_indx == 0 && i != *term) {
      if (*dep_sum >= *cuts) {
        *dep_sum = *dep_sum - *cuts;
        *cuts_buf = *cuts_buf + *cuts;
      } else {
        *total_sum = 0;
        *cuts_buf = 0;
        *adds_buf = 0;
        break;
      }
    }
  }
}

void df_credit(double *min_pay, double *total_payment, double *Q, double *S,
               double *payed, double *min, double *max, double *Y, double *over,
               double *bet, double *per_month) {
  for (int i = 0; i < *total_payment; i++) {
    *Q = *Y - (*min_pay * i);
    *S = *Q * *bet / 12 / 100;
    *payed += *min_pay + *S;
    if (*max < (*min_pay + *S)) *max = *min_pay + *S;
    if (*min > (*min_pay + *S)) *min = *min_pay + *S;
  }
  *per_month = *payed / *total_payment;
  *over = *payed - *Y;
}

void an_credit(double *coef, double *m, double *total_payment,
               double *per_month, double *sum, double *over, double *bet,
               double *cr) {
  *m = (*bet / 12) * 0.01;
  *coef = *m * pow((1 + *m), *total_payment);
  *coef = *coef / (pow(1 + *m, *total_payment) - 1);
  *per_month = *cr * *coef;
  *sum = *per_month * *total_payment;
  *over = *sum - *cr;
}

void calculation(char *label) {
  int err = 0;

  err = clear_label(label);
  err = check_for_correct_actions(label);
  if (err == 0) {
    postfix(label);
    if (err == 0) {
      get_answer(label);
    }
  }
  if (strcmp(label, "end") == 0) strcpy(label, "0");
  if (strcmp(label, "nan") == 0) strcpy(label, "ERROR");
}

t_stack *create_node(char *set_action) {
  t_stack *node = (t_stack *)malloc(sizeof(t_stack));
  strcpy(node->action, set_action);
  node->next = NULL;
  return node;
}

int dblen(double a) {
  int len = 0;
  char temp[2000] = {0};
  sprintf(temp, "%lf", a);
  len = strlen(temp);
  memset(temp, 0, 2000);
  return len;
}

int check_for_correct_actions(char *label) {
  char temp[255] = {0};
  int z = 0, err = 0, val = -1, dg = 0, ac = 0;
  for (size_t i = 0; i < strlen(label); i++) {
    if (is_digit(label, i) == false) {
      temp[z] = label[i];
      z++;
    }
    if ((is_simple_action(temp[0]) == true ||
         is_simple_action(label[i + 1]) == true ||
         is_digit(label, i + 1) == true) &&
        z > 0) {
      val = get_priority_value(temp);
      if (val == 0) {
        err = 1;
        break;
      }
      memset(temp, 0, 255);
      z = 0;
      if (is_simple_action(label[i]) == true && label[i] != '(' &&
          label[i] != ')' && label[i] != '%')
        ac++;
    }
    if (is_digit(label, i) == true && is_digit(label, i + 1) == false) dg++;
  }
  if (dg < 1 || dg <= ac) err = 1;
  if (err == 1) strcpy(label, "ERROR");
  return err;
}

int clear_label(char *label) {
  char temp[255] = {0};
  int err = 0, z = 0;
  for (size_t i = 0; i < strlen(label); i++) {
    if (label[i] == '.' && label[i + 1] == '.') {
      err = 1;
      break;
    }
    if (label[i] != ' ') {
      temp[z] = label[i];
      z++;
    }
  }
  if (err == 0) {
    strcpy(label, temp);
    swap_uno(label);
  } else
    strcpy(label, "ERROR");
  return err;
}

void swap_uno(char *label) {
  char temp[255] = {0};
  int z = 0;
  for (size_t i = 0; i < strlen(label); i++) {
    if (label[i] == '-' && is_digit(label, i) == true &&
        is_digit(label, i + 1) == false) {
      strcat(temp, "(-1)*");
      z += 5;
    } else {
      temp[z] = label[i];
      z++;
    }
  }
  strcpy(label, temp);
}

void get_answer(char *label) {
  t_stack *stack = create_node("end");
  double buf1 = 0, buf2 = 0;
  char temp[255] = {0};
  char action_buffer[255] = {0};
  int z = 0, y = 0, err = 0;
  for (size_t i = 0; i < strlen(label); i++) {
    if (is_digit(label, i) == true) {
      temp[z] = label[i];
      z++;
    }
    if (is_digit(label, i) == false && is_digit(label, i - 1) == true) {
      push_front_stack(&stack, temp);
      memset(temp, 0, 255);
      z = 0;
    }
    if (is_digit(label, i) == false && label[i] != ' ') {
      get_action(action_buffer, label, &i, &y);
    }
    if (action_buffer[strlen(action_buffer) - 1] == ' ') {
      action_buffer[strlen(action_buffer) - 1] = 0;
      if (get_priority_value(action_buffer) > 3) {
        buf2 = atof(stack->action);
        err = apply_function(&buf2, action_buffer);
        if (err == 1) {
          sprintf(stack->action, "%s", "ERROR");
          break;
        }
        sprintf(stack->action, "%lf", buf2);
        memset(action_buffer, 0, 255);
        y = 0;
      } else {
        buf2 = atof(stack->action);
        del_stack_element(&stack);
        buf1 = atof(stack->action);
        err = apply_action(&buf1, buf2, action_buffer);
        if (err == 1) {
          sprintf(stack->action, "%s", "ERROR");
          break;
        }
        sprintf(stack->action, "%lf", buf1);
        memset(action_buffer, 0, 255);
        y = 0;
      }
    }
  }
  strcpy(label, stack->action);
  killstack(stack);
}

int apply_function(double *buf2, char *act) {
  int err = 0;
  if (strcmp(act, "sin") == 0) {
    *buf2 = sin(*buf2);
  }
  if (strcmp(act, "cos") == 0) {
    *buf2 = cos(*buf2);
  }
  if (strcmp(act, "tan") == 0) {
    *buf2 = tan(*buf2);
  }
  if (strcmp(act, "asin") == 0) {
    if (*buf2 <= 1.0 && *buf2 >= -1.0)
      *buf2 = asin(*buf2);
    else
      err = 1;
  }
  if (strcmp(act, "acos") == 0) {
    if (*buf2 <= 1 && *buf2 >= -1)
      *buf2 = acos(*buf2);
    else
      err = 1;
  }
  if (strcmp(act, "atan") == 0) {
    *buf2 = atan(*buf2);
  }
  if (strcmp(act, "sqrt") == 0) {
    if (*buf2 < 0)
      err = 1;
    else
      *buf2 = sqrt(*buf2);
  }
  if (strcmp(act, "ln") == 0) {
    if (*buf2 <= 0)
      err = 1;
    else
      *buf2 = log(*buf2);
  }
  if (strcmp(act, "log") == 0) {
    if (*buf2 <= 0)
      err = 1;
    else
      *buf2 = log10(*buf2);
  }
  if (strchr(act, '%') != NULL) {
    *buf2 = *buf2 * 0.01;
  }
  if (dblen(*buf2) > 255) err = 1;
  if (*buf2 == s21_inf || *buf2 == -(s21_inf) || *buf2 == s21_nan ||
      *buf2 == -(s21_nan))
    err = 1;
  return err;
}

int apply_action(double *buf1, double buf2, char *act) {
  int err = 0;
  if (strcmp(act, "+") == 0) {
    *buf1 = *buf1 + buf2;
  }
  if (strcmp(act, "-") == 0) {
    *buf1 = *buf1 - buf2;
  }
  if (strcmp(act, "*") == 0) {
    *buf1 = *buf1 * buf2;
  }
  if (strcmp(act, "/") == 0) {
    if (buf2 == 0)
      err = 1;
    else
      *buf1 = *buf1 / buf2;
  }
  if (strcmp(act, "^") == 0) {
    *buf1 = pow(*buf1, buf2);
  }
  if (strcmp(act, "mod") == 0) {
    if (buf2 < 1 && buf2 > -1)
      err = 1;
    else
      *buf1 = (int)*buf1 % (int)buf2;
  }
  if (dblen(*buf1) > 255) err = 1;
  return err;
}

void push_front_stack(t_stack **stack, char *set_action) {
  t_stack *new_element = create_node(set_action);
  new_element->next = *stack;
  *stack = new_element;
}

void del_stack_element(t_stack **stack) {
  t_stack *temp = *stack;
  *stack = (*stack)->next;
  free(temp);
}

void killstack(t_stack *stack) {
  t_stack *temp;
  while (stack) {
    temp = stack;
    stack = stack->next;
    free(temp);
  }
}

bool is_digit(char *c, int i) {
  bool res = false;
  if ((c[i] >= '0' && c[i] <= '9') || c[i] == '.') res = true;
  if ((c[i] == '-' && c[i - 1] == '(') || (c[i] == '-' && i == 0)) res = true;
  // if (c[i] == '-' && c[i - 1] == ' ' && (c[i + 1] >= '0' && c[i + 1] <= '9'))
  //   res = true;
  if(c[i] == '-' && (c[i - 1] < '0' || c[i - 1] > '9') && (c[i + 1] >= '0' && c[i + 1] <= '9')) res = true;
  return res;
}

void postfix(char *label) {
  t_stack *stack = create_node("end");
  char exit[255] = {0};
  char action_buffer[255] = {0};
  int arr_counter_exit = 0, current_block = 0;

  for (size_t i = 0; i < strlen(label); i++) {
    if (is_digit(label, i) == true) {
      add_digit(label, exit, &i, &arr_counter_exit);
    } else {
      get_action(action_buffer, label, &i, &current_block);
      if (action_buffer[strlen(action_buffer) - 1] == ' ') {
        action_buffer[strlen(action_buffer) - 1] = 0;
        if (is_less_or_equal_priority(&stack, action_buffer) == true) {
          while (is_less_or_equal_priority(&stack, action_buffer) == true) {
            if (strcmp(stack->action, "(") == 0) break;
            translate_action_to_exit(&stack, exit, &arr_counter_exit);
            del_stack_element(&stack);
          }
        }
        if (strcmp(action_buffer, ")") == 0) {
          while (strcmp(stack->action, "(") != 0) {
            translate_action_to_exit(&stack, exit, &arr_counter_exit);
            del_stack_element(&stack);
          }
          del_stack_element(&stack);
          current_block = 0;
          memset(action_buffer, 0, 255);
        } else {
          push_front_stack(&stack, action_buffer);
          current_block = 0;
          memset(action_buffer, 0, 255);
        }
      }
    }
  }

  while (stack != NULL) {
    if (strcmp(stack->action, "end") != 0) {
      strcat(exit, stack->action);
      strcat(exit, " ");
    }
    del_stack_element(&stack);
  }

  strcpy(label, exit);
  killstack(stack);
}

void translate_action_to_exit(t_stack **stack, char *exit,
                              int *arr_counter_exit) {
  strcat(exit, (*stack)->action);
  strcat(exit, " ");
  *arr_counter_exit = strlen(exit);
}

bool is_less_or_equal_priority(t_stack **stack, char *action_buffer) {
  bool res = false;
  if (strcmp((*stack)->action, "end") == 0)
    res = false;
  else {
    if (get_priority_value((*stack)->action) <
        get_priority_value(action_buffer))
      res = false;
    else if (get_priority_value((*stack)->action) >=
             get_priority_value(action_buffer))
      res = true;
  }
  if (strcmp((*stack)->action, "(") == 0 || strcmp(action_buffer, "(") == 0)
    res = false;
  if (strcmp((*stack)->action, ")") == 0 || strcmp(action_buffer, ")") == 0)
    res = false;
  if (get_priority_value((*stack)->action) == 3 &&
      get_priority_value(action_buffer) == 3)
    res = false;
  return res;
}

int get_priority_value(char *action_buffer) {
  int res = 0;
  if (strcmp(action_buffer, "+") == 0) res = 1;
  if (strcmp(action_buffer, "-") == 0) res = 1;
  if (strcmp(action_buffer, "*") == 0) res = 2;
  if (strcmp(action_buffer, "/") == 0) res = 2;
  if (strcmp(action_buffer, "mod") == 0) res = 2;
  if (strcmp(action_buffer, "^") == 0) res = 3;
  if (strchr(action_buffer, '%') != NULL) res = 4;
  if (strcmp(action_buffer, "sin") == 0) res = 4;
  if (strcmp(action_buffer, "cos") == 0) res = 4;
  if (strcmp(action_buffer, "tan") == 0) res = 4;
  if (strcmp(action_buffer, "asin") == 0) res = 4;
  if (strcmp(action_buffer, "acos") == 0) res = 4;
  if (strcmp(action_buffer, "atan") == 0) res = 4;
  if (strcmp(action_buffer, "sqrt") == 0) res = 4;
  if (strcmp(action_buffer, "ln") == 0) res = 4;
  if (strcmp(action_buffer, "log") == 0) res = 4;
  if (strcmp(action_buffer, "(") == 0) res = 5;
  if (strcmp(action_buffer, ")") == 0) res = 5;
  return res;
}

bool is_simple_action(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' ||
                 c == '(' || c == ')'
             ? true
             : false;
}

void get_action(char *action_buffer, char *label, size_t *i,
                int *current_block) {
  action_buffer[*current_block] = label[*i];
  *current_block = *current_block + 1;
  if (is_simple_action(label[*i]) == true ||
      is_simple_action(label[*i + 1]) == true ||
      get_priority_value(action_buffer) != 0) {
    action_buffer[*current_block] = ' ';
    *current_block = *current_block + 1;
  }
}

void add_digit(char *label, char *str, size_t *i, int *counter) {
  str[*counter] = label[*i];
  *counter = *counter + 1;
  if (is_digit(label, *i + 1) == false) {
    str[*counter] = ' ';
    *counter = *counter + 1;
  }
}
