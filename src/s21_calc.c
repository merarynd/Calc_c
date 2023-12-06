#include "s21_calc.h"

// int main() {
//   char *arr = "1.0 =";
//   int err = 0;
//   double x = 0.0;
//   double res = s21_smart_calc(arr, &err, x);
//   printf("%lf", res);
//   return 0;
// }

double s21_smart_calc(char *string, int *error, double number_x) {
  double res = 0.0;
  char exit[NMAX] = {0};
  validator(string, exit);
  *error = check(exit);
  if (*error == 0) {
    char polk[NMAX] = {0};
    notation(exit, polk);
    *error = schet(polk, &res, number_x);
  }
  return res;
}

void validator(char *str, char *exit) {
  int k = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
      exit[k++] = 'c';
      i += 2;
    } else if (str[i] == 's') {
      if (str[i + 1] == 'i' && str[i + 2] == 'n') {
        exit[k++] = 's';
        i += 2;
      } else if (str[i + 1] == 'q' && str[i + 2] == 'r' && str[i + 3] == 't') {
        exit[k++] = 'q';
        i += 3;
      }
    } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
      exit[k++] = 't';
      i += 2;
    } else if (str[i] == 'a') {
      if (str[i + 1] == 'c' && str[i + 2] == 'o' && str[i + 3] == 's') {
        exit[k++] = 'o';
        i += 3;
      } else if (str[i + 1] == 's' && str[i + 2] == 'i' && str[i + 3] == 'n') {
        exit[k++] = 'n';
        i += 3;
      } else if (str[i + 1] == 't' && str[i + 2] == 'a' && str[i + 3] == 'n') {
        exit[k++] = 'a';
        i += 3;
      }
    } else if (str[i] == 'l') {
      if (str[i + 1] == 'n') {
        exit[k++] = 'l';
        i++;
      } else if (str[i + 1] == 'o' && str[i + 2] == 'g') {
        exit[k++] = 'g';
      }
    } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
      exit[k++] = 'm';
      i += 2;
    } else if (i == 0 && str[i] == '-') {
      exit[k++] = '0';
      exit[k++] = '-';
    } else if (str[i] == '(' && str[i + 1] == '-') {
      exit[k++] = '(';
      exit[k++] = '0';
    } else if ((str[i] >= 48 && str[i] <= 56) &&
               (str[i + 1] == '(' || str[i + 1] == 'a' || str[i + 1] == 'c' ||
                str[i + 1] == 's' || str[i + 1] == 't' || str[i + 1] == 'm' ||
                str[i + 1] == 'l')) {
      exit[k++] = str[i];
      exit[k++] = '*';
    } else {
      exit[k++] = str[i];
    }
  }
}

int check(char *exit) {
  int flag = 2;
  int i = 0;
  while (exit[i] != '\0') {
    if ((exit[i] >= 48 && exit[i] <= 57) || exit[i] == 'x') {
      flag = 0;
    }
    if (exit[0] == ')') flag = 2;
    if ((exit[i] == 'c' || exit[i] == 'o' || exit[i] == 's' || exit[i] == 't' ||
         exit[i] == 'a' || exit[i] == 'n' || exit[i] == 'q' || exit[i] == 'l' ||
         exit[i] == 'g') &&
        exit[i + 1] == '(' && (exit[i + 2] == '\0' || exit[i + 2] == ')'))
      flag = 2;
    i++;
  }
  return flag;
}

struct stack *init(int size) {
  struct stack *s = malloc(sizeof(struct stack));
  if (s != NULL) {
    s->arr = malloc(size * sizeof(char));
    s->top = 0;
  }
  return s;
}

struct stack_chisla *init_schet(int size) {
  struct stack_chisla *s = malloc(sizeof(struct stack_chisla));
  if (s != NULL) {
    s->arr = malloc(size * sizeof(double));
    s->top = 0;
  }
  return s;
}

char pop(struct stack *s) {
  char elem_char = '0';
  if (s->top != 0) {
    elem_char = s->arr[s->top - 1];
    s->top--;
  }
  return elem_char;
}

double pop_schet(struct stack_chisla *s) {
  double elem_char = 0.0;
  if (s->top != 0) {
    elem_char = s->arr[s->top - 1];
    s->top--;
  }
  return elem_char;
}

void push(struct stack *s, char elem) {
  s->arr[s->top] = elem;
  s->top++;
}

double push_schet(struct stack_chisla *a, double elem) {
  a->arr[a->top] = elem;
  a->top++;
  return 0;
}

void cleaner(struct stack *s) {
  if (s != NULL) {
    if (s->arr != NULL) {
      free(s->arr);
      s->top = 0;
    }
    free(s);
  }
}

