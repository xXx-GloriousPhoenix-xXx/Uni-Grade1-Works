#ifndef PROJECTS_STRING_SORT_H
#define PROJECTS_STRING_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>
#include <wchar.h>
#include <windows.h>

wchar_t** get_string_array (int size, int quantity, bool is_random);
wchar_t** get_sorted_string_array (wchar_t** array, int quantity, bool arrangement);

void print_array (const wchar_t** array, int size, int quantity);

void limitation_message ();

#endif //PROJECTS_STRING_SORT_H
