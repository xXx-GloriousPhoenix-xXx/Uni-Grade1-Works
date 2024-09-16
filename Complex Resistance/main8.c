#include "general_functions.h"
#include "Res.h"

int main(void) {
    setlocale (LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    limitation_message();

    do {
        double f_1 = 0., f_2 = 0., df = 0.;
        int circuit = 0;
        wprintf (L"Введіть першу межу частоту (Гц):\n");
        f_1 = get_double (FREQUENCY_BUFFER_SIZE, FREQUENCY_MIN_VAL, FREQUENCY_MAX_VAL, FREQUENCY_MAX_ACC);
        wprintf (L"Введіть другу межу частоту (Гц):\n");
        f_2 = get_double (FREQUENCY_BUFFER_SIZE, FREQUENCY_MIN_VAL, FREQUENCY_MAX_VAL, FREQUENCY_MAX_ACC);
        if (f_1 != f_2) {
            wprintf (L"Введіть крок для зміни частоти (Гц):\n");
            df = get_double(FREQUENCY_BUFFER_SIZE, FREQUENCY_STEP_MIN_VAL, FREQUENCY_STEP_MAX_VAL, FREQUENCY_MAX_ACC);
        } else {
            df = 0.;
        }

        if (get_solution(f_1, f_2, df) == SOLUTION_ERROR) {
            wprintf(L"Ланцюг з таким номером не знайдено!\n");
        }
    } while (get_bool(L"продовжити", L"завершити програму"));
    return 0;
}
