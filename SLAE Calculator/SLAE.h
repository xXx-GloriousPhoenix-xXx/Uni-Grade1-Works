#ifndef PROJECTS_SLAE_H
#define PROJECTS_SLAE_H

#include <stdio.h>
#include <stdbool.h>

#include <windows.h>
#include <locale.h>
#include <wchar.h>

double* get_double_array (int size);
double** get_double_matrix (int size);

bool is_solvable_matrix (double** matrix, int size);
void fill_double_array (double* array, int size);
void fill_double_matrix (double** matrix, int size);
void randomize_double_array (double* array, int size);
void randomize_double_matrix (double** matrix, int size);
void print_array (double* array, int size, int precision);
void print_inlet_matrix (double** matrix, double* array, int size);
void delete_double_matrix (double** matrix, int size);
double* get_solution (double** matrix, double* array, int size, int precision);

void limitation_message (void);

#endif //PROJECTS_SLAE_H
