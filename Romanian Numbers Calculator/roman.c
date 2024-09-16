#include "roman.h"
#define console_hold 0
#if console_hold == 1
    #include <conio.h>
#endif
int main() {
    bool flag = true;
    while (flag) {
        unsigned short num = in_number();
        roman(num);
        flag = in_bool();
    }
#if console_hold == 1
    getch();
#endif
    return 0;
}