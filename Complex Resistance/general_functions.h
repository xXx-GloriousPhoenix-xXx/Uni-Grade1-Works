#ifndef PROJECTS_GENERAL_FUNCTION_H
#define PROJECTS_GENERAL_FUNCTION_H

#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <windows.h>

#include <math.h>

#define FREQUENCY_BUFFER_SIZE 16 //999.999999999
#define FREQUENCY_MIN_VAL 0.000000001
#define FREQUENCY_MAX_VAL 1000
#define FREQUENCY_MAX_ACC 9

#define FREQUENCY_STEP_MIN_VAL 0.000000001
#define FREQUENCY_STEP_MAX_VAL 1000

#define RESISTANCE_BUFFER_SIZE 16 //999.999999999
#define RESISTANCE_MIN_VAL 0.000000001
#define RESISTANCE_MAX_VAL 1000
#define RESISTANCE_MAX_ACC 9

#define INDUCTANCE_BUFFER_SIZE 16 //999.999999999
#define INDUCTANCE_MIN_VAL 0.000000001
#define INDUCTANCE_MAX_VAL 1000
#define INDUCTANCE_MAX_ACC 9

#define CAPACITY_BUFFER_SIZE 16 //999.999999999
#define CAPACITY_MIN_VAL 0.000000001
#define CAPACITY_MAX_VAL 1000
#define CAPACITY_MAX_ACC 9

#define FIRST_CIRCUIT 1
#define SECOND_CIRCUIT 2
#define THIRD_CIRCUIT 3
#define FOURTH_CIRCUIT 4
#define CIRCUIT_QUANTITY 4
#define CIRCUIT_BUFFER_SIZE 1

#define SOLUTION_SUCCESS 1
#define SOLUTION_ERROR 2

int get_integer (int, int, int);
double get_double (int, double, double, int);
bool get_bool (wchar_t* operation_1, wchar_t* operation_2);

#endif //PROJECTS_GENERAL_FUNCTION_H
