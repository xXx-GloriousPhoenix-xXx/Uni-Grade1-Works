#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>
#include <wchar.h>
#include <windows.h>

#define QUANTITY_BUFFER_SIZE 3
#define QUANTITY_MINIMAL_VALUE 2
#define QUANTITY_MAXIMAL_VALUE 100

#define SIZE_BUFFER_SIZE 3
#define SIZE_MINIMAL_VALUE 1
#define SIZE_MAXIMAL_VALUE 100

typedef struct {
    int st_index;
    int interval_length;
} intervals;
intervals index_array[] = {{48, 10}, //0 - 9
                           {65, 26}, //A - Z
                           {97, 26}, //a - z
                           {1025, 1}, //Ё
                           {1028, 1}, //Є
                           {1030, 2}, //І, Ї
                           {1040, 64}, //А - Я, а - я
                           {1105, 1}, //ё
                           {1108, 1}, //є
                           {1110, 2}, //і, ї
                           {1168, 2}}; //Ґ, ґ
const int intervals_quantity = sizeof(index_array) / sizeof(intervals);


bool string_validation (const wchar_t* string, int size) {
    bool is_valid = true;
    int temporary_index = 0;
    for (int i = 0; i < size; i++) {
        if (is_valid) {
            if ((int) string[i] < index_array[0].st_index ||
                (int) string[i] > index_array[intervals_quantity - 1].st_index + index_array[intervals_quantity - 1].interval_length - 1) {
                is_valid = false;
            }
            temporary_index = (int) string[i];
            for (int j = 0; j < intervals_quantity - 1; j++) {
                if (temporary_index > index_array[j].st_index + index_array[j].interval_length - 1 &&
                    temporary_index < index_array[j + 1].st_index) {
                    is_valid = false;
                    break;
                }
            }
        } else {
            break;
        }
    }
    return is_valid;
}
wchar_t* get_user_string (int size) {
    wchar_t* buffer = (wchar_t*) calloc (size + 1, sizeof(wchar_t));
    bool is_valid = false;
    do {
        for (int i = 0; i < size + 1; i++) {
            buffer[i] = L'\000';
        }
        fgetws(buffer, size + 2, stdin);
        fflush(stdin);
        if (buffer[0] == L'\000' || buffer[0] == L'\n') {
            wprintf(L"Рядок пустий! Спробуйте ввести щось інше.\n");
            is_valid = false;
        } else {
            if (buffer[size] != L'\000' && buffer[size] != L'\n') {
                wprintf(L"Переповнення буфера! Спробуйте ввести щось інше.\n");
                is_valid = false;
            } else {
                if (buffer[size - 1] == L'\000' || buffer[size - 1] == L'\n') {
                    wprintf(L"Введений рядок занадто короткий, мав складатись з %d символів! Спробуйте ввести щось інше.\n", size);
                    is_valid = false;
                } else {
                    if (!string_validation (buffer, size)) {
                        wprintf(L"Рядок містить некоректні символи! Спробуйте ввести щось інше.\n");
                        is_valid = false;
                    } else {
                        is_valid = true;
                    }
                }
            }
        }
    } while (!is_valid);
    return buffer;
}
wchar_t* get_random_string (int size) {
    wchar_t* buffer = (wchar_t*) calloc(size + 1, sizeof(wchar_t));
    int elements_quantity = 0;
    for (int i = 0; i < intervals_quantity; i++) {
        elements_quantity += index_array[i].interval_length;
    }
    int random_index = 0;
    int temporary_array_index = 0;
    for (int i = 0; i < size; i++) {
        random_index = 1 + rand() % elements_quantity;
        temporary_array_index = 0;
        while (random_index > index_array[temporary_array_index].interval_length) {
            random_index -= index_array[temporary_array_index].interval_length;
            temporary_array_index++;
        }
        buffer[i] = (wchar_t)(index_array[temporary_array_index].st_index + random_index - 1);
    }
    return buffer;
}
wchar_t** get_string_array (int size, int quantity, bool is_random) {
    wchar_t** buffer = (wchar_t**) calloc(quantity, sizeof(wchar_t*));
    srand(time(NULL));
    for (int i = 0; i < quantity; i++) {
        if (is_random) {
            buffer[i] = get_random_string(size);
        } else {
            wprintf(L"Введіть рядок #%d:\n", i + 1);
            buffer[i] = get_user_string(size);
        }
    }
    return buffer;
}
wchar_t** get_sorted_string_array (wchar_t** array, int quantity, bool arrangement) {
    for (int i = 0; i < quantity - 1; i++) {
        for (int j = i + 1; j < quantity; j++) {
            if ((wcscmp(array[i], array[j]) > 0 && !arrangement) ||
            (wcscmp(array[i], array[j]) < 0 && arrangement)) {
                wchar_t* temporary = array[i];
                array[i] = array[j];
                array[j] = temporary;
            }
        }
    }
    return array;
}

void print_array (const wchar_t** array, int size, int quantity) {
    setlocale(LC_ALL, "");
    for (int i = 0; i < quantity; i++) {
        printf("#%d:\t\t", i + 1);
        for (int j = 0; j < size; j++) {
            wprintf(L"%lc", array[i][j]);
        }
        printf("\n");
    }
}
void limitation_message () {
    setlocale(LC_ALL, "");
    wprintf(L"Дані: Кількість рядків\n"
           "Тип даних: Цілий\n"
           "Обмеження значень: %d <= Значення <= %d\n"
           "Обмеження довжини: %d символів\n\n",
           QUANTITY_MINIMAL_VALUE, QUANTITY_MAXIMAL_VALUE, QUANTITY_BUFFER_SIZE);
    wprintf(L"Дані: Довжина рядків\n"
           "Тип даних: Цілий\n"
           "Обмеження значень: %d <= Значення <= %d\n"
           "Максимальна довжина: %d символів\n\n",
           SIZE_MINIMAL_VALUE, SIZE_MAXIMAL_VALUE, SIZE_BUFFER_SIZE);
    wprintf(L"Дані: Порядок сортування, Вид введення даних\n"
            "Тип даних: Логічний\n"
            "Обмеження значень: %d <= Значення <= %d\n"
            "Максимальна довжина: %d символів\n\n",
            0, 1, 1);
    wprintf(L"Пріоритет сортування:\n");
    int iteration_counter = 0;
    for (int i = 0; i < intervals_quantity; i++) {
        for (int j = 0; j < index_array[i].interval_length; j++) {
            wprintf(L"%lc", index_array[i].st_index + j);
            iteration_counter++;
            if (iteration_counter == 50) {
                printf("\n");
                iteration_counter = 0;
            }
        }
    }
    printf("\n\n");
}