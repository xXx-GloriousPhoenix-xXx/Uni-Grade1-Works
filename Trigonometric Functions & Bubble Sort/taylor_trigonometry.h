#ifndef TAYLOR_TRIGONOMETRY_H
#define TAYLOR_TRIGONOMETRY_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define DOUBLE_BUFFER_SIZE 21
/* 1 symbol for minus
 * 19 symbols for digits
 * 1 symbol for point
 * example: -1000000.000000000000
 * */
#define DOUBLE_MAXIMAL_PRECISION 12
#define DOUBLE_MINIMAL_VALUE (-1080000)
#define DOUBLE_MAXIMAL_VALUE 1080000
#define STEP_MINIMAL_VALUE 0

#define INTEGER_BUFFER_SIZE 2
/*
 * 2 symbol for digit
 * example: 12
 * */
#define INTEGER_MINIMAL_VALUE 1
#define INTEGER_MAXIMAL_VALUE 12

#define ARGUMENT_BIAS 21
/* 1 symbol for minus
 * 19 symbols for digits
 * 1 symbol for point
 * example: -1000000.000000000000
 * */
#define GENERAL_BIAS 15
/* 1 symbol for minus
 * 13 symbols for digits
 * 1 symbol for point
 * example: -0.000000000000
 * */

void get_values (double, double, double, int, bool);
double get_sin (double, int);
double get_cos (double, int);
double get_period_value (double);
double get_radian (double);
void get_output (double, double, double, int);
void limitation_message();

int get_integer (int, int, int);
double get_double (int, double, double, int);
bool get_bool (char*, char*);

#endif //TAYLOR_TRIGONOMETRY_H
