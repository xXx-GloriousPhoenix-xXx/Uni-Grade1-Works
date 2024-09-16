#include "string_sort.h"
#include "general_functions.h"

int main (void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    limitation_message();
    bool root = true;
    bool arrangement = true;
    do {
        root = get_bool(L"ввести випадкові символи", L"ввести символи власноруч");

        wprintf(L"Введіть кількість рядків:\n");
        int quantity = get_integer(QUANTITY_BUFFER_SIZE, QUANTITY_MINIMAL_VALUE, QUANTITY_MAXIMAL_VALUE);
        wprintf(L"Введіть довжину рядків:\n");
        int size = get_integer(SIZE_BUFFER_SIZE, SIZE_MINIMAL_VALUE, SIZE_MAXIMAL_VALUE);
        arrangement = get_bool(L"відсортувати за зростанням", L"відсортувати за спаданням");
        wchar_t** string_array = get_string_array(size, quantity, root);

        wprintf(L"Рядки до сортування:\n");
        print_array((const wchar_t **) string_array, size, quantity);
        get_sorted_string_array(string_array, quantity, arrangement);
        wprintf(L"\nРядки після сортування:\n");
        print_array((const wchar_t **) string_array, size, quantity);
        printf("\n");

        for (int i = 0; i < quantity; i++) {
            free (string_array[i]);
        }
        free (string_array);
    } while (get_bool((wchar_t *)L"продовжити", (wchar_t *)L"вийти з програми"));
    return 0;
}
