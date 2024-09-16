#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>

//----//
bool is_valid_symbol (char symbol) {
    bool is_valid = false;
    if ((int)symbol >= (int)'A' && (int)symbol <= (int)'Z') {
        is_valid = true;
    } else {
        if ((int)symbol >= (int)'a' && (int)symbol <= (int)'z') {
            is_valid = true;
        } else {
            if ((int)symbol >= (int)'!' && (int)symbol <= (int)'.') {
                is_valid = true;
            } else {
                if ((int)symbol >= (int)'0' && (int)symbol <= (int)'9') {
                    is_valid = true;
                } else {
                    switch (symbol) {
                        case ';':
                        case '@':
                        case '^':
                        case '_':
                        case '`':
                        case '{':
                        case '}':
                        case '[':
                        case ']': {
                            is_valid = true;
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
    }
    return is_valid;
}
bool is_valid_character (char symbol) {
    bool is_valid = false;
    if ((int)symbol >= (int)'A' && (int)symbol <= (int)'Z') {
        is_valid = true;
    } else {
        if ((int) symbol >= (int) 'a' && (int) symbol <= (int) 'z') {
            is_valid = true;
        }
    }
    return is_valid;
}
bool is_valid_number (char symbol) {
    return ((int)'0' <= (int)symbol && (int)symbol <= (int)'9');
}
char* get_buffer (int size) {
    return (char*) calloc (size + 1, sizeof(char));
}
wchar_t* get_wbuffer (int size) {
    return (wchar_t*) calloc (size + 1, sizeof(wchar_t));
}
void replace_newendline (char* buffer, int size) {
    for (int i = 0; i < size; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\000';
        }
    }
}
void fill_endline (char* buffer, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] = '\000';
    }
}
bool valid_data (char* array, int size) {
    bool _is_valid = false;
    char* end_pointer;
    strtod (array, &end_pointer);
    if (array[size - 1] != '\000') {
        wprintf (L"Переповнення буфера. Спробуйте ввести щось інше\n");
    } else {
        if (array[0] == '\000') {
            wprintf (L"Введений рядок - пустий. Спробуйте ввести щось інше\n");
        } else {
            if (*end_pointer != '\000') {
                wprintf (L"Введені некоректні дані. Спробуйте ввести щось інше\n");
            } else {
                _is_valid = true;
            }
        }
    }
    return _is_valid;
}
bool valid_string (const char* array, int size) {
    bool is_valid = true;
    if (array[size - 1] != '\000') {
        wprintf (L"Переповнення буфера. Спробуйте ввести щось інше\n");
        is_valid = false;
    } else {
        if (array[0] == '\000') {
            wprintf(L"Введений рядок - пустий. Спробуйте ввести щось інше\n");
            is_valid = false;
        } else {
            for (int i = 0; i < size - 1; i++) {
                if (is_valid_symbol(array[i])) {
                    is_valid = true;
                }
            }
            if (!is_valid) {
                wprintf(L"Рядок містить символи, що не є латинськими літерами, або неприпустимі символи.\n");
            }
        }
    }
    return is_valid;
}
//----//

//----//
bool valid_integer (char* array, int min_val, int max_val) {
    bool _is_valid = true;
    int _value = (int) strtol (array, NULL, 10);
    if (_value < min_val || _value > max_val) {
        wprintf (L"Введене число виходить за межі допустимих значень. Спробуйте ввести щось інше\n");
        _is_valid = false;
    }
    return _is_valid;
}
bool valid_long (char* array, long min_val, long max_val) {
    bool _is_valid = true;
    long _value = strtol (array, NULL, 10);
    if (_value < min_val || _value > max_val) {
        wprintf (L"Введене число виходить за межі допустимих значень. Спробуйте ввести щось інше\n");
        _is_valid = false;
    }
    return _is_valid;
}
bool valid_llong (char* array, long long min_val, long long max_val) {
    bool _is_valid = true;
    long long _value = strtoll (array, NULL, 10);
    if (_value < min_val || _value > max_val) {
        wprintf (L"Введене число виходить за межі допустимих значень. Спробуйте ввести щось інше\n");
        _is_valid = false;
    }
    return _is_valid;
}

bool valid_float (char* array, int size, float min_val, float max_val, int max_acc) {
    bool _is_valid = true;
    bool is_integer = true;
    int dot_index = 0;
    int digits = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == '.') {
            is_integer = false;
            dot_index = i;
            break;
        }
    }
    if (!is_integer) {
        for (int i = dot_index + 1; i < size; i++) {
            if (array[i] != '\000') {
                digits++;
            } else {
                break;
            }
        }
        if (digits > max_acc) {
            wprintf (L"Кількість знаків після коми більша за допустиму. Спробуйте ввести щось інше\n");
            _is_valid = false;
        }
    }
    if (_is_valid) {
        float _value = strtof (array, NULL);
        if (_value < min_val || _value > max_val) {
            wprintf (L"Введене число виходить за межі допустимих значень. Спробуйте ввести щось інше\n");
            _is_valid = false;
        }
    }
    return _is_valid;
}
bool valid_double (char* array, int size, double min_val, double max_val, int max_acc) {
    bool _is_valid = true;
    bool is_integer = true;
    int dot_index = 0;
    int digits = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == '.' || array[i] == ',') {
            is_integer = false;
            dot_index = i;
            break;
        }
    }
    if (!is_integer) {
        for (int i = dot_index + 1; i < size; i++) {
            if (array[i] != '\000') {
                digits++;
            } else {
                break;
            }
        }
        if (digits > max_acc) {
            wprintf (L"Кількість знаків після коми більша за допустиму. Спробуйте ввести щось інше\n");
            _is_valid = false;
        }
    }
    if (_is_valid) {
        double _value = strtod (array, NULL);
        if (_value < min_val || _value > max_val) {
            wprintf (L"Введене число виходить за межі допустимих значень. Спробуйте ввести щось інше\n");
            _is_valid = false;
        }
    }
    return _is_valid;
}
bool valid_long_double (char* array, int size, long double min_val, long double max_val, int max_acc) {
    bool _is_valid = true;
    bool is_integer = true;
    int dot_index = 0;
    int digits = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == '.') {
            is_integer = false;
            dot_index = i;
            break;
        }
    }
    if (!is_integer) {
        for (int i = dot_index + 1; i < size; i++) {
            if (array[i] != '\000') {
                digits++;
            } else {
                break;
            }
        }
        if (digits > max_acc) {
            wprintf (L"Кількість знаків після коми більша за допустиму. Спробуйте ввести щось інше\n");
            _is_valid = false;
        }
    }
    if (_is_valid) {
        long double _value = strtold (array, NULL);
        if (_value < min_val || _value > max_val) {
            wprintf (L"Введене число виходить за межі допустимих значень. Спробуйте ввести щось інше\n");
            _is_valid = false;
        }
    }
    return _is_valid;
}

