#include "general_functions.h"

typedef struct Complex {
    double Re;
    double Im;
} complex;

bool val_cmp (double arg1, double arg2, double temp_arg) {
    return ((arg1 > arg2) ? (temp_arg >= arg2) : (temp_arg <= arg2));
}
complex get_resistance (complex number_1, complex number_2) {
    complex result = {0.0, 0.0};
    result.Re = (number_1.Re * number_2.Re + number_1.Im * number_2.Im) / (pow(number_2.Re, 2) + pow(number_2.Im, 2));
    result.Im = (number_1.Im * number_2.Re - number_1.Re * number_2.Im) / (pow(number_2.Re, 2) + pow(number_2.Im, 2));
    return result;
}
int get_solution (double f_1, double f_2, double df)  {
    wprintf(L"Введіть номер ланцюга (%d-%d):\n", FIRST_CIRCUIT, CIRCUIT_QUANTITY);
    int circuit = get_integer(CIRCUIT_BUFFER_SIZE, FIRST_CIRCUIT, CIRCUIT_QUANTITY);

    double R1 = 0., R2 = 0., L = 0., C = 0.;
    double f0 = 0., w = 0.;

    complex complex_1 =     {0., 0.},
            complex_2 = {0., 0.},
            result = {0., 0.};

    switch (circuit) {
        case FIRST_CIRCUIT: case SECOND_CIRCUIT: {
            wprintf (L"Введіть супротив резистора (Ом):\n");
            R1 = get_double(RESISTANCE_BUFFER_SIZE, RESISTANCE_MIN_VAL, RESISTANCE_MAX_VAL, RESISTANCE_MAX_ACC);
            break;
        }
        case THIRD_CIRCUIT: case FOURTH_CIRCUIT: {
            wprintf (L"Введіть супротив першого резистора (Ом):\n");
            R1 = get_double(RESISTANCE_BUFFER_SIZE, RESISTANCE_MIN_VAL, RESISTANCE_MAX_VAL, RESISTANCE_MAX_ACC);
            wprintf (L"Введіть супротив другого резистора (Ом):\n");
            R2 = get_double(RESISTANCE_BUFFER_SIZE, RESISTANCE_MIN_VAL, RESISTANCE_MAX_VAL, RESISTANCE_MAX_ACC);
            break;
        }
        default: {
            return SOLUTION_ERROR;
        }
    }

    wprintf (L"Введіть індуктивність котушки (мГн):\n");
    L = get_double(INDUCTANCE_BUFFER_SIZE, INDUCTANCE_MIN_VAL, INDUCTANCE_MAX_VAL, INDUCTANCE_MAX_ACC);
    wprintf (L"Введіть ємніть конденстора (мкФ):\n");
    C = get_double(CAPACITY_BUFFER_SIZE, CAPACITY_MIN_VAL, CAPACITY_MAX_VAL, CAPACITY_MAX_ACC);
    f0 = 1. / (2. * M_PI * sqrt(L * C));

    if (df == 0.) {
        w = 2. * M_PI * f_1;
        switch (circuit) {
            case FIRST_CIRCUIT: {
                complex_1.Re = L / C;
                complex_1.Im = -R1 / (w * C);
                complex_2.Re = R1;
                complex_2.Im = w * L - 1 / (w * C);
                result = get_resistance(complex_1, complex_2);
                break;
            }
            case SECOND_CIRCUIT: {
                complex_1.Re = L / C;
                complex_1.Im = R1 / (w * C);
                complex_2.Re = R1;
                complex_2.Im = w * L - 1. / (w * C);
                result = get_resistance(complex_1, complex_2);
                break;
            }
            case THIRD_CIRCUIT: {
                complex_1.Re = R1 * R2;
                complex_1.Im = R1 * (w * L - 1. / (w * C));
                complex_2.Re = R1 + R2;
                complex_2.Im = w * L - 1. / (w * C);
                result = get_resistance(complex_1, complex_2);
                break;
            }
            case FOURTH_CIRCUIT: {
                complex_1.Re = R1 * R2 + L / C;
                complex_1.Im = w * L * R1 - R2 / (w * C);
                complex_2.Re = R1 + R2;
                complex_2.Im = w * L - 1. / (w * C);
                result = get_resistance(complex_1, complex_2);
                break;
            }
            default: {
                return SOLUTION_ERROR;
            }
        }
        wprintf (L"Для частоти f = %.*lf\tопір Z = %e %c %ei\n",
                 FREQUENCY_MAX_ACC, f_1, result.Re, (int)(result.Im > 0. ? '+' : '-'), fabs(result.Im));
    } else {
        double f = f_1;
        if (f_1 > f_2) {
            df = -fabs(df);
        } else {
            df = fabs(df);
        }

        while (val_cmp(f_1, f_2, f)) {
            w = 2 * (double)M_PI * f;
            switch (circuit) {
                case FIRST_CIRCUIT: {
                    complex_1.Re = L / C;
                    complex_1.Im = -R1 / (w * C);
                    complex_2.Re = R1;
                    complex_2.Im = w * L - 1 / (w * C);
                    result = get_resistance(complex_1, complex_2);
                    break;
                }
                case SECOND_CIRCUIT: {
                    complex_1.Re = L / C;
                    complex_1.Im = R1 / (w * C);
                    complex_2.Re = R1;
                    complex_2.Im = w * L - 1. / (w * C);
                    result = get_resistance(complex_1, complex_2);
                    break;
                }
                case THIRD_CIRCUIT: {
                    complex_1.Re = R1 * R2;
                    complex_1.Im = R1 * (w * L - 1. / (w * C));
                    complex_2.Re = R1 + R2;
                    complex_2.Im = w * L - 1. / (w * C);
                    result = get_resistance(complex_1, complex_2);
                    break;
                }
                case FOURTH_CIRCUIT: {
                    complex_1.Re = R1 * R2 + L / C;
                    complex_1.Im = w * L * R1 - R2 / (w * C);
                    complex_2.Re = R1 + R2;
                    complex_2.Im = w * L - 1. / (w * C);
                    result = get_resistance(complex_1, complex_2);
                    break;
                }
                default: {
                    return false;
                }
            }
            wprintf (L"Для частоти f = %.*lf\tопір Z = %e %c %ei\n",
                     FREQUENCY_MAX_ACC, f, result.Re, (int)(result.Im > 0. ? '+' : '-'), fabs(result.Im));
            f += df;
        }
    }
    wprintf (L"Резонансна частота: %.*lf\n", FREQUENCY_MAX_ACC, f0);
    return SOLUTION_SUCCESS;
}
void limitation_message (void) {
    setlocale(LC_ALL, "");
    wprintf (L"Десяткова частина вводиться через кому\n\n");
    wprintf (L"Дані: Частота, Опір, Індуктивність, Ємність\n"
             "Тип даних: Дійсний\n"
             "Обмеження значень: 1E-%d <= Значення <= %d\n"
             "Обмеження довжини: %d символів\n"
             "Обмеження цифр після десяткової крапки: %d цифр\n\n",
             FREQUENCY_MAX_ACC, FREQUENCY_MAX_VAL, FREQUENCY_BUFFER_SIZE, FREQUENCY_MAX_ACC);
    wprintf (L"Дані: Номер ланцюга\n"
             "Тип даних: Цілий\n"
             "Обмеження значень: %d <= Значення <= %d\n"
             "Обмеження довжини: %d символ\n\n",
             FIRST_CIRCUIT, CIRCUIT_QUANTITY, CIRCUIT_BUFFER_SIZE);
}