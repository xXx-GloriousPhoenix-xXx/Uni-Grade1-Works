#ifndef PROJECTS_GENERAL_FUNCTION_H
#define PROJECTS_GENERAL_FUNCTION_H

#include "libs.h"

wchar_t* get_wbuffer (int size);
char* get_buffer (int size);
int get_integer (int size, int min_val, int max_val);
bool get_bool (wchar_t* operation_1, wchar_t* operation_2);
char* get_string (int size);
void fill_endline (char* buffer, int size);
void replace_newendline (char* buffer, int size);
bool is_valid_symbol (char symbol);
char* get_integer_string (int size, int min_val, int max_val);
char* get_double_string (int size, double min_val, double max_val, int max_acc);

#endif //PROJECTS_GENERAL_FUNCTION_H
