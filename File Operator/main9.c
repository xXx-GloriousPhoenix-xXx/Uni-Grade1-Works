#include "libs.h"
#include "menu.h"
#include "defines.h"

int main(void) {
    _setmode(_fileno(stdout), _O_U16TEXT);

    int active_row = ROW_1;
    int active_element = CREATE_FILE;

    int* sorted_records = (int*) calloc (COLUMN_QUANTITY, sizeof(int));
    int case_id = 0;
    do {
        system("cls");
        wprintf_menu(active_row, active_element);
        case_id = operate_ui(&active_row, &active_element, sorted_records);
    } while (case_id != QUIT);
    system("cls");

    free (sorted_records);
    return 0;
}