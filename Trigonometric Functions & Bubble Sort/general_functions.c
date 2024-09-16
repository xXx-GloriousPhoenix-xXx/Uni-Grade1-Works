#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_digit (char symbol) {
    return 47 < (int)symbol && (int)symbol < 58;
}
bool is_special_symbol (char symbol) {
    return (57 < (int)symbol && (int)symbol < 65) ||
           (32 < (int)symbol && (int)symbol < 48) ||
           (90 < (int)symbol && (int)symbol < 97) ||
           (122 < (int)symbol && (int)symbol < 127);
}
bool is_lowercase_symbol (char symbol) {
    return 96 < (int)symbol && (int)symbol < 123;
}
bool is_uppercase_symbol (char symbol) {
    return 64 < (int)symbol && (int)symbol < 91;
}

short get_short (int BUFFER_SIZE, short MINIMAL_VALUE, short MAXIMAL_VALUE) {//Scientific notation is not supported
    short number = 0;
    char *end_pointer;
    char buffer[BUFFER_SIZE + 1];
    bool is_valid = false;
    do {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = '\0';
        }
        fgets(buffer, BUFFER_SIZE + 1, stdin);
        fflush(stdin);
        number = (short)strtol(buffer, &end_pointer, 10);
        if (buffer[BUFFER_SIZE] == '\0' || buffer[BUFFER_SIZE] == '\n') {
            if ((*end_pointer == '\0' || *end_pointer == '\n') && buffer[0] != '\n') {
                if (MINIMAL_VALUE <= number && number <= MAXIMAL_VALUE) {
                    is_valid = true;
                } else {
                    printf("Number must be greater than %d and less than %d! Try entering something else.\n", MINIMAL_VALUE, MAXIMAL_VALUE);
                    is_valid = false;
                }
            } else {
                printf("Wrong Input! Try entering something else.\n");
                is_valid = false;
            }
        } else {
            printf("Buffer Overflow! Try entering something else.\n");
            is_valid = false;
        }
    } while (!is_valid);
    return number;
}
int get_integer (int BUFFER_SIZE, int MINIMAL_VALUE, int MAXIMAL_VALUE) {//Scientific notation is not supported
    int number = 0;
    char *end_pointer;
    char buffer[BUFFER_SIZE + 1];
    bool is_valid = false;
    do {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = '\0';
        }
        fgets(buffer, BUFFER_SIZE + 2, stdin);
        fflush(stdin);
        number = (int)strtol(buffer, &end_pointer, 10);
        if (buffer[BUFFER_SIZE] == '\0' || buffer[BUFFER_SIZE] == '\n') {
            if ((*end_pointer == '\0' || *end_pointer == '\n') && buffer[0] != '\n') {
                if (MINIMAL_VALUE <= number && number <= MAXIMAL_VALUE) {
                    is_valid = true;
                } else {
                    printf("Number must be greater than %d and less than %d! Try entering something else.\n", MINIMAL_VALUE, MAXIMAL_VALUE);
                    is_valid = false;
                }
            } else {
                printf("Wrong Input! Try entering something else.\n");
                is_valid = false;
            }
        } else {
            printf("Buffer Overflow! Try entering something else.\n");
            is_valid = false;
        }
    } while (!is_valid);
    return number;
}
long get_long (int BUFFER_SIZE, long MINIMAL_VALUE, long MAXIMAL_VALUE) {//Scientific notation is not supported
    long number = 0;
    char *end_pointer;
    char buffer[BUFFER_SIZE + 1];
    bool is_valid = false;
    do {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = '\0';
        }
        fgets(buffer, BUFFER_SIZE + 1, stdin);
        fflush(stdin);
        number = strtol(buffer, &end_pointer, 10);
        if (buffer[BUFFER_SIZE] == '\0' || buffer[BUFFER_SIZE] == '\n') {
            if ((*end_pointer == '\0' || *end_pointer == '\n') && buffer[0] != '\n') {
                if (MINIMAL_VALUE <= number && number <= MAXIMAL_VALUE) {
                    is_valid = true;
                } else {
                    printf("Number must be greater than %ld and less than %ld! Try entering something else.\n", MINIMAL_VALUE, MAXIMAL_VALUE);
                    is_valid = false;
                }
            } else {
                printf("Wrong Input! Try entering something else.\n");
                is_valid = false;
            }
        } else {
            printf("Buffer Overflow! Try entering something else.\n");
            is_valid = false;
        }
    } while (!is_valid);
    return number;
}
long long get_long_long (int BUFFER_SIZE, long long MINIMAL_VALUE, long long MAXIMAL_VALUE) {//Scientific notation is not supported
    long long number = 0;
    char *end_pointer;
    char buffer[BUFFER_SIZE + 1];
    bool is_valid = false;
    do {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = '\0';
        }
        fgets(buffer, BUFFER_SIZE + 1, stdin);
        fflush(stdin);
        number = strtoll(buffer, &end_pointer, 10);
        if (buffer[BUFFER_SIZE] == '\0' || buffer[BUFFER_SIZE] == '\n') {
            if ((*end_pointer == '\0' || *end_pointer == '\n') && buffer[0] != '\n') {
                if (MINIMAL_VALUE <= number && number <= MAXIMAL_VALUE) {
                    is_valid = true;
                } else {
                    printf("Number must be greater than %lld and less than %lld! Try entering something else.\n", MINIMAL_VALUE, MAXIMAL_VALUE);
                    is_valid = false;
                }
            } else {
                printf("Wrong Input! Try entering something else.\n");
                is_valid = false;
            }
        } else {
            printf("Buffer Overflow! Try entering something else.\n");
            is_valid = false;
        }
    } while (!is_valid);
    return number;
}

