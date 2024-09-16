#define task 1
#ifdef task

    #if task == 1
        #include "n_root.h"
    #elif task == 2
        #include "calendar.h"
    #elif task == 3
        #include "cubic_equation.h"
    #endif

    int main() {
        #if task == 1
            limitation_message();
            double argument = 0;
            int power = 0;
            double precision = 0;
            double result = 0;
            bool undefined_value_case = false;
            do {
                undefined_value_case = false;
                argument = get_argument(ARGUMENT_BUFFER_SIZE);
                power = get_power(POWER_BUFFER_SIZE,argument, &undefined_value_case);
                if (undefined_value_case)
                    continue;
                precision = get_precision(PRECISION_BUFFER_SIZE);
                result = get_root(argument, power, precision);
                printf("Result:%.*lf\n", (int)fabs(log10(precision)), result);
                fflush(stdin);
            } while (get_statement(STATEMENT_BUFFER_SIZE));
        #elif task == 2
            limitation_message();
            do {
                int day = 0;
                int month = 0;
                int year = 0;
                get_date(DATE_BUFFER_SIZE, &day, &month, &year);
                calculate_day_of_week(day, month, year);
            } while(get_statement(STATEMENT_BUFFER_SIZE));
        #elif task == 3
            limitation_message();
            do {
                int a = get_number(COEFFICIENT_BUFFER_SIZE, "(by x squared)");
                int b = get_number(COEFFICIENT_BUFFER_SIZE, "(by x)");
                int c = get_number(COEFFICIENT_BUFFER_SIZE, "(free)");
                get_solution(a, b, c);
            } while(get_statement(STATEMENT_BUFFER_SIZE));
        #endif
        return 0;
    }

#endif