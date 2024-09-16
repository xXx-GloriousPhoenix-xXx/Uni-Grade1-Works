#ifndef PROJECTS_N_ROOT_H
#define PROJECTS_N_ROOT_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ARGUMENT_BUFFER_SIZE 9 //1000000 (7 symbols), -1000000 (8 symbols) (+1 for overflow checking)
#define ARGUMENT_MAX_VALUE 1e+6
#define ARGUMENT_MIN_VALUE (-1e+6)

#define POWER_BUFFER_SIZE 5 //100 (3 symbols), -100 (4 symbols) (+1 for overflow checking)
#define POWER_MAX_VALUE 100
#define POWER_MIN_VALUE (-100)

#define PRECISION_BUFFER_SIZE 9 //0.1 (3 symbols), 0.000001 (8 symbols) (+1 for overflow checking)
#define PRECISION_MAX_INT_VALUE 6
#define PRECISION_MIN_INT_VALUE 1
#define PRECISION_MAX_FLOAT_VALUE 1e-1
#define PRECISION_MIN_FLOAT_VALUE 1e-6

#define STATEMENT_BUFFER_SIZE 2 //1 (1 symbol), 0 (1 symbol) (+1 for overflow checking)

double get_root(double argument, int power, double precision) {
    bool negative_case = false;
    if (argument == 0) return 0;
    if (power < 0) {
        argument = 1.0f/argument;
        power = -power;
    }
    if (argument < 0) {
        negative_case = true;
        argument = -argument;
    }
    double delta = 1;
    double value = 1;
    while (fabs(delta) >= precision) {
        delta = (argument / pow(value, (power - 1)) - value) / (double)power;
        value += delta;
    }
    return negative_case ? -value : value;
}
double get_argument(int buffer_size) {
    char buffer[buffer_size];
    char *symbols_in_buffer_pointer;
    double temporary_number_value = 0;
    bool is_valid = false;
    do {
        for (int i = 0; i < buffer_size; i++) {
            buffer[i] = '\0';
        }
        printf("Enter the argument (x):\n");
        fgets(buffer, buffer_size + 1, stdin);
        fflush(stdin);
        if (buffer[buffer_size - 1] != '\0' && buffer[buffer_size - 1] != '\n') {
            printf("Buffer overflow!\n");
            is_valid = false;
        } else {
            temporary_number_value = strtod(buffer, &symbols_in_buffer_pointer);
            if (*symbols_in_buffer_pointer != '\n' && *symbols_in_buffer_pointer != '\0') {
                printf("Invalid input!\n");
                is_valid = false;
            } else {
                if (temporary_number_value > ARGUMENT_MAX_VALUE) {
                    printf("Entered argument is greater than maximal value!\n");
                    is_valid = false;
                } else if (temporary_number_value < ARGUMENT_MIN_VALUE) {
                    printf("Entered argument is less than minimal value!\n");
                    is_valid = false;
                } else {
                    is_valid = true;
                }
            }
        }
    } while (!is_valid);
    return temporary_number_value;
}
int get_power(int buffer_size, double argument, bool *undefined_value_case) {
    char buffer[buffer_size];
    char *symbols_in_buffer_pointer;
    int temporary_number_value = 0;
    bool is_valid = false;
    do {
        for (int i = 0; i < buffer_size; i++) {
            buffer[i] = '\0';
        }
        printf("Enter the power (k):\n");
        fgets(buffer, buffer_size + 1, stdin);
        fflush(stdin);
        if (buffer[buffer_size - 1] != '\0' && buffer[buffer_size - 1] != '\n') {
            printf("Buffer overflow!\n");
            is_valid = false;
        } else {
            temporary_number_value = strtol(buffer, &symbols_in_buffer_pointer,10);
            if (*symbols_in_buffer_pointer != '\n' && *symbols_in_buffer_pointer != '\0') {
                printf("Invalid input!\n");
                is_valid = false;
            } else {
                if (temporary_number_value > POWER_MAX_VALUE) {
                    printf("Entered power is greater than maximal value!\n");
                    is_valid = false;
                } else {
                    if (temporary_number_value < POWER_MIN_VALUE) {
                        printf("Entered power is less than minimal value!\n");
                        is_valid = false;
                    } else {
                        if (temporary_number_value == 0) {
                            printf("Impossible to find zero-power root!\n");
                            is_valid = false;
                            *undefined_value_case = true;
                            break;
                        } else {
                            if (temporary_number_value % 2 == 0 && argument < 0) {
                                printf("Even root of negative argument is complex!\n");
                                is_valid = false;
                                *undefined_value_case = true;
                                break;
                            } else {
                                if (temporary_number_value < 0 && argument == 0) {
                                    printf("Unable to find negative root of zero!\n");
                                    is_valid = false;
                                    *undefined_value_case = true;
                                    break;
                                } else {
                                    is_valid = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (!is_valid);
    return temporary_number_value;
}
double get_precision (int buffer_size) {
    char buffer[buffer_size];
    char *symbols_in_buffer_pointer;
    double temporary_number_value_float = 0.0f;
    int temporary_number_value_int = 0;
    bool is_valid = false;
    do {
        for (int i = 0; i < buffer_size; i++) {
            buffer[i] = '\0';
        }
        printf("Enter the precision (e):\n");
        fgets(buffer, buffer_size + 1, stdin);
        fflush(stdin);
        if (buffer[buffer_size - 1] != '\0' && buffer[buffer_size - 1] != '\n') {
            printf("Buffer overflow!\n");
            is_valid = false;
        } else {
            temporary_number_value_float = strtod(buffer, &symbols_in_buffer_pointer);
            if (*symbols_in_buffer_pointer != '\n' && *symbols_in_buffer_pointer != '\0' && *symbols_in_buffer_pointer != '.') {
                printf("Invalid input!\n");
                is_valid = false;
            } else {
                temporary_number_value_int = strtol(buffer, &symbols_in_buffer_pointer,10);
                if (*symbols_in_buffer_pointer == '\n' || *symbols_in_buffer_pointer == '\0') {
                    if (temporary_number_value_int > PRECISION_MAX_INT_VALUE) {
                        printf("Entered precision is greater than maximal value!\n");
                        is_valid = false;
                        continue;
                    } else
                        if (temporary_number_value_int < PRECISION_MIN_INT_VALUE) {
                            printf("Entered precision is less than minimal value!\n");
                            is_valid = false;
                            continue;
                        } else {
                            temporary_number_value_float = pow(0.1, temporary_number_value_int);
                        }

                }
                if (temporary_number_value_float > PRECISION_MAX_FLOAT_VALUE) {
                    printf("Entered precision is greater than maximal value!\n");
                    is_valid = false;
                } else
                    if (temporary_number_value_float < PRECISION_MIN_FLOAT_VALUE) {
                        printf("Entered precision is less than minimal value!\n");
                        is_valid = false;
                    } else {
                        is_valid = true;
                    }
            }
        }
    } while (!is_valid);
    return temporary_number_value_float;
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
        printf("Enter 1 to continue or 0 to exit\n(maximal length of input is 1 symbol):\n");
        fgets(buffer, buffer_size + 1, stdin);
        fflush(stdin);
        if (buffer[buffer_size - 1] != '\0' && buffer[buffer_size - 1] != '\n') {
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
                        temporary_number_value = false;
                        is_valid = false;
                    }
                }
            }
        }
    } while (!is_valid);
    return temporary_number_value;
}
void limitation_message() {
    printf("Argument (x) must be a number between -1,000,000 and 1,000,000\nMaximal length of inputs is 8 symbols\n");
    printf("Power (k) must be an integer between -100 and 100\nMaximal length of inputs is 4 symbols\n");
    printf("Precision (e) must be a float number between 0.1 and 0.000001 (1e-6) or integer number between 1 and 6\nMaximal length of inputs is 8 symbols\n");
}

#endif