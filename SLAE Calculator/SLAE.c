#include "general_functions.h"

double* get_double_array (int size) {
    return (double*) calloc (size, sizeof(double));

}
double** get_double_matrix (int size) {
    double** matrix = (double**) calloc (size, sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix[i] = get_double_array(size);
    }
    return matrix;
}

bool is_solvable_matrix (double** matrix, int size) {
    bool is_solvable = true;
    double row_summary = 0;
    for (int i = 0; i < size; i++) {
        row_summary = 0;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                row_summary += matrix[i][j];
            }
        }
        if (fabs(row_summary) > fabs(matrix[i][i])) {
            is_solvable = false;
            break;
        }
    }
    return is_solvable;
}
void fill_double_array (double* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = get_double(COEFFICIENT_BUFFER_SIZE, COEFFICIENT_MINIMAL_VALUE, COEFFICIENT_MAXIMAL_VALUE, COEFFICIENT_MAXIMAL_PRECISION);
    }
}
void fill_double_matrix (double** matrix, int size) {
    fflush (stdout);
    for (int i = 0; i < size; i++) {
        wprintf (L"Введіть рядок #%d (Кожен коефіцієнт в окремий рядок):\n", i + 1);
        fill_double_array(matrix[i], size);
    }
}
void randomize_double_array (double* array, int size) {

    const int minimal_value = COEFFICIENT_MINIMAL_VALUE;
    const int maximal_value = COEFFICIENT_MAXIMAL_VALUE;
    const int precision = COEFFICIENT_MAXIMAL_PRECISION;
    double value = 0.;
    for (int i = 0; i < size; i++) {
        value = (double)(rand() % (2 * maximal_value - 1) + minimal_value - 1);
        if (value > 0.) {
            value += rand() % (int)pow(10, precision) / pow(10, precision);
        } else {
            if (value < 0.) {
                value -= rand() % (int)pow(10, precision) / pow(10, precision);
            }
        }
        array[i] = value;
    }
}
void randomize_double_matrix (double** matrix, int size) {

    const int minimal_value = COEFFICIENT_MINIMAL_VALUE;
    const int maximal_value = COEFFICIENT_MAXIMAL_VALUE;
    const int precision = COEFFICIENT_MAXIMAL_PRECISION;
    double value = 0.;
    double summary = 0.;
    for (int i = 0; i < size; i++) {
        summary = 0.;
        for (int j = 0; j < size; j++) {
            if (i != j) {
                value = (double)(rand() % (2 * maximal_value - 1) + minimal_value - 1);
                if (value > 0.) {
                    value += rand() % (int)pow(10, precision) / pow(10, precision);
                } else {
                    if (value < 0.) {
                        value -= rand() % (int)pow(10, precision) / pow(10, precision);
                    }
                }
                matrix[i][j] = value;
                summary += fabs(value);
            }
        }
        matrix[i][i] = summary + 1 + rand() % 10 + rand() % (int)pow(10, precision) / pow(10, precision);
    }
}

void print_array (double* array, int size, int precision) {
    for (int i = 0; i < size; i++) {
        printf("%.*lf\n", precision, array[i]);
    }
}
void print_inlet_matrix (double** matrix, double* array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%lf\t", matrix[i][j]);
        }
        printf("%lf\n", array[i]);
    }
}

void delete_double_matrix (double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free (matrix[i]);
    }
    free (matrix);
}

double get_max (const double* array, int size) {
    double value = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > value) {
            value = array[i];
        }
    }
    return value;
}
double* get_solution (double** matrix, double* array, int size, int precision) {
    double* x = get_double_array (size);
    double* xp = get_double_array (size);
    double* delta = get_double_array (size);

    const double epsilon = 1. / pow(10, precision);
    double summary = 0.;

    for (int i = 0; i < size; i++) {
        xp[i] = array[i] / matrix[i][i];
    }

    do {
        for (int i = 0; i < size; i++) {
            summary = 0.0;
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    summary += matrix[i][j] * xp[j];
                }
            }
            x[i] = (array[i] - summary) / matrix[i][i];
            delta[i] = fabs(x[i] - xp[i]);
        }
        for (int i = 0; i < size; i++) {
            xp[i] = x[i];
        }
    } while ((fabs(get_max(delta, size)) >= epsilon));
    free (x);
    free (delta);
    return xp;
}

void limitation_message (void) {
    setlocale (LC_ALL, "");
    wprintf (L"Десяткова частина вводиться через кому\n\n");
    wprintf (L"Дані: Розмірність матриці\n"
            "Тип даних: Цілий\n"
            "Обмеження значень: %d <= Значення <= %d\n"
            "Обмеження довжини: %d символів\n\n",
             MATRIX_SIZE_MINIMAL_VALUE, MATRIX_SIZE_MAXIMAL_VALUE, MATRIX_SIZE_BUFFER_SIZE);
    wprintf (L"Дані: Точність розрахунків\n"
            "Тип даних: Цілий\n"
            "Обмеження значень: %d <= Значення <= %d\n"
            "Обмеження довжини: %d символів\n\n",
             PRECISION_MINIMAL_VALUE, PRECISION_MAXIMAL_VALUE, PRECISION_BUFFER_SIZE);
    wprintf (L"Дані: Коефіцієнт\n"
             "Тип даних: Дійсний\n"
             "Обмеження значень: %d <= Значення <= %d\n"
             "Обмеження довжини: %d символів\n"
             "Обмеження цифр після десяткової крапки: %d цифр\n",
             COEFFICIENT_MINIMAL_VALUE, COEFFICIENT_MAXIMAL_VALUE, COEFFICIENT_BUFFER_SIZE, COEFFICIENT_MAXIMAL_PRECISION);
}
