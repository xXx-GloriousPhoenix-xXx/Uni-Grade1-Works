#include "general_functions.h"

#define BISECTOR_METHOD 1
#define NEWTON_METHOD 2
#define METHODS_QUANTITY 2
#define METHOD_SIZE 1

#define TRIGONOMETRY_FUNCTION 1
#define TRIGONOMETRY_LOGARITHMIC_FUNCTION 2
#define FUNCTION_QUANTITY 2
#define FUNCTION_SIZE 1

data get_data (void) {
    setlocale(LC_ALL, "");
    data new_data = {0,0,0,0};
    wprintf (L"Введіть значення параметра t:\n");
    new_data.t = get_double (T_BUFFER_SIZE, T_MIN_VAL, T_MAX_VAL, T_MAX_ACC);
    wprintf (L"Введіть ліву межу інтервалу:\n");
    new_data.a = get_double (BORDER_BUFFER_SIZE, BORDER_MIN_VAL, BORDER_MAX_VAL, BORDER_MAX_ACC);
    wprintf (L"Введіть праву межу інтервалу:\n");
    new_data.b = get_double (BORDER_BUFFER_SIZE, BORDER_MIN_VAL, BORDER_MAX_VAL, BORDER_MAX_ACC);
    wprintf (L"Введіть точність розрахунків:\n");
    new_data.digits = get_integer (EPS_BUFFER_SIZE, EPS_MIN_VAL, EPS_MAX_VAL);
    return new_data;
}

double trig_equation (double x, double t) {
    return cos(t/x) - 2 * sin(1./x) + 1./x;
}
double trig_log_equation (double x, double t) {
    return sin(log(x)) - cos(log(x)) + t * log(x);
}

bool is_valid_arguments (double a, double b, int task) {
    bool is_valid = true;
    if (a > b) {
        wprintf (L"Права границя менша за ліву!\n");
        is_valid = false;
    } else {
        if (a == 0 || b == 0) {
            wprintf (L"Функція не визначена у нулі. Неможливо розрахувати!\n");
            is_valid = false;
        } else {
            if (a == -b) {
                wprintf (L"Середина інтервалу це 0, у якому функція не визначена!\n");
                is_valid = false;
            }
        }
    }
    if (task == TRIGONOMETRY_LOGARITHMIC_FUNCTION && (a < 0 || b < 0)) {
        wprintf (L"Для другої функції значення меж має бути додатнім!\n");
        is_valid = false;
    }
    return is_valid;
}

double bisector (double (*f) (double, double), data info) {
    int iteration = 0;
    double eps = 1. / pow(10, info.digits),
           x = 0.;
    if (info.a / info.b > 0) {
        double xa = 0.,
               xb = 0.,
               temp_a = info.a,
               temp_b = info.b;
        do {
            xa = (temp_a + temp_b) / 2.;
            if (f(temp_a, info.t) * f(xa, info.t) > 0) {
                temp_a = xa;
            } else {
                temp_b = xa;
            }
            iteration++;
        } while (fabs(f(xa, info.t)) >= eps && iteration < 10000);
        if (fabs(f(xa, info.t)) <= eps && info.a <= xa && xa <= info.b) {
            x = xa;
        } else {
            temp_a = info.a,
                    temp_b = info.b;
            iteration = 0;
            do {
                xb = (temp_a + temp_b) / 2.;
                if (f(temp_b, info.t) * f(xb, info.t) > 0) {
                    temp_b = xb;
                } else {
                    temp_a = xb;
                }
                iteration++;
            } while (fabs(f(xb, info.t)) >= eps && iteration < 10000);
            if (fabs(f(xb, info.t)) <= eps && info.a <= xb && xb <= info.b) {
                x = xb;
            } else {
                wprintf(L"Неможливо знайти корінь методом бісекції на цьому інтервалі!\n");
            }
        }
    } else {
        double temp_x = 0.;
        do {
            temp_x = (info.a + info.b) / 2.;
            if (f(info.a, info.t) * f(temp_x, info.t) < 0) {
                info.a = temp_x;
            } else {
                if (f(info.b, info.t) * f(temp_x, info.t) < 0) {
                    info.b = temp_x;
                }
            }
            iteration++;
        } while (fabs(f(temp_x, info.t)) >= eps && iteration < 10000);
        if (fabs(f(temp_x, info.t)) <= eps && info.a <= temp_x && temp_x <= info.b) {
            x = temp_x;
        } else {
            wprintf(L"Неможливо знайти корінь методом бісекції на цьому інтервалі!\n");
        }
    }
    return x;
}
double newton (double (*f) (double, double), data info) {
    double eps = 1. / pow(10, info.digits);
    double x = 0., delta = 0.;
    const double alpha = 1e-12;
    double xa = info.a, xb = info.b;
    int iteration = 0;
    bool is_nan = false;
    do {
        delta = f(xa ,info.t) * alpha / (f(xa + alpha, info.t) - f(xa, info.t));
        xa = xa - delta;
        is_nan = isnan(xa) ? true : false;
        iteration++;
    } while (fabs(f(xa, info.t)) >= eps && iteration < 10000 && !is_nan);
    if (fabs(f(xa, info.t)) <= eps && info.a <= xa && xa <= info.b) {
        x = xa;
    } else {
        iteration = 0;
        is_nan = false;
        do {
            delta = f(xb, info.t) * alpha / (f(xb + alpha, info.t) - f(xb, info.t));
            xb = xb - delta;
            is_nan = isnan(xb) ? true : false;
            iteration++;
        } while (fabs(f(xb, info.t)) >= eps && iteration < 10000 && !is_nan);
        if (fabs(f(xb, info.t)) <= eps && info.a <= xb && xb <= info.b) {
            x = xb;
        } else {
            wprintf(L"Неможливо знайти корінь методом Ньютона на цьому інтервалі!\n");
        }
    }
    return x;
}

void limitation_message (void) {
    setlocale(LC_ALL, "");
    wprintf (L"Десяткова частина вводиться через кому\n\n");
    wprintf (L"Дані: Межі\n"
             "Тип даних: Дійсний\n"
             "Обмеження значень: %d <= Значення <= %d\n"
             "Обмеження довжини: %d символів\n"
             "Обмеження цифр після десяткової крапки: %d цифр\n\n",
             BORDER_MIN_VAL, BORDER_MAX_VAL, BORDER_BUFFER_SIZE, BORDER_MAX_ACC);
    wprintf (L"Дані: Параметр t\n"
             "Тип даних: Дійсний\n"
             "Обмеження значень: %d <= Значення <= %d\n"
             "Обмеження довжини: %d символів\n"
             "Обмеження цифр після десяткової крапки: %d цифр\n\n",
             T_MIN_VAL, T_MAX_VAL, T_BUFFER_SIZE, T_MAX_ACC);
    wprintf (L"Дані: Точність\n"
             "Тип даних: Цілий\n"
             "Обмеження значень: %d <= Значення <= %d\n"
             "Обмеження довжини: %d символів\n\n",
             EPS_MIN_VAL, EPS_MAX_VAL, EPS_BUFFER_SIZE);

}
void get_functions_list (void) {
    wprintf (L"1) f(x) = cos(t/x) - 2sin(1/x) + 1/x\n"
                     "2) f(x) = sin(ln(x)) - cos(ln(x)) + t * ln(x)\n");
}
void get_methods_list (void) {
    wprintf(L"1) Метод бісекції\n"
                    "2) Метод Ньютона\n");
}