void cleaner_schet(struct stack_chisla *a) {
  if (a != NULL) {
    if (a->arr != NULL) {
      free(a->arr);
      a->top = 0;
    }
    free(a);
  }
}

char find(struct stack *s) {
  char flag = '0';
  if (s->top != 0) {
    flag = s->arr[s->top - 1];
  }
  return flag;
}

void notation(char *exit, char *polk) {
  struct stack *s = init(NMAX);
  int k = 0;
  for (int i = 0; exit[i] != '\0'; i++) {
    if (priority(exit[i]) == 0) {
      polk[k++] = exit[i];
      if (priority(exit[i + 1]) != 0) {
        polk[k++] = ' ';
      }
    } else if (priority(exit[i]) > 1 && priority(exit[i]) <= 4) {
      if (priority(find(s)) < priority(exit[i])) {
        push(s, exit[i]);
      } else if (priority(find(s)) >= priority(exit[i])) {
        while (priority(find(s)) >= priority(exit[i])) {
          polk[k++] = pop(s);
        }
        push(s, exit[i]);
      }
    } else if (exit[i] == 'x') {
      polk[k++] = exit[i];
    } else if (exit[i] == '(') {
      push(s, exit[i]);
    } else if (exit[i] == ')') {
      while (find(s) != '(') {
        polk[k++] = pop(s);
      }
      pop(s);
    }
  }
  while (s->top != 0) {
    polk[k++] = pop(s);
  }
  cleaner(s);
}

int priority(char a) {
  int res = 1;
  if ((a >= 48 && a <= 57) || a == 46) res = 0;
  if (a == '(' || a == ')') res = 1;
  if (a == '+' || a == '-') res = 2;
  if (a == '*' || a == '/' || a == 'm') res = 3;
  if (a == 'c' || a == 's' || a == 't' || a == 'g' || a == 'q' || a == 'l' ||
      a == '^' || a == 'a' || a == 'o' || a == 'n')
    res = 4;
  return res;
}

int schet(const char *polk, double *res, double number_x) {
  int flag = 0;
  struct stack_chisla *a = init_schet(NMAX);
  for (int i = 0; polk[i] != '\0'; i++) {
    if (polk[i] == 'x') push_schet(a, number_x);
    if ((polk[i] >= 48 && polk[i] <= 57) || polk[i] == 46) {
      char num[NMAX] = {'\0'};
      int k = 0;
      while (polk[i] != ' ') {
        num[k++] = polk[i++];
      }
      push_schet(a, atof(num));
    } else if (flag == 0 &&
               !((polk[i] == '-' || polk[i] == '*' || polk[i] == '/') &&
                 a->top == 1)) {
      flag = math_operations(polk, i, a);
    }
  }
  *res = pop_schet(a);
  cleaner_schet(a);
  return flag;
}

int math_operations(const char *polk, int i, struct stack_chisla *a) {
  int flag = 0;
  if (polk[i] == '+') push_schet(a, pop_schet(a) + pop_schet(a));
  if (polk[i] == '-') {
    double a1 = pop_schet(a);
    push_schet(a, pop_schet(a) - a1);
  }
  if (polk[i] == '*') push_schet(a, pop_schet(a) * pop_schet(a));
  if (polk[i] == '/') {
    double a1 = pop_schet(a);
    if (a1 != 0) {
      push_schet(a, pop_schet(a) / a1);
    } else {
      flag = 1;
    }
  }
  if (polk[i] == 'm') {
    double a1 = pop_schet(a);
    if (a->top == 0) {
      flag = 2;
    } else
      push_schet(a, fmodl(pop_schet(a), a1));
  }
  if (polk[i] == 't') push_schet(a, tan(pop_schet(a)));
  if (polk[i] == 'c') push_schet(a, cos(pop_schet(a)));
  if (polk[i] == 's') push_schet(a, sin(pop_schet(a)));
  if (polk[i] == 'o') push_schet(a, acos(pop_schet(a)));
  if (polk[i] == 'n') push_schet(a, asin(pop_schet(a)));
  if (polk[i] == 'a') push_schet(a, atan(pop_schet(a)));
  if (polk[i] == 'q') push_schet(a, sqrt(pop_schet(a)));
  if (polk[i] == 'l') push_schet(a, log(pop_schet(a)));
  if (polk[i] == 'g') push_schet(a, log10(pop_schet(a)));
  if (polk[i] == '^') {
    double a1 = pop_schet(a);
    if (a->top == 0) {
      flag = 2;
    } else
      push_schet(a, pow(pop_schet(a), a1));
  }
  return flag;
}