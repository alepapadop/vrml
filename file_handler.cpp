#include "file_handler.h"

using namespace std;


vector<string> *token_stack = NULL;
ifstream *fp = NULL;

void init_token_stack()
{
    if (token_stack == NULL) {
        token_stack = new vector<string>;
    }
}

void close_file(ifstream *fp)
{

    fp->close();

}


ifstream *open_file(string file_name)
{

    fp = new ifstream();
    fp->open(file_name.c_str());

    if (fp->is_open()) {
        init_token_stack();
        return fp;

    } else {
        cout << "Unable to open file" << endl;
        close_file(fp);
        return NULL;
    }
}




void empty_token_stack()
{
    // opote adeiazei to stack to programma paei kai tsimpaei nea grammi
    // apo to arxeio
    token_stack->erase(token_stack->begin(), token_stack->end());
}

void trim(string *s)
{
    size_t p = s->find_first_not_of(" \t");
    s->erase(0, p);

    p = s->find_last_not_of(" \t");
    if (string::npos != p)
    s->erase(p+1);
}

string *read_line(string *line)
{

    if (fp->good()) {

        getline(*fp, *line);
        trim(line);

        //cout << "line: " << *line << endl;

    } else {
        line->clear();
    }
    return line;
}

void go_to_next_line()
{
    empty_token_stack();
}


int is_blank(string token)
{
    size_t value = 0;

    if (token.find_first_not_of("\t\n ") == string::npos) {
        //string is blank
        value = 1;
    }

    return value;

}



void tokenize_line(string line)
{

    size_t  next = 0;
    size_t  prev = 0;
    string delimiter = " ";
    string substring;

    while ((next = line.find_first_of(delimiter, prev)) != string::npos) {

        if (next - prev != 0) {

            substring = line.substr(prev, next - prev);

            if (!is_blank(substring)) {

                token_stack->push_back(substring);
            }
        }
        prev = next + 1;
    }

    if (prev < line.size()) {

        substring = line.substr(prev);

        if (!is_blank(substring)) {

            token_stack->push_back(substring);

        }
    }
}


string get_token()
{

    string value, line;


    if (!token_stack->empty()) {
        value = token_stack->front();
        token_stack->erase(token_stack->begin());
    } else {
        read_line(&line);
        if (line.size() != 0) {
            tokenize_line(line);
            value = token_stack->front();
            token_stack->erase(token_stack->begin());
        }
    }

    //cout << "tokn: " << value << endl;
    return value;

}
