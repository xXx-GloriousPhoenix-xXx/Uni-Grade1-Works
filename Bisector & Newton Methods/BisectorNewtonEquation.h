#ifndef PROJECTS_BISECTORNEWTONEQUATION_H
#define PROJECTS_BISECTORNEWTONEQUATION_H

#include <stdbool.h>

#define BISECTOR_METHOD 1
#define NEWTON_METHOD 2
#define METHODS_QUANTITY 2
#define METHOD_SIZE 1

#define TRIGONOMETRY_FUNCTION 1
#define TRIGONOMETRY_LOGARITHMIC_FUNCTION 2
#define FUNCTION_QUANTITY 2
#define FUNCTION_SIZE 1

data get_data (void);

double trig_equation (double x, double t);
double trig_log_equation (double x, double t);

bool is_valid_arguments (double a, double b, int task);
double bisector (double (*f) (double, double), data info);
double newton (double (*f) (double, double), data info);

void limitation_message (void);
void get_functions_list (void);
void get_methods_list (void);

#endif //PROJECTS_BISECTORNEWTONEQUATION_H

