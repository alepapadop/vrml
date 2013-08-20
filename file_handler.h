#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream *open_file(string file_name);
string get_token();
void go_to_next_line();

#endif // FILE_HANDLER_H
