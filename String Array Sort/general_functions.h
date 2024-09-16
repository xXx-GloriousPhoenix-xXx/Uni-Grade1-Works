#ifndef PROJECTS_GENERAL_FUCNTIONS_H
#define PROJECTS_GENERAL_FUCNTIONS_H

#include <stdbool.h>
#include <wchar.h>

#define QUANTITY_BUFFER_SIZE 3
#define QUANTITY_MINIMAL_VALUE 2
#define QUANTITY_MAXIMAL_VALUE 100

#define SIZE_BUFFER_SIZE 3
#define SIZE_MINIMAL_VALUE 1
#define SIZE_MAXIMAL_VALUE 100

int get_integer (int, int, int);
bool get_bool (wchar_t*, wchar_t*);

#endif //PROJECTS_GENERAL_FUCNTIONS_H
