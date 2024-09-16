#include "libs.h"
#include "file_operations.h"
#include "defines.h"

//-------------------UI-Print-Functions----------------------
void wprintf_string(wchar_t symbol, int quantity) {
    for (int i = 0; i < quantity; i++) {
        wprintf(L"%lc", symbol);
    }
}
void wprintf_button_row(int row, int active) {
    wchar_t* menu_text[][2] = {{L"      Створити Файл      ",L"    » Створити Файл «    "},
                               {L"      Зчитати  Файл      ",L"    » Зчитати  Файл «    "},
                               {L"      Видалити Файл      ",L"    » Видалити Файл «    "},
                               {L"     Створити  Запис     ",L"   » Створити  Запис «   "},
                               {L"      Зчитати запис      ",L"    » Зчитати запис «    "},
                               {L"    Редагувати  запис    ",L"  » Редагувати  запис «  "},
                               {L"   Впорядкувати записи   ",L" » Впорядкувати записи « "},
                               {L"     Вставка  запису     ",L"   » Вставка  запису «   "},
                               {L"    Видалення  запису    ",L"  » Видалення  запису «  "},
                               {L"     Доступні  файли     ",L"   » Доступні  Файли «   "},
                               {L"    Завершити  роботу    ",L"  » Завершити  роботу «  "},
                               {L"      Про  програму      ",L"    » Про  програму «    "}};

    wprintf(L"%ls",L"║  ╔");
    wprintf_string(L'═', 25);
    wprintf(L"%ls",L"╗  ╔");
    wprintf_string(L'═', 25);
    wprintf(L"%ls",L"╗  ╔");
    wprintf_string(L'═', 25);
    wprintf(L"%ls\n",L"╗  ║");

    for (int i = 1; i <= OPS_IN_ROW; i++) {
        wprintf(L"%ls",L"║  ║");
        wprintf(L"%ls",menu_text[OPS_IN_ROW * row - (OPS_IN_ROW + 1 - i)][active == i]);
    }
    wprintf(L"%ls",L"║  ║\n");

    wprintf(L"%ls",L"║  ╚");
    wprintf_string(L'═', 25);
    wprintf(L"%ls",L"╝  ╚");
    wprintf_string(L'═', 25);
    wprintf(L"%ls",L"╝  ╚");
    wprintf_string(L'═', 25);
    wprintf(L"%ls\n",L"╝  ║");
}
void wprintf_menu(int active_row, int active_element) {
    wprintf(L"%lc",L'╔');
    wprintf_string(L'═', 89);
    wprintf(L"%lc\n",L'╗');

    for (int i = ROW_1; i <= ROW_QUANTITY; i++) {
        wprintf_button_row(i, i == active_row ? active_element : 0);
    }

    wprintf(L"%lc",L'╚');
    wprintf_string(L'═', 89);
    wprintf(L"%lc\n",L'╝');
}
//-----------------------------------------------------------

//-------------File-Operation-Processor----------------------
int task_manager (int active_row, int active_element, int* sort_array) {
    system("cls");
    switch (active_row) {
        case ROW_1: {
            switch (active_element) {
                case CREATE_FILE: {
                    return create_File();
                }
                case READ_FILE: {
                    return read_File();
                }
                case DELETE_FILE: {
                    return delete_File();
                }
                default: {
                    return OPERATION_ERROR;
                }
            }
        }
        case ROW_2: {
            switch (active_element) {
                case CREATE_RECORD: {
                    return create_Record();
                }
                case READ_RECORD: {
                    return read_Record();
                }
                case EDIT_RECORD: {
                    return edit_Record();
                }
                default: {
                    return OPERATION_ERROR;
                }
            }
        }
        case ROW_3: {
            switch (active_element) {
                case ARRANGE_RECORDS: {
                    return arrange_Records(sort_array);
                }
                case INSERT_RECORD: {
                    return insert_Record(sort_array);
                }
                case DELETE_RECORD: {
                    return delete_Record();
                }
                default: {
                    return OPERATION_ERROR;
                }
            }
        }
        case ROW_4: {
            switch (active_element) {
                case SHOW_FILES: {
                    int case_id = show_Files();
                    leave();
                    return case_id;
                }
                case QUIT: {
                    return OPERATION_QUIT;
                }
                case SHOW_INFO: {
                    show_Info();
                    break;
                }
                default: {
                    return OPERATION_ERROR;
                }
            }
            break;
        }
        default: {
            return OPERATION_ERROR;
        }
    }
    return OPERATION_SUCCESS;
}
//-----------------------------------------------------------

//-------------------UI Control Function---------------------
int operate_ui (int *active_row, int *active_element, int* sorted_records) {
    int symbol;
    symbol = getch();
    switch (symbol) {
        case (int)L'w': {
            if (*active_row > TOP_BORDER) {
                (*active_row)--;
            }
            break;
        }
        case (int)L'a': {
            if (*active_element > LEFT_BORDER) {
                (*active_element)--;
            }
            break;
        }
        case (int)L's': {
            if (*active_row < BOTTOM_BORDER) {
                (*active_row)++;
            }
            break;
        }
        case (int)L'd': {
            if (*active_element < RIGHT_BORDER) {
                (*active_element)++;
            }
            break;
        }
        case (int)L' ': {
            return task_manager(*active_row, *active_element, sorted_records);
        }
        default: {break;}
    }
    return OPERATION_SUCCESS;
}
//-----------------------------------------------------------