#include "libs.h"
#include "general_functions.h"
#include "defines.h"

#define FOE (-1)

//-------------------------------Additional Functions-------------------------------
bool is_Valid_File_Name (const char* File_Name) {
    bool is_valid_name = true;
    for (int i = 0; i < FILE_NAME_SIZE; i++) {
        if (File_Name[i] == '\000') {
            break;
        } else {
            if (!is_valid_symbol(File_Name[i]) && File_Name[i] != ' ') {
                is_valid_name = false;
                break;
            }
        }
    }
    return is_valid_name;
}
char* get_File_Name (void) {
    bool is_valid_name = false;
    wprintf(L"Введіть назву файлу (Максимум %d символів):\n", FILE_NAME_SIZE);
    char* Temp_Name;
    while (!is_valid_name) {
        Temp_Name = get_string(FILE_NAME_SIZE);
        if (is_Valid_File_Name(Temp_Name)) {
            is_valid_name = true;
        } else {
            wprintf(L"Некоректна назва файлу!\n");
        }
    }
    char* File_Name = get_buffer(GENERAL_FILE_NAME_SIZE);
    strcpy(File_Name, PROGRAM_PATH);
    strcat(File_Name, Temp_Name);
    strcat(File_Name, PROGRAM_EXTENSION);
    free(Temp_Name);
    return File_Name;
}
char* get_Record_Element (int size) {
    char* array = get_string(size);
    char* element = (char*)calloc(size + 1, sizeof(char));
    for (int i = 0; i < size; i++) {
        element[i] = (char)(array[i] == '\0' ? 32 : array[i]);
    }
    free(array);
    return element;
}
void get_Aligned_Right (char* string, int size) {
    int last_char = 0;
    for (int i = size - 1; i >= 0; i--) {
        if (is_valid_symbol(string[i])) {
            last_char = i;
            break;
        }
    }
    if (last_char != size - 1) {
        for (int i = last_char; i >= 0; i--) {
            string[size - 1 - (last_char - i)] = string[i];
            string[i] = ' ';
        }
    }
}
char* get_Record (void) {
    wprintf(L"Введіть назву (Максимум %d символів):\n", GAME_NAME_SIZE);
    char* game_name = get_Record_Element(GAME_NAME_SIZE);

    char* game_rate;
    wprintf(L"Введіть оцінку (%.2f <= Оцінка <= %.2f, Вводити через кому):\n", MIN_RATE, MAX_RATE);
    game_rate = get_double_string (RATE_SIZE - 5, MIN_RATE, MAX_RATE, MAX_RATE_ACC);
    get_Aligned_Right(game_rate, RATE_SIZE - 5);

    char* game_year;
    wprintf(L"Введіть рік створення (Максимум %d символів):\n", CREATION_YEAR_SIZE);
    game_year = get_integer_string (CREATION_YEAR_SIZE, MIN_YEAR, MAX_YEAR);
    get_Aligned_Right(game_year, CREATION_YEAR_SIZE);

    wprintf(L"Введіть розробників (Максимум %d символів):\n", DEVELOPER_NAME_SIZE);
    char* game_developer = get_Record_Element(DEVELOPER_NAME_SIZE);

    char* record = (char*)calloc(GENERAL_RECORD_SIZE, sizeof(char));

    strcpy(record, game_name);
    for (int i = 0; i < RECORD_STEP_SIZE; i++) {
        strcat(record, " ");
    }
    strcat(record, game_rate);
    strcat(record, " / 10");
    for (int i = 0; i < RECORD_STEP_SIZE; i++) {
        strcat(record, " ");
    }
    strcat(record, game_year);
    for (int i = 0; i < RECORD_STEP_SIZE; i++) {
        strcat(record, " ");
    }
    strcat(record, game_developer);
    free(game_name);
    free(game_rate);
    free(game_year);
    free(game_developer);
    return record;
}
int get_Line_Count (char* File_Name, int line_size) {
    int line_quantity = 0;
    FILE* Temp_Ptr = fopen(File_Name, "r");
    fseek(Temp_Ptr, 0, SEEK_SET);
    if (Temp_Ptr == NULL) {
        wprintf(L"Помилка відкриття файлу!\n");
    } else {
        while (fgetc(Temp_Ptr) != EOF) {
            line_quantity++;
            fseek(Temp_Ptr, line_size - 1, SEEK_CUR);
        }
    }
    fseek(Temp_Ptr, 0, SEEK_SET);
    return line_quantity;
}
void leave (void) {
    wprintf(L"Натисність пробіл щоб перейти до меню.\n");
    while (getch() != (int)L' ');
}
//----------------------------------------------------------------------------------

