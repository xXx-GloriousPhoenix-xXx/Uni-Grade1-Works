#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define DOUBLE_BUFFER_SIZE 21
/* 1 symbol for minus
 * 19 symbols for digits
 * 1 symbol for point
 * example: -1000000.000000000000
 * */
#define DOUBLE_MAXIMAL_PRECISION 12
#define DOUBLE_MINIMAL_VALUE (-1080000)
#define DOUBLE_MAXIMAL_VALUE 1080000
#define STEP_MINIMAL_VALUE 0

#define INTEGER_BUFFER_SIZE 2
/*
 * 2 symbol for digit
 * example: 12
 * */
#define INTEGER_MINIMAL_VALUE 1
#define INTEGER_MAXIMAL_VALUE 12

#define ARGUMENT_BIAS 21
/* 1 symbol for minus
 * 19 symbols for digits
 * 1 symbol for point
 * example: -1000000.000000000000
 * */
#define GENERAL_BIAS 15
/* 1 symbol for minus
 * 13 symbols for digits
 * 1 symbol for point
 * example: -0.000000000000
 * */
#define DIFFERENCE_PRECISION 6

bool val_cmp (double arg1, double arg2, double temp_arg) {
    return ((arg1 > arg2) ? (temp_arg >= arg2) : (temp_arg <= arg2));
}

double get_period_value (double argument) {
    return argument - (int)(argument / 360.0) * 360.0;
}
double get_radian (double argument) {
    return (M_PI * get_period_value(argument)) / 180;   
}

int get_val_length (double argument, int precision) {
    return 1 + (argument < 0) + precision + ((int)fabs(argument) ? (int)(log10((int)fabs(argument)) + 1) : 1);
}

double get_sin (double argument, int precision) {
    double delta = argument;
    double sin_result = argument;
    int n = 1;
    double numerator = argument;
    double denominator = 1.;
    double double_precision = 1. / pow(10, precision);
    do {
        numerator = -numerator * (argument * argument);
        denominator = denominator * (n + 1.) * (n + 2.);
        delta = numerator / denominator;
        sin_result = sin_result + delta;
        n = n + 2;
    } while (fabs(delta) >= double_precision);
    return sin_result;
}
double get_cos (double argument, int precision) {
    double delta = 1.;
    double cos_result = 1.;
    int n = 1;
    double numerator = 1.;
    double denominator = 1.;
    double double_precision = 1. / pow(10, precision);
    do {
        numerator = -numerator * (argument * argument);
        denominator = denominator * n * (n + 1.);
        delta = numerator / denominator;
        cos_result = cos_result + delta;
        n = n + 2;
    } while (fabs(delta) >= double_precision);
    return cos_result;
}

void get_output (double argument, double trigonometry, double taylor, int precision) {
    int temporary_bias = 0;
    //TODO fix output tabs
    /*Tests:
     * -1080000 12
     * -0.000000000001
     * */
    temporary_bias = ARGUMENT_BIAS - get_val_length(argument, precision);
    //temporary_bias = ARGUMENT_BIAS - (get_integer_length(argument, precision) + 1 + precision);
    printf("%.*lf", precision, argument);
    for (int i = 0; i < temporary_bias; i++) {
        printf(" ");
    }

    temporary_bias = GENERAL_BIAS - get_val_length(trigonometry, precision);
    printf("   %.*lf", precision, trigonometry);
    for (int i = 0; i < temporary_bias; i++) {
        printf(" ");
    }

    temporary_bias = GENERAL_BIAS - get_val_length(taylor, precision);
    printf("   %.*lf", precision, taylor);
    for (int i = 0; i < temporary_bias; i++) {
        printf(" ");
    }

    printf("   %.*e\n", DIFFERENCE_PRECISION, trigonometry - taylor);
}

void get_values (double border_1, double border_2, double step, int precision, bool path) {
    if (path) {
        double trigonometry_sin;
        double taylor_sin;
        double argument;
        printf("----------X----------   -----Sin(x)----   --TaylorSin(x)-   Sin(x)-TaylorSin(x)\n");
        if (step == STEP_MINIMAL_VALUE) {
            argument = get_radian(border_1);
            trigonometry_sin = sin(argument);
            if (argument < 0) {
                taylor_sin = -get_sin(-argument, precision);
            } else {
                taylor_sin = get_sin(argument, precision);
            }
            get_output(border_1, trigonometry_sin, taylor_sin, precision);
        } else {
            double temp_value = border_1;
            if (border_1 > border_2) {
                step = -step;
            }
            while (val_cmp(border_1, border_2, temp_value)) {
                argument = get_radian(temp_value);
                trigonometry_sin = sin(argument);
                if (argument < 0) {
                    taylor_sin = -get_sin(-argument, precision);
                } else {
                    taylor_sin = get_sin(argument, precision);
                }
                get_output(temp_value, trigonometry_sin, taylor_sin, precision);
                temp_value += step;
            }
        }
    } else {
        printf("----------X----------   ----Cos(x)----    -TaylorCos(x)-    Cos(x)-TaylorCos(x)\n");
        double trigonometry_cos;
        double taylor_cos;
        double argument;
        if (step == STEP_MINIMAL_VALUE) {
            argument = get_radian(border_1);
            trigonometry_cos = cos(argument);
            if (argument < 0) {
                taylor_cos = get_cos (-argument, precision);
            } else {
                taylor_cos = get_cos (argument, precision);
            }
            get_output(border_1, trigonometry_cos, taylor_cos, precision);
        } else {
            double temp_value = border_1;
            if (border_1 > border_2) {
                step = -step;
            }
            while (val_cmp(border_1, border_2, temp_value)) {
                argument = get_radian(temp_value);
                trigonometry_cos = cos(argument);
                if (argument < 0) {
                    taylor_cos = get_cos(-argument, precision);
                } else {
                    taylor_cos = get_cos(argument, precision);
                }
                get_output(temp_value, trigonometry_cos, taylor_cos, precision);
                temp_value += step;
            }
        }
    }
}
void limitation_message () {
    printf("Input: Border 1, Border 2\n"
           "Type: Double\n"
           "Value limitation: %d <= Element <= %d"
           "\nMaximal length of input: %d symbols"
           "\nPrecision limitation: %d digits after decimal point\n\n",
           DOUBLE_MINIMAL_VALUE, DOUBLE_MAXIMAL_VALUE, DOUBLE_BUFFER_SIZE, DOUBLE_MAXIMAL_PRECISION);
    printf("Input: Step\n"
           "Type: Double\n"
           "Value limitation: %d <= Element <= %d"
           "\nMaximal length of input: %d symbols"
           "\nPrecision limitation: %d digits after decimal point\n\n",
           STEP_MINIMAL_VALUE, DOUBLE_MAXIMAL_VALUE, DOUBLE_BUFFER_SIZE, DOUBLE_MAXIMAL_PRECISION);
    printf("Input: Precision\n"
           "Type: Integer\n"
           "Value limitation: %d <= Value <= %d\n"
           "Maximal length of input: %d symbols\n\n",
           INTEGER_MINIMAL_VALUE, INTEGER_MAXIMAL_VALUE, INTEGER_BUFFER_SIZE);
    printf("Input: Path (Sin or Cos)\n"
           "Type: Boolean\n"
           "Value limitation: %d <= Value <= %d\n"
           "Maximal length of input: %d symbols\n\n",
           0, 1, 1);
}
