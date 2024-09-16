#include <stdio.h>
#include <stdbool.h>

#define DOUBLE_BUFFER_SIZE 14
/* 1 symbol for minus
 * 13 symbols for digits
 * 1 symbol for point
 * */
#define DOUBLE_MAXIMAL_PRECISION 6
#define DOUBLE_MINIMAL_VALUE (-1000000)
#define DOUBLE_MAXIMAL_VALUE 1000000

#define INTEGER_BUFFER_SIZE 7
/* 1 symbol for minus
 * 6 symbols for digits
 * */
#define INTEGER_MINIMAL_VALUE 1
#define INTEGER_MAXIMAL_VALUE 1000000

#define ASCENDING_ARRANGEMENT 1
#define DESCENDING_ARRANGEMENT 0

void get_sorted (double* array_pointer, int size_of_array, bool arrangement) {
    for (int i = 0; i < size_of_array - 1; i++) {
        for (int j = i + 1; j < size_of_array; j++) {
            if ((array_pointer[j] < array_pointer[i] && arrangement == ASCENDING_ARRANGEMENT) ||
                    (array_pointer[j] > array_pointer[i] && arrangement == DESCENDING_ARRANGEMENT)) {
                double element_switch = array_pointer[j];
                array_pointer[j] = array_pointer[i];
                array_pointer[i] = element_switch;
            }
        }
    }
}
void limitation_message () {
    printf("Input: Length\n"
           "Type: Integer\n"
           "Value limitation: %d <= Value <= %d\n"
           "Maximal length of input: %d symbols\n\n",
           INTEGER_MINIMAL_VALUE, INTEGER_MAXIMAL_VALUE, INTEGER_BUFFER_SIZE);
    printf("Input: Element\n"
           "Type: Double\n"
           "Value limitation: %d <= Value <= %d"
           "\nMaximal length of input: %d symbols"
           "\nPrecision limitation: %d digits after decimal point\n\n",
           DOUBLE_MINIMAL_VALUE, DOUBLE_MAXIMAL_VALUE, DOUBLE_BUFFER_SIZE, DOUBLE_MAXIMAL_PRECISION);
    printf("Input: Arrangement\n"
           "Type: Integer\n"
           "Value limitation: %d <= Value <= %d\n"
           "Maximal length of input: %d symbols\n\n",
           DESCENDING_ARRANGEMENT, ASCENDING_ARRANGEMENT, 1);
}