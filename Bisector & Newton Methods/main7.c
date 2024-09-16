#include "general_functions.h"
#include "BisectorNewtonEquation.h"

int main (void)     {
    setlocale (LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int task = 1,
        way = 1;
    data info = {0.,0.,0.,0};
    double result = 0.;
    double (*f) (double, double) = NULL;
    double (*w) (double (*f) (double, double), data) = NULL;
    limitation_message();
    do {
        wprintf(L"Оберіть функцію для розрахунків:\n");
        get_functions_list();
        task = get_integer(FUNCTION_SIZE, TRIGONOMETRY_FUNCTION, FUNCTION_QUANTITY);
        info = get_data();
        if (is_valid_arguments(info.a, info.b, task)) {
            switch (task) {
                case TRIGONOMETRY_FUNCTION: {
                    f = trig_equation;
                    break;
                }
                case TRIGONOMETRY_LOGARITHMIC_FUNCTION: {
                    f = trig_log_equation;
                    break;
                }
                default: {
                    f = NULL;
                    wprintf(L"Помилка вибору функції!\n");
                    break;
                }
            }
            wprintf(L"Оберіть метод для розрахунків:\n");
            get_methods_list();
            way = get_integer(METHOD_SIZE, BISECTOR_METHOD, METHODS_QUANTITY);
            if (f != NULL) {
                switch (way) {
                    case BISECTOR_METHOD: {
                        w = bisector;
                        break;
                    }
                    case NEWTON_METHOD: {
                        w = newton;
                        break;
                    }
                    default: {
                        w = NULL;
                        wprintf(L"Помилка вибору методу!\n");
                        break;
                    }
                }
                if (w != NULL) {
                    result = w (f, info);
                    if (fabs(f(result, info.t)) < 1. / pow(10, info.digits) && info.a <= result && result <= info.b) {
                        wprintf (L"Відповідь: %.*lf\n", info.digits, result);
                    }
                }
            }
        }
    } while (get_bool (L"продовжити", L"вийти з програми"));
    return 0;
}