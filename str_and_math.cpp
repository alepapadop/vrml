#include "str_and_math.h"

using namespace std;

int is_number(string s)
{
    string::const_iterator it = s.begin();

    while (it != s.end() && ( isdigit(*it) || *it == '.' || *it == '-')) {
        ++it;
    }
    return !s.empty() && it == s.end();
}


double str2double(string str, int *valid_flag)
{
    char *endptr = NULL;
    double value = strtod(str.c_str(), &endptr);

    if (*endptr) {
        *valid_flag = 0;
    }

    return value;
}

int find_comma_and_remove_it(string *tokn)
{
    int pos = 0;
    int value = 0;

    if ( (pos = tokn->find_first_of(",")) != string::npos) {
        *tokn = tokn->substr(0, pos);
        value = 1;
    }

    return value;
}