//----------------------Show-Info-Files----------------------
int get_Records(char* File_Name) {
    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {
        wprintf(L"Помилка відкриття файлу!\n");
        free(File_Name);
        return OPERATION_ERROR;
    } else {
        int record_quantity = get_Line_Count(File_Name, GENERAL_RECORD_SIZE);
        char buff[GENERAL_RECORD_SIZE];
        for (int i = 0; i < record_quantity; i++) {
            fseek(File_Ptr, i * GENERAL_RECORD_SIZE, SEEK_SET);
            if (fgets(buff, GENERAL_RECORD_SIZE, File_Ptr) == NULL) {
                wprintf(L"Помилка зчитування запису!\n");
                free(File_Name);
                fclose(File_Ptr);
                return OPERATION_ERROR;
            } else {
                wprintf(L"%d)\t%s", i + 1, buff);
            }
        }
        fclose(File_Ptr);
    }
    wprintf(L"\n");
    return OPERATION_SUCCESS;
}
void show_Info (void) {
    wprintf(L"Ця програма призначена для роботи з файлами і записами у них\n"
            "Вона може працювати лише з файлами розришення .txt, що знаходяться у папці Files\n"
            "Програма має шаблон для збереження інформації про ігри:\n"
            "- Їх назву\n"
            "- Їх оцінка по десятибальній шкалі (з сотими)\n"
            "- Їх рік випуску\n"
            "- Їх розробників\n\n"
            "Обмеження довижин:\n"
            "Назва файлу: %d символ\n"
            "Назва гри: %d символ\n"
            "Оцінка: %d символ\n"
            "Рік випуску: %d символ\n"
            "Розробники: %d символ\n\n", FILE_NAME_SIZE, GAME_NAME_SIZE, RATE_SIZE, CREATION_YEAR_SIZE, DEVELOPER_NAME_SIZE);
    wprintf(L"Для переміщення по меню потрібно натискати клавіши WASD\n"
            "Щоб виконати потрібну функцію потрібно перейти на неї за допомогою клавіш і натиснути Пробіл\n");

    leave();
}
int show_Files (void) {
    DIR* Folder_Ptr = opendir(FOLDER_PATH);
    if (Folder_Ptr == NULL) {
        wprintf(L"Помилка відкриття директорії!\n");
        return OPERATION_ERROR;
    } else {
        struct dirent *Files;
        int i = 0;
        while ((Files = readdir(Folder_Ptr)) != NULL) {
            if (i > 1) {
                wprintf(L"%d)\t%s\n", i - 1, Files->d_name);
            }
            i++;
        }
        if (i == 2) {
            wprintf(L"Директорія не містить файлів!\n");
            return OPERATION_ERROR;
        }
    }
    wprintf(L"\n");
    return OPERATION_SUCCESS;
}
int show_File (char* File_Name) {
    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {
        return OPERATION_ERROR;
    } else {
        int line_quantity = get_Line_Count(File_Name, GENERAL_RECORD_SIZE);
        if (line_quantity > 0) {
            char buff[GENERAL_RECORD_SIZE];
            fill_endline(buff, GENERAL_RECORD_SIZE);
            fseek(File_Ptr, 0, SEEK_SET);

            for (int i = 0; i < line_quantity; i++) {
                if (fgets(buff, GENERAL_RECORD_SIZE, File_Ptr) == NULL) {
                    wprintf(L"Помилка читання вмісту файла!\n");
                    free(File_Name);
                    fclose(File_Ptr);
                    return OPERATION_ERROR;
                } else {
                    wprintf(L"%s", buff);
                }
            }
        } else {
            wprintf(L"Файл не містить записів!\n");
            free(File_Name);
            fclose(File_Ptr);
            return OPERATION_ERROR;
        }
        fclose(File_Ptr);
    }
    return OPERATION_SUCCESS;
}
//-----------------------------------------------------------

