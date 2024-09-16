#ifndef PROJECTS_GENERAL_FUNCTIONS_H
#define PROJECTS_GENERAL_FUNCTIONS_H

#include <stdbool.h>
#include <wchar.h>
#include <locale.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_SIZE_BUFFER_SIZE 3
#define MATRIX_SIZE_MINIMAL_VALUE 2
#define MATRIX_SIZE_MAXIMAL_VALUE 100

#define COEFFICIENT_BUFFER_SIZE 4
#define COEFFICIENT_MINIMAL_VALUE (-100)
#define COEFFICIENT_MAXIMAL_VALUE 100
#define COEFFICIENT_MAXIMAL_PRECISION 6

#define PRECISION_BUFFER_SIZE 2
#define PRECISION_MINIMAL_VALUE 1
#define PRECISION_MAXIMAL_VALUE 12

int get_integer (int, int, int);
double get_double (int, double, double, int);
bool get_bool (wchar_t* operation_1, wchar_t* operation_2);

#endif //PROJECTS_GENERAL_FUNCTIONS_H
