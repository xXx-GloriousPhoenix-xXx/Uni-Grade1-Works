#ifndef PROJECTS_CALENDAR_H
#define PROJECTS_CALENDAR_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DATE_BUFFER_SIZE 11 //00-31 (2 symbols), 00-12 (2 symbols), 1-9999 (4), dots (2 symbols) (+1 for overflow checking)
#define STATEMENT_BUFFER_SIZE 2 //1/0 (1 symbol) (+1 for overflow checking)
#define MAX_YEAR 9999
#define MAX_MONTH 12

bool calculate_day_of_week(int day, int month, int year) {
    if (year < MAX_YEAR) {
        if (month <= MAX_MONTH) {
            int maximum_days = 0;
            switch (month) {
                case 1: {maximum_days = 31; break;}
                case 2: {maximum_days = (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))? 29 : 28); break;}
                case 3: {maximum_days = 31; break;}
                case 4: {maximum_days = 30; break;}
                case 5: {maximum_days = 31; break;}
                case 6: {maximum_days = 30; break;}
                case 7: {maximum_days = 31; break;}
                case 8: {maximum_days = 31; break;}
                case 9: {maximum_days = 30; break;}
                case 10: {maximum_days = 31; break;}
                case 11: {maximum_days = 30; break;}
                case 12: {maximum_days = 31; break;}
                default: {
                    printf("Non-exist month number. Must've been greater than 0 and less than 13!\n");
                    return false;
                    break;
                }
            }
            if (day > maximum_days) {
                printf("Last day of this month of this year is %d!\n", maximum_days);
                return false;
            } else {
                int bias;
                if (month > 2) {
                    bias = 0;
                } else {
                    if (!(year % 4)) {
                        bias = 1;
                    } else {
                        bias = 2;
                    }
                }
                int day_of_week = ((year * 1461 / 4) + (month * 3056 / 100) + day + bias) % 7;
                switch (day_of_week) {
                    case 0: {printf("It is Monday!\n"); break;}
                    case 1: {printf("It is Tuesday!\n"); break;}
                    case 2: {printf("It is Wednesday!\n"); break;}
                    case 3: {printf("It is Thursday!\n"); break;}
                    case 4: {printf("It is Friday!\n"); break;}
                    case 5: {printf("It is Saturday!\n"); break;}
                    case 6: {printf("It is Sunday!\n"); break;}
                    default: {
                        printf("Inappropriate day counting system. Must've been base7!\n");
                        return false;
                        break;
                    }
                }
                return true;
            }
        } else {
            printf("Month must be integer greater than 0 and less than 13!\n");
            return false;
        }
    } else {
        printf("Year must be integer greater than 0 and less than 10000!\n");
        return false;
    }

}
void get_date(int buffer_size, int* day, int* month, int* year) {
    char buffer[buffer_size];
    char* symbols_in_buffer_pointer;
    int temporary_number_value;
    bool is_valid = false;

    do {
        for (int i = 0; i < buffer_size; i++) {
            buffer[i] = '\0';
        }
        printf("Enter the date (example: dd.mm.yyyy):\n");
        fgets(buffer, buffer_size + 1, stdin);
        fflush(stdin);
        if (buffer[buffer_size - 1] != '\n' && buffer[buffer_size - 1] != '\0') {
            printf("Buffer overflow!\n");
            is_valid = false;
        } else {
            unsigned short dot_count = 0;
            bool is_numbers = true;
            for (int i = 0; i < buffer_size && buffer[i] != '\n' && buffer[i] != '\0';  i++) {

                if(buffer[i] == '.') dot_count++;
                else if(!('0' <= buffer[i] && buffer[i] <= '9')) {
                    is_numbers = false;
                    break;
                }
            }
            if (!is_numbers) {
                printf("Entered date contains symbols!\n");
                is_valid = false;
            } else {
                if (dot_count < 2) {
                    printf("Entered date is not complete!\n");
                    is_valid = false;
                } else {
                    if (dot_count > 2) {
                        printf("Entered date contain too many dots!\n");
                        is_valid = false;
                    } else {
                        int temp_index;
                        temporary_number_value = strtol(buffer, &symbols_in_buffer_pointer, 10);
                        if (*symbols_in_buffer_pointer == '.' && temporary_number_value > 0) {
                            *day = temporary_number_value;
                            temp_index = 0;
                            do {
                                buffer[temp_index++] = '0';
                            } while (buffer[temp_index] != '.' && temp_index < buffer_size - 1);
                            buffer[temp_index] = '0';
                            temporary_number_value = strtol(buffer, &symbols_in_buffer_pointer, 10);

                            if (*symbols_in_buffer_pointer == '.' && temporary_number_value > 0) {
                                *month = temporary_number_value;
                                temp_index = 0;
                                do {
                                    buffer[temp_index++] = '0';
                                } while (buffer[temp_index] != '.' && temp_index < buffer_size - 1);
                                buffer[temp_index] = '0';
                                temporary_number_value = strtol(buffer, &symbols_in_buffer_pointer, 10);

                                if ((*symbols_in_buffer_pointer == '\n' || *symbols_in_buffer_pointer == '\0') &&
                                    temporary_number_value > 0) {
                                    *year = temporary_number_value;
                                    is_valid = true;
                                } else {
                                    printf("Year is missing or equal to 0, but must be positive integer!\n");
                                    is_valid = false;
                                }
                            } else {
                                printf("Month must be positive integer!\n");
                                is_valid = false;
                            }
                        } else {
                            printf("Day must be positive integer!\n");
                            is_valid = false;
                        }
                    }
                }
            }
        }
    } while(!is_valid);
}
bool get_statement (int buffer_size) {
    char buffer[buffer_size];
    char *symbols_in_buffer_pointer;
    int temporary_number_value = true;
    bool is_valid = false;
    do {
        for (int i = 0; i < buffer_size; i++) {
            buffer[i] = '\0';
        }
        printf("Enter 1 to continue or 0 to exit:\n");
        fgets(buffer, buffer_size + 1, stdin);
        fflush(stdin);
        if (buffer[buffer_size - 1] != '\n' && buffer[buffer_size - 1] != '\0') {
            printf("Buffer overflow!\n");
            is_valid = false;
        } else {
            temporary_number_value = strtol(buffer, &symbols_in_buffer_pointer,10);
            if (*symbols_in_buffer_pointer != '\n' && *symbols_in_buffer_pointer != '\0') {
                printf("Invalid input!\n");
                is_valid = false;
            } else {
                if (temporary_number_value == 1) {
                    temporary_number_value = true;
                    is_valid = true;
                } else {
                    if (temporary_number_value == 0) {
                        temporary_number_value = false;
                        is_valid = true;
                    } else {
                        printf("Input is neither 1 nor 0!\n");
                        is_valid = false;
                    }
                }
            }
        }
    } while (!is_valid);
    return temporary_number_value;
}
void limitation_message() {
    printf("Input can only contain 15 symbols!\nMaximal year is 9999!\n");
}

#endif