//-------------------------------File Operations------------------------------------
int create_File (void) {
    wprintf(L"Файли в директорії:\n");
    if (show_Files() == OPERATION_ERROR) {
        return OPERATION_ERROR;
    }

    char* File_Name = get_File_Name();

    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {

        File_Ptr = fopen(File_Name, "w+");
        if (File_Ptr == NULL) {
            wprintf(L"Помилка створення файлу!\n");
            free(File_Name);
            leave();
            return OPERATION_ERROR;
        } else {
            wprintf(L"Файл успішно створений.\n\n");
            fclose(File_Ptr);

            wprintf(L"Файли після створення нового:\n");
            show_Files();

        }
    } else {
        wprintf(L"Файл з такою назвою вже існує. Новий файл не створено!\n");
        fclose(File_Ptr);
        free(File_Name);
        leave();
        return OPERATION_ERROR;
    }
    free(File_Name);
    leave();
    return OPERATION_SUCCESS;
}
int read_File (void) {
    wprintf(L"Файли в директорії:\n");
    if (show_Files() == OPERATION_ERROR) {
        return OPERATION_ERROR;
    }

    char* File_Name = get_File_Name();
    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {
        wprintf(L"Вказаний файл не існує!\n");
        free(File_Name);
        leave();
        return OPERATION_ERROR;
    } else {
        int line_quantity = get_Line_Count(File_Name, GENERAL_RECORD_SIZE);
        if (line_quantity > 0) {
            char buff[GENERAL_RECORD_SIZE];
            fill_endline(buff, GENERAL_RECORD_SIZE);
            fseek(File_Ptr, 0, SEEK_SET);

            for (int i = 0; i < line_quantity; i++) {
                if (fgets(buff, GENERAL_RECORD_SIZE, File_Ptr) == NULL) {
                    wprintf(L"Помилка читання вмісту файла!\n");
                    free(File_Name);
                    fclose(File_Ptr);
                    leave();
                    return OPERATION_ERROR;
                } else {
                    wprintf(L"%d)\t%s", i + 1, buff);
                }
            }
        } else {
            wprintf(L"Файл не містить записів!\n");
            free(File_Name);
            fclose(File_Ptr);
            leave();
            return OPERATION_ERROR;
        }
        fclose(File_Ptr);
    }
    free(File_Name);
    leave();
    return OPERATION_SUCCESS;
}
int delete_File (void) {
    wprintf(L"Файли в директорії:\n");
    if (show_Files() == OPERATION_ERROR) {
        return OPERATION_ERROR;
    }

    char* File_Name = get_File_Name();
    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {
        wprintf(L"Вказаний файл не існує!\n");
        free(File_Name);
        leave();
        return OPERATION_ERROR;
    } else {
        fclose(File_Ptr);
        if (remove(File_Name) == FOE) {
            wprintf(L"Помилка видалення файлу. Файл не видалено!\n");
            free(File_Name);
            leave();
            return OPERATION_ERROR;
        } else {
            wprintf(L"Файл успішно видалено.\n\n");

            wprintf(L"Директорія після видалення:\n");
            show_Files();

        }
    }
    free(File_Name);
    leave();
    return OPERATION_SUCCESS;
}
//----------------------------------------------------------------------------------

