//Бібліотеки
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

//Препроцессорні константи
#define ld long double
#define us unsigned short

//Фунції для розрахування довжин відрізків
ld get_height(const ld a, const ld b, const ld c) {
    const ld p = (a + b + c) / 2;
    return 2 * sqrtl(p * (p - a) * (p - b) * (p - c)) / a;
}
ld get_median(const ld a, const ld b, const ld c) {
    return sqrtl(2 * b * b + 2 * c * c - a * a) / 2;
}
ld get_bisector(const ld a, const ld b, const ld c) {
    const ld p = (a + b + c) / 2;
    return 2 * sqrtl(b * c * p * (p - a)) / (b + c);
}
ld get_square(const ld a, const ld b, const ld c) {
    const ld p = (a + b + c) / 2;
    return sqrtl(p * (p - a) * (p - b) * (p - c));
}
ld get_perimeter(const ld a, const ld b, const ld c) {
    return a + b + c;
}
void calculate(const ld a, const ld b, const ld c) {
    const us precision = 10;
    printf("Square of triangle: %.*Lf\n", precision, get_square(a, b, c));

    printf("Perimeter of triangle %.*Lf\n", precision, get_perimeter(a, b, c));

    printf("Height to side a: %.*Lf\n", precision, get_height(a, b, c));
    printf("Height to side b: %.*Lf\n", precision, get_height(b, c, a));
    printf("Height to side c: %.*Lf\n", precision, get_height(c, a, b));

    printf("Median to side a: %.*Lf\n", precision, get_median(a, b, c));
    printf("Median to side b: %.*Lf\n", precision, get_median(b, c, a));
    printf("Median to side c: %.*Lf\n", precision, get_median(c, a, b));

    printf("Bisector to side a: %.*Lf\n", precision, get_bisector(a, b, c));
    printf("Bisector to side b: %.*Lf\n", precision, get_bisector(b, c, a));
    printf("Bisector to side c: %.*Lf\n", precision, get_bisector(c, a, b));
}

//Фунція для вводу даних у буфер
ld num_in(const char side) {
    ld num;
    char *num_ptr;
    const us buff_size = 30;
    char buff[buff_size + 1];
    bool is_valid = false;
    do {
        printf("Enter the length of side %c:\n", side);
        fgets(buff, buff_size, stdin);
        ld temp_num = strtold(buff, &num_ptr);
        if ((bool)temp_num && *num_ptr == '\n') {
            num = strtold(buff, NULL);
            is_valid = true;
        } else {
            printf("Invalid input.\n");
            fflush(stdin);
            fflush(stdout);
        }
    } while (!is_valid);
    return num;
}
bool bool_in() {
    const us buff_size = 20;
    char buff[buff_size + 1];
    printf("Enter 1 to continue or anything else to exit:\n");
    fgets(buff, buff_size, stdin);
    return strtod(buff, NULL) == 1;
}

//Функція для тестування довжин сторін та запуску обробки розрахунків
void test_cases(const ld a, const ld b, const ld c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Length of sides must be positive.\n");
        fflush(stdin);
        fflush(stdout);
    } else if (a + b <= c || a + c <= b || b + c <= c) {
        printf("Invalid lengths of sides.\n");
        fflush(stdin);
        fflush(stdout);
    } else {
        calculate(a, b, c);
    }
}

//Функція повідомлення обмежень вводу
void warning_message() {
    printf("Warning!\n"
           "The difference between exponents of a number should be no more than 10 or result may contain fault.\n"
           "The difference between exponents of sides also must be less or equal 10 or result will be unexpected.\n"
           "Algorithm accepts both conventional and scientific notation,\n"
           "but the length of input must should be 20 or less symbols, anything else will be ignored.\n");
}