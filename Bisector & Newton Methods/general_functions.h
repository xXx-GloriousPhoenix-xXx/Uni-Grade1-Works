#ifndef PROJECTS_GENERAL_FUNCTIONS_H
#define PROJECTS_GENERAL_FUNCTIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>
#include <math.h>

#define T_BUFFER_SIZE 10 //-99.999999
#define T_MIN_VAL (-100)
#define T_MAX_VAL 100
#define T_MAX_ACC 6

#define BORDER_BUFFER_SIZE 11 //-999.999999
#define BORDER_MIN_VAL (-1000)
#define BORDER_MAX_VAL 1000
#define BORDER_MAX_ACC 6

#define EPS_BUFFER_SIZE 2
#define EPS_MIN_VAL 1
#define EPS_MAX_VAL 12

typedef struct Data {
    double t;
    double a;
    double b;
    int digits;
} data;

int get_integer (int size, int min_val, int max_val);
double get_double (int size, double min_val, double max_val, int max_acc);
bool get_bool (wchar_t* operation_1, wchar_t* operation_2);

#endif //PROJECTS_GENERAL_FUNCTIONS_H
