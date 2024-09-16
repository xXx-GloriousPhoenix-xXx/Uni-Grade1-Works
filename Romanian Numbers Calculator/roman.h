#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool in_bool() {
    bool value;
    bool flag = false;
    const unsigned short buff_length = 10;
    char buff[buff_length];
    while (!flag) {
        printf("Enter 0 to exit programme or 1 else to continue:");
        fgets(buff, 9, stdin);
        for (unsigned short i = 0; i < buff_length; i++) {
            if (buff[i] == '\n' || buff[i] == '\0') {
                break;
            }
            if (buff[0] == '0' || buff[0] == '1') {
                flag = 1;
            }
            if (i > 0 && buff[i] != ' ') {
                flag = 0;
                break;
            }
        }
        if (!flag) {
            printf("Invalid input.\n");
        }
    }
    sscanf(buff, "%d", &value);
    return value;
}
unsigned short in_number() {
    const unsigned short length = 10;
    char buff[length];
    unsigned short num;
    unsigned short global_valid = false;
    unsigned short local_valid;
    const unsigned short max_digits = 4;
    const char numbers[] = {'1', '2', '3', '4', '5',
                        '6', '7', '8', '9', '0'};
    while (!global_valid) {
        global_valid = false;
        printf("Enter the arabic number:");
        fgets(buff, length - 1, stdin);
        for (unsigned short i = 0; i < length; i++) {
            if (buff[i] == '\n') {
                if (i < max_digits) {
                    global_valid = true;
                }
                break;
            }
            local_valid = false;
            for (unsigned short j = 0; j < length; j++) {
                if (local_valid) {
                    break;
                }
                if (buff[i] == numbers[j]) {
                    local_valid = true;
                }
            }
            if (local_valid) {
                global_valid = true;
            }
            else {
                global_valid = false;
                break;
            }
        }
        if (global_valid) {
            sscanf(buff, "%hu", &num);
            if (num > 0 && num < 4000) {
                global_valid = true;
            }
            else {
                printf("Invalid input\n");
                global_valid = false;
            }
        }
        else {
            printf("Invalid input.\n");
        }
        if (buff[0] == '0') {
            global_valid = false;
            printf("Invalid input.\n");
        }
    }
    return num;
}
void roman(unsigned short num) {
    const char* arr_rom[] = {"M","CM","D","CD","C","XC", "L",
                        "XL", "X", "IX", "V", "IV", "I"};
    const int arr_ara[] = {1000, 900, 500, 400, 100, 90,
                      50,40, 10, 9, 5, 4, 1};
    const unsigned short max_length_of_roman = 15;
    char line[max_length_of_roman + 1] = {};
    line[max_length_of_roman] = '\0';
    unsigned short i = 0;
    while (num > 0) {
        if (arr_ara[i] > num) {
            i++;
        } else {
            num = num - arr_ara[i];
            strcat(line, arr_rom[i]);
            i = 0;
        }
    }
    printf("The answer is: %s\n", line);
}