float get_float (int BUFFER_SIZE, float MINIMAL_VALUE, float MAXIMAL_VALUE, int PRECISION) {//Scientific notation is supported
    if (PRECISION >= BUFFER_SIZE - 2) {
        printf("Precision is bigger than buffer size! Try entering something else.\n");
        return 0;
    }
    float number = 0.0F;
    char *end_pointer;
    char buffer[BUFFER_SIZE + 1];
    bool is_valid = false;
    do {
        for (int i = 0; i < BUFFER_SIZE + 1; i++) {
            buffer[i] = '\0';
        }
        fgets(buffer, BUFFER_SIZE + 1, stdin);
        fflush(stdin);
        number = strtof(buffer, &end_pointer);
        if (buffer[BUFFER_SIZE] == '\0' || buffer[BUFFER_SIZE] == '\n') {
            if ((*end_pointer == '\0' || *end_pointer == '\n') && buffer[0] != '\n') {
                if (MINIMAL_VALUE <= number && number <= MAXIMAL_VALUE) {
                    int precision_digits = 0;
                    bool dot_in_input = false;
                    for (int i = 0; i < BUFFER_SIZE; i++) {
                        if (buffer[i] == '\0' || buffer[i] == '\n') {
                            break;
                        } else {
                            if (dot_in_input && is_digit(buffer[i])) {
                                precision_digits++;
                            } else {
                                if (buffer[i] == '.') {
                                    dot_in_input = true;
                                }
                            }
                        }
                    }
                    if (precision_digits <= PRECISION) {
                        is_valid = true;
                    } else {
                        printf("Precision must be less or equal %d digits after decimal point! Try entering something else.\n", PRECISION);
                        is_valid = false;
                    }
                } else {
                    printf("Number must be greater than %f and less than %f! Try entering something else.\n", MINIMAL_VALUE, MAXIMAL_VALUE);
                    is_valid = false;
                }
            } else {
                printf("Wrong Input!\n");
                is_valid = false;
            }
        } else {
            printf("Buffer Overflow!\n");
            is_valid = false;
        }
    } while (!is_valid);
    return number;
}
double get_double (int BUFFER_SIZE, double MINIMAL_VALUE, double MAXIMAL_VALUE, int PRECISION) {//Scientific notation is supported
    if (PRECISION >= BUFFER_SIZE - 2) {
        printf("Precision is bigger than buffer size! Try entering something else.\n");
        return 0;
    }
    double number = 0.0;
    char *end_pointer;
    char buffer[BUFFER_SIZE + 1];
    bool is_valid = false;
    do {
        for (int i = 0; i < BUFFER_SIZE + 1; i++) {
            buffer[i] = '\0';
        }
        fgets(buffer, BUFFER_SIZE + 2, stdin);
        fflush(stdin);
        number = strtod(buffer, &end_pointer);
        if (buffer[BUFFER_SIZE] == '\0' || buffer[BUFFER_SIZE] == '\n') {
            if ((*end_pointer == '\0' || *end_pointer == '\n') && buffer[0] != '\n') {
                if (MINIMAL_VALUE <= number && number <= MAXIMAL_VALUE) {
                    int precision_digits = 0;
                    bool dot_in_input = false;
                    for (int i = 0; i < BUFFER_SIZE; i++) {
                        if (buffer[i] == '\0' || buffer[i] == '\n') {
                            break;
                        } else {
                            if (dot_in_input && is_digit(buffer[i])) {
                                precision_digits++;
                            } else {
                                if (buffer[i] == '.') {
                                    dot_in_input = true;
                                }
                            }
                        }
                    }
                    if (precision_digits <= PRECISION) {
                        is_valid = true;
                    } else {
                        printf("Precision must be less or equal %d digits after decimal point! Try entering something else.\n", PRECISION);
                        is_valid = false;
                    }
                } else {
                    printf("Number must be greater than %.*lf and less than %.*lf! Try entering something else.\n", PRECISION, MINIMAL_VALUE, PRECISION, MAXIMAL_VALUE);
                    is_valid = false;
                }
            } else {
                printf("Wrong Input! Try entering something else.\n");
                is_valid = false;
            }
        } else {
            printf("Buffer Overflow! Try entering something else.\n");
            is_valid = false;
        }
    } while (!is_valid);
    return number;
}
long double get_long_double (int BUFFER_SIZE, long double MINIMAL_VALUE, long double MAXIMAL_VALUE, int PRECISION) {//Scientific notation is supported
    if (PRECISION >= BUFFER_SIZE - 2) {
        printf("Precision is bigger than buffer size! Try entering something else.\n");
        return 0;
    }
    long double number = 0.0;
    char *end_pointer;
    char buffer[BUFFER_SIZE + 1];
    bool is_valid = false;
    do {
        for (int i = 0; i < BUFFER_SIZE + 1; i++) {
            buffer[i] = '\0';
        }
        fgets(buffer, BUFFER_SIZE + 1, stdin);
        fflush(stdin);
        number = strtold(buffer, &end_pointer);
        if (buffer[BUFFER_SIZE] == '\0' || buffer[BUFFER_SIZE] == '\n') {
            if ((*end_pointer == '\0' || *end_pointer == '\n') && buffer[0] != '\n') {
                if (MINIMAL_VALUE <= number && number <= MAXIMAL_VALUE) {
                    int precision_digits = 0;
                    bool dot_in_input = false;
                    for (int i = 0; i < BUFFER_SIZE; i++) {
                        if (buffer[i] == '\0' || buffer[i] == '\n') {
                            break;
                        } else {
                            if (dot_in_input && is_digit(buffer[i])) {
                                precision_digits++;
                            } else {
                                if (buffer[i] == '.') {
                                    dot_in_input = true;
                                }
                            }
                        }
                    }
                    if (precision_digits <= PRECISION) {
                        is_valid = true;
                    } else {
                        printf("Precision must be less or equal %d digits after decimal point! Try entering something else.\n", PRECISION);
                        is_valid = false;
                    }
                } else {
                    printf("Number must be greater than %Lf and less than %Lf! Try entering something else.\n", MINIMAL_VALUE, MAXIMAL_VALUE);
                    is_valid = false;
                }
            } else {
                printf("Wrong Input! Try entering something else.\n");
                is_valid = false;
            }
        } else {
            printf("Buffer Overflow! Try entering something else.\n");
            is_valid = false;
        }
    } while (!is_valid);
    return number;
}

bool get_bool (char* operation_1, char* operation_2) {
    const int BUFFER_SIZE = 2;
    int number = 0;
    char* end_pointer;
    char buffer[BUFFER_SIZE];
    bool is_valid = false;
    do {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            buffer[i] = '\0';
        }
        printf("Enter 1 to %s or 0 to %s:\n", operation_1, operation_2);
        fgets(buffer, BUFFER_SIZE + 1, stdin);
        fflush(stdin);
        number = strtol(buffer, &end_pointer, 10);
        if (buffer[BUFFER_SIZE - 1] == '\0' || buffer[BUFFER_SIZE - 1] == '\n') {
            if (*end_pointer == '\0' || *end_pointer == '\n') {
                if (number == true || number == false) {
                    is_valid = true;
                } else {
                    printf("Input must be 1 or 0!\n");
                    is_valid = false;
                }
            } else {
                printf("Wrong Input! Try entering something else.\n");
                is_valid = false;
            }
        } else {
            printf("Buffer Overflow! Try entering something else.\n");
            is_valid = false;
        }
    } while (!is_valid);
    return (bool)number;
}
