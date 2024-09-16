#include "taylor_trigonometry.h"
#include "general_functions.h"

int main () {
    double border_1 = 0.;
    double border_2 = 0.;
    double step = 0.;
    int precision = 0;
    bool path = false;
    limitation_message();

    do {
        printf("Enter the first border:\n");
        border_1 = get_double(DOUBLE_BUFFER_SIZE, DOUBLE_MINIMAL_VALUE, DOUBLE_MAXIMAL_VALUE, DOUBLE_MAXIMAL_PRECISION);

        printf("Enter the second border:\n");
        border_2 = get_double(DOUBLE_BUFFER_SIZE, DOUBLE_MINIMAL_VALUE, DOUBLE_MAXIMAL_VALUE, DOUBLE_MAXIMAL_PRECISION);

        if (border_1 != border_2) {
            printf("Enter the step of sequence:\n");
            step = get_double(DOUBLE_BUFFER_SIZE, STEP_MINIMAL_VALUE, fabs(border_1 - border_2), DOUBLE_MAXIMAL_PRECISION);
        } else {
            step = STEP_MINIMAL_VALUE;
        }

        printf("Enter the precision of calculation:\n");
        precision = get_integer(INTEGER_BUFFER_SIZE, INTEGER_MINIMAL_VALUE, INTEGER_MAXIMAL_VALUE);
        path = get_bool("find sin","find cos");
        get_values(border_1, border_2, step, precision, path);

    } while (get_bool("continue","exit"));

    return 0;
}