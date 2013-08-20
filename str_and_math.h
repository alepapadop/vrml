#ifndef STR_AND_MATH_H
#define STR_AND_MATH_H

#include <string>
#include <cstdlib>

using namespace std;

int is_number(string s);
double str2double(string str, int *valid_flag);
int find_comma_and_remove_it(string *tokn);


#endif // STR_AND_MATH_H
