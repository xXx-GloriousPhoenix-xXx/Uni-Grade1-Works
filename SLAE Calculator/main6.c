#include "general_functions.h"
#include "SLAE.h"

int main (void) {
    srand(time(NULL));
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    limitation_message();

    int matrix_size = 0;
    int precision = 0;
    bool root = true;

    double* array;
    double** matrix;
    double* solution_array;

    do {
        matrix_size = 0;
        precision = 0;
        root = true;

        wprintf(L"Введіть розмірність матриці:\n");
        matrix_size = get_integer (MATRIX_SIZE_BUFFER_SIZE, MATRIX_SIZE_MINIMAL_VALUE, MATRIX_SIZE_MAXIMAL_VALUE);
        wprintf(L"Введіть точність розрахунків:\n");
        precision = get_integer (PRECISION_BUFFER_SIZE, PRECISION_MINIMAL_VALUE, PRECISION_MAXIMAL_VALUE);
        root = get_bool (L"згенерувати випадкові коефіцієнти", L"ввести коефіцієнти власноруч");
        array = get_double_array (matrix_size);
        matrix = get_double_matrix (matrix_size);
        if (root) {
            randomize_double_matrix (matrix, matrix_size);
            randomize_double_array (array, matrix_size);
        } else {
            fill_double_matrix (matrix, matrix_size);
            wprintf (L"Введіть вільні коефіцієнти (Кожен коефіцієнт в окремий рядок):\n");
            fill_double_array (array, matrix_size);
        }
        if (is_solvable_matrix (matrix, matrix_size)) {
            wprintf(L"Вхідна матриця:\n");
            print_inlet_matrix (matrix, array, matrix_size);

            solution_array = get_solution (matrix, array, matrix_size, precision);
            wprintf (L"Масив розв'язків:\n");
            print_array (solution_array, matrix_size, precision);

            free (solution_array);
        } else {
            wprintf(L"Неможливо знайти корені цим методом.\n");
        }
        delete_double_matrix (matrix, matrix_size);
        free (array);
    } while (get_bool(L"продовжити", L"вийти з програми"));

    return 0;
}