//-------------------------------Record Operations----------------------------------
int create_Record (void) {
    wprintf(L"Директорія файлів:\n");
    if (show_Files() == OPERATION_ERROR) {
        return OPERATION_ERROR;
    }

    char* File_Name = get_File_Name();
    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {
        wprintf(L"Вказаний файл не існує!\n");
        free(File_Name);
        leave();
        return OPERATION_ERROR;
    } else {
        fclose(File_Ptr);
        File_Ptr = fopen(File_Name, "a");
        if (File_Ptr == NULL) {
            wprintf(L"Не вдалося відкрити файл для створення запису!\n");
            free(File_Name);
            leave();
            return OPERATION_ERROR;
        } else {
            wprintf(L"\n");
            fprintf(File_Ptr, "%s\n", get_Record());
            wprintf(L"Запис створено!\n\n");
            fclose(File_Ptr);

            wprintf(L"Файл після додавання запису:\n");
            if (show_File(File_Name) == OPERATION_ERROR) {
                free(File_Name);
                return OPERATION_ERROR;
            }
        }
    }
    free(File_Name);
    leave();
    return OPERATION_SUCCESS;
}
int read_Record (void) {
    wprintf(L"Директорія файлів:\n");
    if (show_Files() == OPERATION_ERROR) {
        return OPERATION_ERROR;
    }

    char* File_Name = get_File_Name();
    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {
        wprintf(L"Вказаний файл не існує!\n");
        free(File_Name);
        leave();
        return OPERATION_ERROR;
    } else {
        int line_quantity = get_Line_Count(File_Name, GENERAL_RECORD_SIZE);

        if (line_quantity > 0) {
            char *buff = get_buffer(GENERAL_RECORD_SIZE);
            int quantity_size = (int) (log10((double) line_quantity) + 1);

            wprintf(L"\nЗнайдено %d запис(-и/-ів):\n", line_quantity);
            wprintf(L"Оберіть режим виведення:\n"
                    "%d - Вивести окремі записи\n"
                    "%d - Вивести інтервал записів\n",
                    READ_SEPARATELY, READ_INTERVAL);
            int mode = get_integer(CHOICE_SIZE, MIN_CHOICE, READ_MAX_CHOICE);

            if (mode == READ_SEPARATELY) {
                wprintf(L"\nВведіть кількість записів для виведення (від 1 до %d):\n", line_quantity);
                int quantity = get_integer(quantity_size, MIN_QUANTITY_OUTPUT, line_quantity);
                int record_array[quantity];
                for (int i = 0; i < quantity; i++) {
                    wprintf(L"\nВведіть номер запису №%d:\n", i + 1);
                    record_array[i] = get_integer(quantity_size, MIN_INT_VALUE, line_quantity);
                }
                for (int i = 0; i < quantity; i++) {
                    fseek(File_Ptr, (record_array[i] - 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                    if (fgets(buff, GENERAL_RECORD_SIZE, File_Ptr) == NULL) {
                        wprintf(L"Помилка зчитування запису!\n");
                        free(File_Name);
                        free(buff);
                        fclose(File_Ptr);
                        leave();
                        return OPERATION_ERROR;
                    } else {
                        wprintf(L"%s", buff);
                    }
                }
            } else {
                if (mode == READ_INTERVAL) {
                    wprintf(L"Введіть початкову межу інтервалу:\n");
                    int start = get_integer(quantity_size, MIN_INT_VALUE, line_quantity);
                    wprintf(L"Введіть кінцеву межу інтервалу:\n");
                    int end = get_integer(quantity_size, MIN_INT_VALUE, line_quantity);
                    if (start <= end) {
                        for (int i = start; i <= end; i++) {
                            fseek(File_Ptr, (i - 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                            if (fgets(buff, GENERAL_RECORD_SIZE, File_Ptr) == NULL) {
                                wprintf(L"Помилка зчитування запису!\n");
                                free(File_Name);
                                free(buff);
                                fclose(File_Ptr);
                                leave();
                                return OPERATION_ERROR;
                            } else {
                                wprintf(L"%s", buff);
                            }
                        }
                    } else {
                        for (int i = end; i >= start; i--) {
                            fseek(File_Ptr, (i - 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                            if (fgets(buff, GENERAL_RECORD_SIZE, File_Ptr) == NULL) {
                                wprintf(L"Помилка зчитування запису!\n");
                                free(File_Name);
                                free(buff);
                                fclose(File_Ptr);
                                leave();
                                return OPERATION_ERROR;
                            } else {
                                wprintf(L"%s", buff);
                            }
                        }
                    }
                }
            }
            free(buff);
        } else {
            wprintf(L"Файл не містить записів!\n");
            free(File_Name);
            fclose(File_Ptr);
            leave();
            return OPERATION_ERROR;
        }
        fclose(File_Ptr);
    }
    free(File_Name);
    leave();
    return OPERATION_SUCCESS;
}
int edit_Record (void) {
    wprintf(L"Директорія файлів:\n");
    if (show_Files() == OPERATION_ERROR) {
        return OPERATION_ERROR;
    }

    char* File_Name = get_File_Name();
    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {
        wprintf(L"Вказаного файлу не існує!\n");
        free(File_Name);
        leave();
        return OPERATION_ERROR;
    } else {
        fclose(File_Ptr);
        File_Ptr = fopen(File_Name, "r+");
        if (File_Ptr == NULL) {
            wprintf(L"Помилка відкриття файлу!\n");
            free(File_Name);
            leave();
            return OPERATION_ERROR;
        } else {
            int line_quantity = get_Line_Count(File_Name, GENERAL_RECORD_SIZE);
            if (line_quantity > 0) {
                char buff[GENERAL_RECORD_SIZE];
                int quantity_size = (int) (log10((double) line_quantity) + 1);

                wprintf(L"\nЗаписи у файлі:\n");
                if (get_Records(File_Name) == OPERATION_ERROR) {
                    free(File_Name);
                    fclose(File_Ptr);
                    return OPERATION_ERROR;
                }

                wprintf(L"Введіть номер запису (від %d до %d):\n", 1, line_quantity);
                int line = get_integer(quantity_size, 1, line_quantity);
                fseek(File_Ptr, (line - 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                if (fgets(buff, GENERAL_RECORD_SIZE, File_Ptr) == NULL) {
                    wprintf(L"Помилка редагування запису!\n");
                    free(File_Name);
                    fclose(File_Ptr);
                    leave();
                    return OPERATION_ERROR;
                } else {
                    fseek(File_Ptr, (line - 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                    wprintf(L"\nВведіть які дані змінити:\n"
                            "%d - Назва гри\n"
                            "%d - Оцінка гри\n"
                            "%d - Рік випуску\n"
                            "%d - Назва розробників\n"
                            "%d - Весь запис\n",
                            GAME_NAME, RATE, CREATION_YEAR, DEVELOPER_NAME, WHOLE_RECORD);
                    int choice = get_integer(CHOICE_SIZE, MIN_CHOICE, EDIT_MAX_CHOICE);
                    if (choice == WHOLE_RECORD) {
                        wprintf(L"\nЗапис до змінення:\n%s", buff);
                        char *empty_line = get_buffer(GENERAL_RECORD_SIZE);
                        fprintf(File_Ptr, "%s\n", empty_line);
                        free(empty_line);
                        fseek(File_Ptr, (line - 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                        fprintf(File_Ptr, "%s", get_Record());

                    } else {
                        wprintf(L"\nЗапис до змінення:\n%s", buff);
                        char *edit_element;
                        int buff_padding = 0;
                        int temp_size = GAME_NAME_SIZE;
                        if (choice > GAME_NAME) {
                            buff_padding += (GAME_NAME_SIZE + RECORD_STEP_SIZE);
                            temp_size = RATE_SIZE;
                            if (choice > RATE) {
                                buff_padding += (RATE_SIZE + RECORD_STEP_SIZE);
                                temp_size = CREATION_YEAR_SIZE;
                                if (choice > CREATION_YEAR) {
                                    buff_padding += (CREATION_YEAR_SIZE + RECORD_STEP_SIZE);
                                    temp_size = DEVELOPER_NAME_SIZE;
                                }
                            }
                        }
                        fseek(File_Ptr, buff_padding, SEEK_CUR);
                        switch (choice) {
                            case GAME_NAME: {
                                temp_size = GAME_NAME_SIZE;
                                wprintf(L"\nВведіть назву (Максимум %d символів):\n", GAME_NAME_SIZE);
                                edit_element = get_Record_Element(GAME_NAME_SIZE);
                                break;
                            }
                            case RATE: {
                                temp_size = RATE_SIZE;
                                wprintf(L"\nВведіть оцінку (%.2f <= Оцінка <= %.2f):\n", MIN_RATE, MAX_RATE);
                                edit_element = get_Record_Element(RATE_SIZE);
                                break;
                            }
                            case CREATION_YEAR: {
                                temp_size = CREATION_YEAR_SIZE;
                                wprintf(L"\nВведіть рік створення (Максимум %d символів):\n", CREATION_YEAR_SIZE);
                                edit_element = get_Record_Element(CREATION_YEAR_SIZE);
                                break;
                            }
                            case DEVELOPER_NAME: {
                                temp_size = DEVELOPER_NAME_SIZE;
                                wprintf(L"\nВведіть розробників (Максимум %d символів):\n", DEVELOPER_NAME_SIZE);
                                edit_element = get_Record_Element(DEVELOPER_NAME_SIZE);
                                break;
                            }
                            default: {
                                wprintf(L"Помилка обрання стовпчика\n");
                                free(File_Name);
                                fclose(File_Ptr);
                                leave();
                                return OPERATION_ERROR;
                            }
                        }
                        for (int i = 0; i < temp_size; i++) {
                            fputc(edit_element[i], File_Ptr);
                        }
                        if (choice == RATE) {
                            fseek(File_Ptr, -5, SEEK_CUR);
                            fprintf(File_Ptr, "%s", " / 10");
                        }
                        free(edit_element);
                    }
                    fseek(File_Ptr, (line - 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                    fgets(buff, GENERAL_RECORD_SIZE, File_Ptr);
                    wprintf(L"\nЗапис після змінення:\n%s", buff);
                }
            } else {
                wprintf(L"Файл не містить записів!\n");
                free(File_Name);
                fclose(File_Ptr);
                leave();
                return OPERATION_ERROR;
            }
            fclose(File_Ptr);
        }
    }
    free(File_Name);
    leave();
    return OPERATION_SUCCESS;
}

int arrange_Records (int* sort_array) {
    wprintf(L"Директорія файлів:\n");
    if (show_Files() == OPERATION_ERROR) {
        return OPERATION_ERROR;
    }

    char* File_Name = get_File_Name();
    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {
        wprintf(L"Вказаного файлу не існує!\n");
        free(File_Name);
        leave();
        return OPERATION_ERROR;
    } else {
        fclose(File_Ptr);
        File_Ptr = fopen(File_Name, "r+");
        if (File_Ptr == NULL) {
            wprintf(L"Помилка відкриття файлу!\n");
            free(File_Name);
            leave();
            return OPERATION_ERROR;
        } else {
            wprintf(L"Записи у файлі:\n");
            if (get_Records(File_Name) == OPERATION_ERROR) {
                free(File_Name);
                fclose(File_Ptr);
                return OPERATION_ERROR;
            }
            int line_quantity = get_Line_Count(File_Name, GENERAL_RECORD_SIZE);
            if (line_quantity > 1) {
                wprintf(L"Введіть номер стовпця за яким буде проводитись сортування:\n"
                        "%d - Назва гри\n"
                        "%d - Оцінка гри\n"
                        "%d - Рік випуску\n"
                        "%d - Назва розробників\n",
                        GAME_NAME, RATE, CREATION_YEAR, DEVELOPER_NAME);
                int column_choice = get_integer(CHOICE_SIZE, MIN_CHOICE, ARRANGE_MAX_CHOICE);
                wprintf(L"\nВведіть порядок сортування:\n"
                        "%d - За зростанням\n"
                        "%d - За спаданням\n",
                        ASCENDING_ARRANGEMENT, DESCENDING_ARRANGEMENT);
                int arrangement_choice = get_integer(CHOICE_SIZE, ASCENDING_ARRANGEMENT, DESCENDING_ARRANGEMENT);
                int st_index = 0;
                int sub_size = 0;
                switch (column_choice) {
                    case GAME_NAME: {
                        sub_size = GAME_NAME_SIZE;
                        break;
                    }
                    case RATE: {
                        st_index = GAME_NAME_SIZE + RECORD_STEP_SIZE;
                        sub_size = RATE_SIZE;
                        break;
                    }
                    case CREATION_YEAR: {
                        st_index = GAME_NAME_SIZE + RATE_SIZE + 2 * RECORD_STEP_SIZE;
                        sub_size = CREATION_YEAR_SIZE;
                        break;
                    }
                    case DEVELOPER_NAME: {
                        st_index = GAME_NAME_SIZE + RATE_SIZE + CREATION_YEAR_SIZE + 3 * RECORD_STEP_SIZE;
                        sub_size = DEVELOPER_NAME_SIZE;
                        break;
                    }
                    default: {
                        wprintf(L"Помилка обрання стовпчика\n");
                        free(File_Name);
                        fclose(File_Ptr);
                        leave();
                        return OPERATION_ERROR;
                    }

                }
                char buff_1[GENERAL_RECORD_SIZE];
                char buff_2[GENERAL_RECORD_SIZE];
                char line_1[sub_size];
                char line_2[sub_size];

                for (int i = 1; i < line_quantity; i++) {
                    for (int j = 0; j < line_quantity - i; j++) {
                        fseek(File_Ptr, j * GENERAL_RECORD_SIZE, SEEK_SET);
                        fgets(buff_1, GENERAL_RECORD_SIZE, File_Ptr);
                        for (int k = 0; k < sub_size; k++) {
                            line_1[k] = buff_1[k + st_index];
                        }

                        fseek(File_Ptr, (j + 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                        fgets(buff_2, GENERAL_RECORD_SIZE, File_Ptr);
                        for (int k = 0; k < sub_size; k++) {
                            line_2[k] = buff_2[k + st_index];
                        }
                        if ((arrangement_choice == ASCENDING_ARRANGEMENT && strcmp(line_1, line_2) > 0) ||
                            (arrangement_choice == DESCENDING_ARRANGEMENT && strcmp (line_1, line_2) < 0)) {
                            fseek(File_Ptr, j * GENERAL_RECORD_SIZE, SEEK_SET);
                            fprintf(File_Ptr, "%s", buff_2);
                            fseek(File_Ptr, (j + 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                            fprintf(File_Ptr, "%s", buff_1);
                        }
                    }
                }
                wprintf(L"Сортування завершено!\n");
                for (int i = 0; i < COLUMN_QUANTITY; i++) {
                    sort_array[i] = 0;
                }
                sort_array[column_choice - 1] = arrangement_choice;

            } else {
                if (line_quantity > 0) {
                    wprintf(L"Записи вже відсортовані!\n");
                    free(File_Name);
                    fclose(File_Ptr);
                    leave();
                    return OPERATION_ERROR;
                } else {
                    wprintf(L"Файл не містить записів!\n");
                    free(File_Name);
                    fclose(File_Ptr);
                    leave();
                    return OPERATION_ERROR;
                }
            }
            fclose(File_Ptr);

            wprintf(L"\nЗаписи після сортування:\n");

            if (get_Records(File_Name) == OPERATION_ERROR) {
                free(File_Name);
                return OPERATION_ERROR;
            }
        }
    }
    free(File_Name);
    leave();
    return OPERATION_SUCCESS;
}
int insert_Record (const int* sort_array) {
    bool is_sorted = false;
    int sort_column = 0;
    int sort_arrangement = 0;
    for (int i = 0; i < COLUMN_QUANTITY; i++) {
        if (sort_array[i] != 0) {
            is_sorted = true;
            sort_column = i + 1;
            sort_arrangement = sort_array[i];
        }
    }
    if (is_sorted) {
        wprintf(L"Директорія файлів:\n");
        if (show_Files() == OPERATION_ERROR) {
            return OPERATION_ERROR;
        }

        char* File_Name = get_File_Name();
        FILE* File_Ptr = fopen(File_Name, "r");
        if (File_Ptr == NULL) {
            wprintf(L"Вказаного файлу не існує!\n");
            free(File_Name);
            leave();
            return OPERATION_ERROR;
        } else {
            fclose(File_Ptr);
            File_Ptr = fopen (File_Name, "r+");
            if (File_Ptr == NULL) {
                wprintf(L"Помилка відкриття файлу!\n");
                free(File_Name);
                leave();
                return OPERATION_ERROR;
            } else {
                wprintf(L"Записи у файлі:\n");
                if (get_Records(File_Name) == OPERATION_ERROR) {
                    free(File_Name);
                    fclose(File_Ptr);
                    return OPERATION_ERROR;
                }
                int line_quantity = get_Line_Count(File_Name, GENERAL_RECORD_SIZE);
                char* insertion_line = get_Record();
                int st_index = 0;
                int sub_size = 0;
                switch (sort_column) {
                    case GAME_NAME: {
                        sub_size = GAME_NAME_SIZE;
                        break;
                    }
                    case RATE: {
                        st_index = GAME_NAME_SIZE + RECORD_STEP_SIZE - 1;
                        sub_size = RATE_SIZE;
                        break;
                    }
                    case CREATION_YEAR: {
                        st_index = GAME_NAME_SIZE + RATE_SIZE + 2 * RECORD_STEP_SIZE - 1;
                        sub_size = CREATION_YEAR_SIZE;
                        break;
                    }
                    case DEVELOPER_NAME: {
                        st_index = GAME_NAME_SIZE + RATE_SIZE + CREATION_YEAR_SIZE + 3 * RECORD_STEP_SIZE - 1;
                        sub_size = DEVELOPER_NAME_SIZE;
                        break;
                    }
                    default: {
                        wprintf(L"Помилка обрання стовпчику\n");
                        free(File_Name);
                        free(insertion_line);
                        fclose(File_Ptr);
                        leave();
                        return OPERATION_ERROR;
                    }
                }
                char comparison_line[sub_size];
                for (int i = 0; i < sub_size; i++) {
                    comparison_line[i] = insertion_line[st_index + i];
                }
                char buff[GENERAL_RECORD_SIZE];
                char comparison_buff[sub_size];
                int insertion_point = 0;
                switch (sort_arrangement) {
                    case ASCENDING_ARRANGEMENT: {
                        for (int i = 0; i < line_quantity; i++) {
                            fseek(File_Ptr, i * GENERAL_RECORD_SIZE, SEEK_SET);
                            fgets(buff, GENERAL_RECORD_SIZE, File_Ptr);
                            for (int j = 0; j < sub_size; j++) {
                                comparison_buff[j] = buff[st_index + j];
                            }
                            if (strcmp(comparison_line, comparison_buff) < 0) {
                                insertion_point = i;
                                break;
                            }
                        }
                        break;
                    }
                    case DESCENDING_ARRANGEMENT: {
                        for (int i = 0; i < line_quantity; i++) {
                            fseek(File_Ptr, i * GENERAL_RECORD_SIZE, SEEK_SET);
                            fgets(buff, GENERAL_RECORD_SIZE, File_Ptr);
                            for (int j = 0; j < sub_size; j++) {
                                comparison_buff[j] = buff[st_index + j];
                            }
                            if (strcmp(comparison_line, comparison_buff) > 0) {
                                insertion_point = i;
                                break;
                            }
                        }
                        break;
                    }
                    default: {
                        free(File_Name);
                        free(insertion_line);
                        fclose(File_Ptr);
                        return OPERATION_ERROR;
                    }
                }
                for (int i = line_quantity - 1; i >= insertion_point; i--) {
                    fseek(File_Ptr, i * GENERAL_RECORD_SIZE, SEEK_SET);
                    fgets(buff, GENERAL_RECORD_SIZE, File_Ptr);
                    fseek(File_Ptr, (i + 1) * GENERAL_RECORD_SIZE, SEEK_SET);
                    fprintf(File_Ptr, "%s", buff);
                }
                fseek(File_Ptr, insertion_point * GENERAL_RECORD_SIZE, SEEK_SET);
                fprintf(File_Ptr, "%s\n", insertion_line);
                free(insertion_line);
                wprintf(L"Вставку виконано!\n");
            }

            fclose(File_Ptr);

            wprintf(L"\nЗаписи після вставки:\n");
            if (get_Records(File_Name) == OPERATION_ERROR) {
                free(File_Name);
                return OPERATION_ERROR;
            }
        }
        free(File_Name);
    } else {
        wprintf(L"Записи ще не відсортовані! Вставку не виконано.\n");
        leave();
        return OPERATION_ERROR;
    }
    leave();
    return OPERATION_SUCCESS;
}
int delete_Record (void) {
    wprintf(L"Директорія файлів:\n");
    if (show_Files() == OPERATION_ERROR) {
        return OPERATION_ERROR;
    }

    char* File_Name = get_File_Name();
    FILE* File_Ptr = fopen(File_Name, "r");
    if (File_Ptr == NULL) {
        wprintf(L"Вказаного файлу не існує!\n");
        free(File_Name);
        leave();
        return OPERATION_ERROR;
    } else {
        fclose(File_Ptr);
        File_Ptr = fopen(File_Name, "r+");
        if (File_Ptr == NULL) {
            wprintf(L"Помилка відкриття файлу!\n");
            free(File_Name);
            leave();
            return OPERATION_ERROR;
        } else {
            wprintf(L"Записи у файлі:\n");
            if (get_Records(File_Name) == OPERATION_ERROR) {
                free(File_Name);
                fclose(File_Ptr);
                leave();
                return OPERATION_ERROR;
            }
            int line_quantity = get_Line_Count(File_Name, GENERAL_RECORD_SIZE);
            if (line_quantity > 0) {
                char** storage = (char**) calloc (line_quantity - 1, sizeof(char*));
                for (int i = 0; i < line_quantity - 1; i++) {
                    storage[i] = (char*) calloc (GENERAL_RECORD_SIZE, sizeof(char));
                }
                int quantity_size = (int) (log10((double) line_quantity) + 1);
                wprintf(L"Введіть номер запису для видалення:\n");
                int deleting_line = get_integer(quantity_size, MIN_LINE_VALUE, line_quantity) - 1;
                int storage_index = 0;
                int actual_index = 0;
                while (actual_index < line_quantity) {
                    if (actual_index != deleting_line) {
                        fseek(File_Ptr, actual_index * GENERAL_RECORD_SIZE, SEEK_SET);
                        fgets(storage[storage_index], GENERAL_RECORD_SIZE, File_Ptr);
                        storage_index++;
                    }
                    actual_index++;
                }
                fclose(File_Ptr);
                File_Ptr = fopen(File_Name, "w");
                if (File_Ptr == NULL) {
                    wprintf(L"Помилка видалення запису!\n");
                    free(File_Name);
                    for (int i = 0; i < line_quantity - 1; i++) {
                        free(storage[i]);
                    }
                    free(storage);
                    fclose(File_Ptr);
                    leave();
                    return OPERATION_ERROR;
                } else {
                    for (int i = 0; i < line_quantity - 1; i++) {
                        fprintf(File_Ptr, "%s", storage[i]);
                    }
                    wprintf(L"Запис видалено!\n");
                    fclose(File_Ptr);

                    wprintf(L"Записи після видалення:\n");
                    if (get_Records(File_Name) == OPERATION_ERROR) {
                        free(File_Name);
                        for (int i = 0; i < line_quantity - 1; i++) {
                            free(storage[i]);
                        }
                        free(storage);
                        return OPERATION_ERROR;
                    }
                }
            } else {
                wprintf(L"Файл не містить записів!\n");
                free(File_Name);
                fclose(File_Ptr);
                leave();
                return OPERATION_ERROR;
            }
        }
    }
    free(File_Name);
    leave();
    return OPERATION_SUCCESS;
}
//----------------------------------------------------------------------------------