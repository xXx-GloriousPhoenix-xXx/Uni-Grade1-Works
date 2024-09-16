#include "bubble_array_sort.h"
#include "general_functions.h"

int main() {
    int array_size = 0;
    double* array_pointer;
    limitation_message();
    do {
        printf("Enter the size of array:\n");
        array_size = get_integer(INTEGER_BUFFER_SIZE, INTEGER_MINIMAL_VALUE, INTEGER_MAXIMAL_VALUE);
        array_pointer = (double*)calloc(array_size, sizeof(double));
        for (int i = 0; i < array_size; i++) {
            printf("Enter the element #%d:\n", i + 1);
            array_pointer[i] = get_double(DOUBLE_BUFFER_SIZE, DOUBLE_MINIMAL_VALUE, DOUBLE_MAXIMAL_VALUE, DOUBLE_MAXIMAL_PRECISION);
        }
        bool arrangement = get_bool("sort in ascending order", "sort in descending order");
        get_sorted(array_pointer, array_size, arrangement);
        for (int i = 0; i < array_size; i++) {
            printf("%lf ", array_pointer[i]);
        }
        printf("\n");
        free(array_pointer);
    } while (get_bool("continue","exit"));
}
