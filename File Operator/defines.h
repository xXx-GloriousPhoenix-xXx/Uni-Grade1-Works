#ifndef PROJECTS_DEFINES_H
#define PROJECTS_DEFINES_H

#include "libs.h"

//File size constants
#define FILE_NAME_SIZE 256
#define PROGRAM_EXTENSION ".txt"
#define PROGRAM_EXTENSION_SIZE 4
#define PROGRAM_PATH "../9.FileManager/Files/"
#define PROGRAM_PATH_SIZE 23
#define FOLDER_PATH "../9.FileManager/Files"
#define GENERAL_FILE_NAME_SIZE (PROGRAM_PATH_SIZE + FILE_NAME_SIZE + PROGRAM_EXTENSION_SIZE)

//Record size constants
#define COLUMN_QUANTITY 4
#define GAME_NAME_SIZE 75
#define RATE_SIZE 10 //Example "10.00 / 10"
#define CREATION_YEAR_SIZE 5
#define DEVELOPER_NAME_SIZE 50
#define RECORD_STEP_SIZE 5
#define GENERAL_RECORD_SIZE (GAME_NAME_SIZE + RATE_SIZE + CREATION_YEAR_SIZE + DEVELOPER_NAME_SIZE + 3 * RECORD_STEP_SIZE + 2)

//Record value constants
#define MIN_RATE 0.00
#define MAX_RATE 10.00
#define MAX_RATE_ACC 2
#define MIN_YEAR 1976 //First game "Colossal Cave Adventure" (1976)
#define MAX_YEAR 99999

//Record operating size constants
#define CHOICE_SIZE 1

//Record operating value constants
#define MIN_CHOICE 1
#define READ_MAX_CHOICE 2
#define EDIT_MAX_CHOICE 5
#define ARRANGE_MAX_CHOICE 4
#define ASCENDING_ARRANGEMENT 1
#define DESCENDING_ARRANGEMENT 2
#define MIN_LINE_VALUE 1

//Read choices
#define READ_SEPARATELY 1
#define READ_INTERVAL 2

//Edit choices
#define GAME_NAME 1
#define RATE 2
#define CREATION_YEAR 3
#define DEVELOPER_NAME 4
#define WHOLE_RECORD 5

//Record read constants
#define MIN_QUANTITY_OUTPUT 1
#define MIN_INT_VALUE 1

#define ROW_1 1
#define CREATE_FILE 1
#define READ_FILE 2
#define DELETE_FILE 3

#define ROW_2 2
#define CREATE_RECORD 1
#define READ_RECORD 2
#define EDIT_RECORD 3

#define ROW_3 3
#define ARRANGE_RECORDS 1
#define INSERT_RECORD 2
#define DELETE_RECORD 3

#define ROW_4 4
#define SHOW_FILES 1
#define QUIT 2
#define SHOW_INFO 3

//UI borders constants
#define ROW_QUANTITY 4
#define OPS_IN_ROW 3
#define TOP_BORDER 1
#define LEFT_BORDER 1
#define RIGHT_BORDER OPS_IN_ROW
#define BOTTOM_BORDER ROW_QUANTITY

//Operation cases
#define OPERATION_SUCCESS 0
#define OPERATION_ERROR 1
#define OPERATION_QUIT 2


#endif //PROJECTS_DEFINES_H