bool valid_bool (char* array) {
    bool _is_valid = false;
    char* end_pointer;
    int _value = 0;
    _value = (int) strtol (array, &end_pointer, 10);
    if (valid_data (array , 2)) {
        if ((_value != 0 && _value != 1) || *end_pointer != '\000') {
            wprintf (L"Введення має бути 1 або 0. Спробуйте ще раз\n");
        } else {
            _is_valid = true;
        }
    }
    return _is_valid;
}
//----//

//----//
int get_integer (int size, int min_val, int max_val) {
    setlocale (LC_ALL, "");
    bool _is_valid = false;
    const int buffer_size = size + 1;
    int _value = 0;
    char *buffer;
    buffer = get_buffer (buffer_size);
    do {
        fill_endline (buffer, buffer_size);
        fgets (buffer, buffer_size + 1, stdin);
        fflush (stdin);
        replace_newendline (buffer, buffer_size);

        if (valid_data (buffer, buffer_size)) {
            if (valid_integer (buffer, min_val, max_val)) {
                _value = (int) strtol (buffer, NULL, 10);
                _is_valid = true;
            }
        }
    } while (!_is_valid);
    free(buffer);
    return _value;
}
char* get_integer_string (int size, int min_val, int max_val) {
    setlocale (LC_ALL, "");
    bool _is_valid = false;
    const int buffer_size = size + 1;
    char *buffer;
    buffer = get_buffer (buffer_size);
    do {
        fill_endline (buffer, buffer_size);
        fgets (buffer, buffer_size + 1, stdin);
        fflush (stdin);
        replace_newendline (buffer, buffer_size);

        if (valid_data (buffer, buffer_size)) {
            if (valid_integer (buffer, min_val, max_val)) {
                _is_valid = true;
            }
        }
    } while (!_is_valid);
    char* output = get_buffer(size);
    strcpy(output, buffer);
    free(buffer);
    return output;
}
long get_long (int size, long min_val, long max_val) {
    setlocale (LC_ALL, "");
    bool _is_valid = false;
    const int buffer_size = size + 1;
    long _value = 0;
    char *buffer;
    buffer = get_buffer (buffer_size);
    do {
        fill_endline (buffer, buffer_size);
        fgets (buffer, buffer_size + 1, stdin);
        fflush (stdin);
        replace_newendline (buffer, buffer_size);

        if (valid_data (buffer, buffer_size)) {
            if (valid_long (buffer, min_val, max_val)) {
                _value = strtol (buffer, NULL, 10);
                _is_valid = true;
            }
        }
    } while (!_is_valid);
    free(buffer);
    return _value;
}
long long get_llong (int size, long long min_val, long long max_val) {
    setlocale (LC_ALL, "");
    bool _is_valid = false;
    const int buffer_size = size + 1;
    long long _value = 0;
    char *buffer;
    buffer = get_buffer (buffer_size);
    do {
        fill_endline (buffer, buffer_size);
        fgets (buffer, buffer_size + 1, stdin);
        fflush (stdin);
        replace_newendline (buffer, buffer_size);

        if (valid_data (buffer, buffer_size)) {
            if (valid_llong (buffer, min_val, max_val)) {
                _value = strtoll (buffer, NULL, 10);
                _is_valid = true;
            }
        }
    } while (!_is_valid);
    free(buffer);
    return _value;
}
char* get_llong_string (int size, long long min_val, long long max_val) {
    setlocale (LC_ALL, "");
    bool _is_valid = false;
    const int buffer_size = size + 1;
    char *buffer;
    buffer = get_buffer (buffer_size);
    do {
        fill_endline (buffer, buffer_size);
        fgets (buffer, buffer_size + 1, stdin);
        fflush (stdin);
        replace_newendline (buffer, buffer_size);

        if (valid_data (buffer, buffer_size)) {
            if (valid_llong (buffer, min_val, max_val)) {
                _is_valid = true;
            }
        }
    } while (!_is_valid);
    return buffer;
}

