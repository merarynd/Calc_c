#ifndef SRC_MODULE_INPUT_H_
#define SRC_MODULE_INPUT_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 256

struct stack {
  char *arr;
  int top;
};

struct stack_chisla {
  double *arr;
  int top;
};

double s21_smart_calc(char *string, int *error, double number_x);
void validator(char *str, char *exit);
void notation(char *exit, char *polk);
int check(char *exit);
int priority(char a);
int schet(const char *polk, double *res, double number_x);
int math_operations(const char *polk, int i, struct stack_chisla *a);

struct stack *init(int size);
char pop(struct stack *s);
void push(struct stack *s, char elem);
char find(struct stack *s);
void cleaner(struct stack *s);

struct stack_chisla *init_schet(int size);
double pop_schet(struct stack_chisla *a);
double push_schet(struct stack_chisla *a, double elem);
void cleaner_schet(struct stack_chisla *s);

#endif  // SRC_MODULE_INPUT_H_