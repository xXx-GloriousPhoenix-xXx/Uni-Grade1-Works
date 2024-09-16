#ifndef PROJECTS_FILE_OPERATIONS_H
#define PROJECTS_FILE_OPERATIONS_H

#include "libs.h"

int create_File (void);
int read_File (void);
int delete_File (void);

int create_Record (void);
int read_Record (void);
int edit_Record (void);

int arrange_Records (int* sort_array);
int insert_Record (const int* sort_records);
int delete_Record (void);

void show_Info (void);
int show_Files (void);
void leave(void);

#endif //PROJECTS_FILE_OPERATIONS_H