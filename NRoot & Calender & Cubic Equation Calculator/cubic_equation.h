#ifndef PROJECTS_CUBIC_EQUATION_H
#define PROJECTS_CUBIC_EQUATION_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define COEFFICIENT_BUFFER_SIZE 6 //1000 (4 symbols), -1000 (5 symbols) (+1 for overflow checking)
#define STATEMENT_BUFFER_SIZE 2 //0-1 (1 symbol) (+1 for overflow checking)
#define MAX_COEFFICIENT_VALUE 1e+3
#define MIN_COEFFICIENT_VALUE (-1e+3)

bool get_statement (int buffer_size) {
    char buffer[buffer_size];
    char *symbols_in_buffer_pointer;
    int temporary_number_value = true;
    bool is_valid = false;
    do {
        for (int i = 0; i < buffer_size; buffer[i] = '\0', i++);
        printf("Enter 1 to continue or 0 to exit (maximal length of input is 1 symbol):\n");
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
int get_number (int buffer_size, char* text) {
    char buffer[buffer_size];
    char *symbols_in_buffer_pointer;
    int temporary_number_value = 0;
    bool is_valid = false;
    do {
        for (int i = 0; i < buffer_size; buffer[i] = '\0', i++);
        printf("Enter the coefficient %s:\n", text);
        fgets(buffer, buffer_size + 1, stdin);
        if (buffer[buffer_size - 1] != '\n' && buffer[buffer_size - 1] != '\0') {
            printf("Buffer overflow!\n");
        } else {
            temporary_number_value = strtol(buffer, &symbols_in_buffer_pointer,10);
            if (*symbols_in_buffer_pointer != '\n' && *symbols_in_buffer_pointer != '\0') {
                printf("Invalid input!\n");
            } else {
                if (temporary_number_value > MAX_COEFFICIENT_VALUE) {
                    printf("Entered power is greater than maximal value!\n");
                    is_valid = false;
                } else {
                    if (temporary_number_value < MIN_COEFFICIENT_VALUE) {
                        printf("Entered power is less than minimal value!\n");
                        is_valid = false;
                    } else {
                        is_valid = true;
                    }
                }
            }
        }
        fflush(stdin);
    } while (!is_valid);
    return temporary_number_value;
}
void get_solution (int a, int b, int c) {
    const int precision_digits = 2;
    double p = b - pow(a, 2) / 3.;
    double q = 2. * pow(a, 3) / 27. - (a * b) / 3. + c;
    double d = pow(p, 3) / 27. + pow(q, 2) / 4.;
    if (d >= 0) {
        double u = cbrt((q / -2.) + sqrt(d));
        double v = cbrt((q / -2.) - sqrt(d));
        double x1 = u + v - (a / 3.);
        double real = (u + v) / (-2.) - (a / 3.);
        double abs_imaginary = fabs(((u - v) * sqrt(3) / -2.));
        if (d == 0) {
            if (x1 == real) {
                if (real == -0) {
                    real = fabs(real);
                }
                printf("Solution 1, 2 and 3: %.*lf\n", precision_digits, real);
            } else {
                printf("Solution 1: %.3lf\n", x1);
                if (abs_imaginary == 0) {
                    printf("Solution 2, 3: %.*lf\n", precision_digits, real);
                } else {
                    printf("Solution 2, 3: %.*lf + %.*lfi\n", precision_digits, real, precision_digits, abs_imaginary);
                }
            }
        } else {
            printf("Solution 1: %.*lf\n", precision_digits, x1);
            if (real == 0 || fabs(real) < 1e-15) {
                printf("Solution 2: %.*lfi\n", precision_digits, abs_imaginary);
                printf("Solution 3: -%.*lfi\n", precision_digits, abs_imaginary);
            } else {
                printf("Solution 2: %.*lf + %.*lfi\n", precision_digits, real, precision_digits, abs_imaginary);
                printf("Solution 3: %.*lf - %.*lfi\n", precision_digits, real, precision_digits, abs_imaginary);
            }
        }
    } else {
        double radius = sqrt((-pow(p, 3) / 27.));
        double angle = acos((-q / (2. * radius)));
        double x1 = 2. * fabs(cbrt(radius)) * cos(angle / 3.) - (a / 3.);
        double x2 = 2. * fabs(cbrt(radius)) * cos((angle + 2. * M_PI) / 3.) - (a / 3.);
        double x3 = 2. * fabs(cbrt(radius)) * cos((angle + 4. * M_PI) / 3.) - (a / 3.);
        printf("Solution 1: %.*lf\n", precision_digits, x1);
        printf("Solution 2: %.*lf\n", precision_digits, x2);
        printf("Solution 3: %.*lf\n", precision_digits, x3);
    }
}
void limitation_message () {
    printf("Coefficient must be an integer between -1000 and 1000\nMaximal length of input is 5 symbols\nScientific notation is not supported\n");

}

#endif
