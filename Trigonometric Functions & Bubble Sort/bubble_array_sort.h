#ifndef BUBBLE_ARRAY_H
#define BUBBLE_ARRAY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DOUBLE_BUFFER_SIZE 14
/* 1 symbol for minus
 * 13 symbols for digits
 * 1 symbol for point
 * */
#define DOUBLE_MAXIMAL_PRECISION 6
#define DOUBLE_MINIMAL_VALUE (-1000000)
#define DOUBLE_MAXIMAL_VALUE 1000000

#define INTEGER_BUFFER_SIZE 7
/* 1 symbol for minus
 * 6 symbols for digits
 * */
#define INTEGER_MINIMAL_VALUE 1
#define INTEGER_MAXIMAL_VALUE 1000000

void get_sorted (double*, int, bool);
void limitation_message();

int get_integer (int, int, int);
double get_double (int, double, double, int);
bool get_bool (char*, char*);

#endif //BUBBLE_ARRAY_H
