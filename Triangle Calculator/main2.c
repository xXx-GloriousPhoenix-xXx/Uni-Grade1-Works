//Включення файла з бібліотеками
#include "triangle.h"

//Головна функція
int main() {
    warning_message();
    bool repeat;
    do {
        const ld a = num_in('a');
        const ld b = num_in('b');
        const ld c = num_in('c');
        test_cases(a, b, c);
        repeat = bool_in();
        fflush(stdin);
        fflush(stdout);
    } while (repeat);
    return 0;
}