double get_double (int size, double min_val, double max_val, int max_acc) {
    setlocale (LC_ALL, "");
    bool _is_valid = false;
    const int buffer_size = size + 1;
    double _value = 0.0;
    char *buffer;
    buffer = get_buffer (buffer_size);
    do {
        fill_endline (buffer, buffer_size);
        fgets (buffer, buffer_size + 1, stdin);
        fflush (stdin);
        replace_newendline (buffer, buffer_size);

        if (valid_data (buffer, buffer_size)) {
            if (valid_double (buffer, buffer_size, min_val, max_val, max_acc)) {
                _value = strtod (buffer, NULL);
                _is_valid = true;
            }
        }
    } while (!_is_valid);
    free (buffer);
    return _value;
}
char* get_double_string (int size, double min_val, double max_val, int max_acc) {
    setlocale (LC_ALL, "");
    bool _is_valid = false;
    const int buffer_size = size + 1;
    char *buffer;
    buffer = get_buffer (buffer_size);
    do {
        fill_endline (buffer, buffer_size);
        fgets (buffer, buffer_size + 1, stdin);
        fflush (stdin);
        replace_newendline (buffer, buffer_size);

        if (valid_data (buffer, buffer_size)) {
            if (valid_double (buffer, buffer_size, min_val, max_val, max_acc)) {
                _is_valid = true;
            }
        }
    } while (!_is_valid);
    char* output = get_buffer(size);
    strcpy(output, buffer);
    free(buffer);
    return output;
}
bool get_bool (wchar_t* operation_1, wchar_t* operation_2) {
    setlocale (LC_ALL, "");
    bool _is_valid = false;
    const int buffer_size = 2;
    bool _value = false;
    char* buffer;
    buffer = get_buffer (buffer_size);
    do {
        fill_endline (buffer, buffer_size);
        wprintf (L"Введіть 1, щоб %ls або 0, щоб %ls:\n", operation_1, operation_2);
        fgets (buffer, buffer_size + 1, stdin);
        fflush (stdin);
        replace_newendline (buffer, buffer_size);

        if (valid_bool (buffer)) {
            _value = (int) strtol (buffer, NULL, 10);
            _is_valid = true;
        }
    } while (!_is_valid);
    return _value;
}
char* get_string (int size) {
    int buffer_size = size + 2;
    bool is_valid = false;
    char* buffer = get_buffer(buffer_size);
    do {
        fill_endline(buffer, buffer_size);
        fgets(buffer, buffer_size + 2, stdin);
        fflush(stdin);
        if (valid_string(buffer, buffer_size)) {
            is_valid = true;
        }
    } while (!is_valid);
    replace_newendline(buffer, buffer_size);
    return buffer;
}
wchar_t* get_wstring (wchar_t* text, int size) {
    bool is_valid_wstring = false;
    wchar_t* wstring;
    wprintf(L"Введіть %ls (Максимальна довжина %d символів)\n", text, size);
    do {
        wstring = get_wbuffer(size);
        fgetws(wstring, size + 2, stdin);
        if (wstring[size] != L'\000') {
            wprintf(L"Назва занадто довга! Спробуйте іншу\n");
            free(wstring);
        } else {
            is_valid_wstring = true;
        }
    } while (!is_valid_wstring);
    return wstring;
}
//----//