#ifndef VRML_PARSER_H
#define VRML_PARSER_H

#include <string>
#include <stack>
#include "file_handler.h"
#include "data_types.h"

using namespace std;

typedef struct GlobalVar {

    map<string, DataType> *node_type_map;
    map<DataType, DataSup *> *type_sup_map;

    map<string, DataType> *field_type_map;

    map<string, Container *> *def_map;

    map<string, void *> *def_map2;

    stack<string> *file_stack;
    vector<Container *> *frame;


    int def_flag;
    int use_flag;
    string def_tokn;
    string use_tokn;

} GlobalVar;

void read_vrml();
string get_tokn();
void *call_node_read_function(string tokn, void *args);
void *call_field_read_function(string tokn, void *args);

extern GlobalVar *gvar;

#endif // VRML_PARSER_H
