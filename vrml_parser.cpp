#include "vrml_parser.h"




GlobalVar *gvar = NULL;

/*************************************************************************************/

/*************************************************************************************/


void init_gvar(map<string, DataType> *node_type_map, map<DataType, DataSup *> *type_sup_map,
               map<string, DataType> *field_type_map, stack<string> *file_stack,
               map<string, Container *> *def_map, map<string, void *> *def_map2)
{
    if (gvar == NULL) {
        gvar = new GlobalVar;
    }

    gvar->node_type_map = node_type_map;
    gvar->type_sup_map = type_sup_map;
    gvar->field_type_map = field_type_map;
    gvar->file_stack = file_stack;
    gvar->def_map = def_map;
    gvar->def_map2 = def_map2;
    gvar->frame = NULL;
    gvar->def_flag = 0;
    gvar->use_flag = 0;
    gvar->def_tokn = "";
    gvar->use_tokn = "";
}

/*************************************************************************************/

/*************************************************************************************/

map<string, DataType> *get_node_type_map()
{
    return gvar->node_type_map;
}


/*************************************************************************************/

/*************************************************************************************/

map<DataType, DataSup *> *get_type_sup_map()
{
    return gvar->type_sup_map;
}


/*************************************************************************************/

/*************************************************************************************/

map<string, Container *> *get_def_map()
{
    return gvar->def_map;
}

/*************************************************************************************/

/*************************************************************************************/

map<string, DataType> *get_field_type_map()
{
    return gvar->field_type_map;
}


/*************************************************************************************/

/* Stack */

/*************************************************************************************/


void init_stack(stack<string> **file_stack)
{

    if (*file_stack == NULL) {
        *file_stack = new stack<string>;
    }
}

/*************************************************************************************/

/*************************************************************************************/

int check_tokn_to_add_stack(string tokn)
{
    int value = 0;
    map<string, DataType> *node_type_map = NULL;
    map<string, DataType>::iterator node_type_map_it;

    node_type_map = gvar->node_type_map;
    node_type_map_it = node_type_map->find(tokn);

    if (node_type_map) {

        if (tokn.find("{") != string::npos) {
            value = 1;
        } else if (tokn.find("}") != string::npos) {
            value = 1;
        } else if (node_type_map_it != node_type_map->end()) {
            value = 1;
        }
    }

    return value;
}

/*************************************************************************************/

/*************************************************************************************/

string top_stack()
{
    stack<string> *file_stack = NULL;
    file_stack = gvar->file_stack;
    string value;

    if (file_stack) {
        value = file_stack->top();
    }

    return value;
}

/*************************************************************************************/

/*************************************************************************************/

int check_matching_bracket(string tokn)
{
    int value = 0;

    if (top_stack() == "{" && tokn == "}") {
        value = 1;
    }
    return value;
}

/*************************************************************************************/

/*************************************************************************************/

int top_is_bracket()
{
    int value = 0;
    string top;

    top = top_stack();

    if (top == "}" || top == "{") {
        value = 1;
    }
    return value;
}

/*************************************************************************************/

/*************************************************************************************/

int size_stack()
{
    stack<string> *file_stack = NULL;
    file_stack = gvar->file_stack;
    int value = 0;

    if (file_stack) {
        value = file_stack->size();
    }

    return value;
}

/*************************************************************************************/

/*************************************************************************************/

void push_stack(string tokn)
{
    stack<string> *file_stack = NULL;
    file_stack = gvar->file_stack;
    string value;

    if (file_stack) {
        file_stack->push(tokn);
    }
}

/*************************************************************************************/

/*************************************************************************************/

void pop_stack()
{
    stack<string> *file_stack = NULL;
    file_stack = gvar->file_stack;
    string value;

    if (file_stack) {
        file_stack->pop();
    }
}

/*************************************************************************************/

/*************************************************************************************/

void perform_stack_operations(string tokn)
{

    if (check_tokn_to_add_stack(tokn)) {

        if (size_stack()) {

            if (check_matching_bracket(tokn)) {

                // pop brackets
                pop_stack();

                if (!top_is_bracket()) {

                    //pop keyword
                    pop_stack();

                }

            } else {

                push_stack(tokn);

            }

        } else {

            push_stack(tokn);
        }

    }
}

/*************************************************************************************/

/*************************************************************************************/

void stack_operations(string tokn)
{
    perform_stack_operations(tokn);
}

/*************************************************************************************/

/*************************************************************************************/

void debug_stack(string msg)
{

    cout << msg <<endl;
    while (size_stack()) {
        cout << " stack: "<<top_stack() << endl;
        pop_stack();
    }
}

/*************************************************************************************/

/*************************************************************************************/

string get_tokn()
{
    string tokn;

    //tokn = get_token();
    //stack_operations(tokn);

    tokn = get_token();
    stack_operations(tokn);

    // for comments inline
    while (tokn.find_first_of("#") != string::npos) {

        go_to_next_line();
        tokn = get_token();
        stack_operations(tokn);

    }

    check_def_tokn(tokn);
    check_use_tokn(tokn);

    return tokn;
}


/*************************************************************************************/

/*************************************************************************************/



void check_shape(Container *container)
{
    PointSet *point_set = NULL;
    Coordinate *coordinate = NULL;
    vector<Point *> *coordinate_vec = NULL;
    vector<Point *>::iterator it;
    Point *point = NULL;
    Shape *shape = NULL;

    shape = (Shape *) get_container_data(container);

    if (shape) {

        point_set = shape->point_set;

        if (point_set) {

            coordinate = point_set->coordinate;
            if (coordinate) {

                coordinate_vec = coordinate->coordinate_vec;
                if (coordinate_vec) {
                    for (it = coordinate_vec->begin(); it != coordinate_vec->end(); ++it) {
                        point = *it;
                        if (point)
                            cout << "r_shape value: x = " << point->x << " y = " << point->y << " z = "
                                 << point->z << endl;
                    }
                }
            }
        }
    }
}

/*************************************************************************************/

/*************************************************************************************/

void check_read_point_set(void *args)
{
    Coordinate *coordinate = NULL;
    vector<Point *> *coordinate_vec = NULL;
    vector<Point *>::iterator it;
    Point *point = NULL;
    PointSet *point_set = NULL;

    point_set = (PointSet *)args;

    if (point_set) {

        coordinate = point_set->coordinate;
        if (coordinate) {
            coordinate_vec = coordinate->coordinate_vec;
            if (coordinate_vec) {
                for (it = coordinate_vec->begin(); it != coordinate_vec->end(); ++it) {
                    point = *it;
                    if (point)
                        cout << "r_point_set value: x = " << point->x << " y = " << point->y << " z = " << point->z << endl;
                }
            }
        }
    }
}


void check_shape2(void *args)
{
    PointSet *point_set = NULL;
    Coordinate *coordinate = NULL;
    vector<Point *> *coordinate_vec = NULL;
    vector<Point *>::iterator it;
    Point *point = NULL;
    Shape *shape = NULL;

    shape = (Shape *)args;

    if (shape) {

        point_set = shape->point_set;

        if (point_set) {

            coordinate = point_set->coordinate;
            if (coordinate) {

                coordinate_vec = coordinate->coordinate_vec;
                if (coordinate_vec) {
                    for (it = coordinate_vec->begin(); it != coordinate_vec->end(); ++it) {
                        point = *it;
                        if (point)
                            cout << "r_shape value: x = " << point->x << " y = " << point->y << " z = "
                                 << point->z << endl;
                    }
                }
            }
        }
    }
}

void check_transform2(void *args)
{

    int i;
    DataType type;
    void *data = NULL;

    data = args;



    if (data) {

        while (data != NULL) {

            type = get_node_type(data);

            if (type == SHAPE) {


                check_shape2(data);
                data = NULL;

            } else if ( type == TRANSFORM) {

                Transform *transform = (Transform *)data;

                for (i = 0; i < 3; i++) {
                    cout << "translation[" << i << "] -> " << transform->translation[i] << endl;
                }


                for (i = 0; i < 3; i++) {
                    cout << "scale[" << i << "] -> " << transform->scale[i] << endl;
                }


                for (i = 0; i < 4; i++) {
                    cout << "rotation[" << i << "] -> " << transform->rotation[i] << endl;
                }

                data = transform->children;

            } else {
                data = NULL;
            }
        }
    }
}

/*************************************************************************************/

/*************************************************************************************/

void check_frame(vector<Container *> *frame)
{
    vector<Container *>::iterator it;
    DataType type = UNKNOWN;


    for (it = frame->begin(); it != frame->end(); ++it) {

        type = get_container_type((Container *)*it);

        if (type == SHAPE) {
            cout << "SHAPE" << endl;
            check_shape(*it);
        } else if (type == TRANSFORM) {
            //check_transform(*it);
        }
    }
}


/*************************************************************************************/

/*************************************************************************************/


void debug_def2()
{
    map<string, void *>::iterator def_map_it;
    map<string, void *> *def_map = NULL;

    def_map = gvar->def_map2;
    int i = 0;

    if (def_map) {

        for (def_map_it = def_map->begin(); def_map_it != def_map->end(); ++def_map_it) {
            cout << "def map key: " << def_map_it->first <<"   value: " << def_map_it->second << endl;
            i++;
            if (i == 1) {
                cout << endl << "@@@@@@@@@@   TRANSFORM  @@@@@@@@@@@" << endl;
               check_transform2(def_map_it->second);
            }
            if (i == 2) {
                cout << endl << "@@@@@@@@@@   SHAPE  @@@@@@@@@@@" << endl;
                check_shape2(def_map_it->second);

            }

            if (i == 3) {
                cout << endl << "@@@@@@@@@@   POINTSET  @@@@@@@@@@@" << endl;
                check_read_point_set(def_map_it->second);

            }
        }
    }
}



/*************************************************************************************/

/*************************************************************************************/

void *call_node_read_function(string tokn, void *args)
{

    map<string, DataType> *node_type_map = NULL;
    map<string, DataType>::iterator node_type_map_it;

    map<DataType, DataSup *> *type_sup_map = NULL;
    map<DataType, DataSup *>::iterator type_sup_map_it;

    void *data = NULL;

    node_type_map = get_node_type_map();
    type_sup_map = get_type_sup_map();

    node_type_map_it = node_type_map->find(tokn);

    if (node_type_map_it != node_type_map->end()) {

        type_sup_map_it = type_sup_map->find(node_type_map_it->second);

        if (type_sup_map_it != type_sup_map->end()) {

            data = type_sup_map_it->second->read_node_fun(args);
        }
    }
    return data;
}

/*************************************************************************************/

/*************************************************************************************/


void *call_field_read_function(string tokn, void *args)
{

    map<string, DataType> *field_type_map = NULL;
    map<string, DataType>::iterator field_type_map_it;

    map<DataType, DataSup *> *type_sup_map = NULL;
    map<DataType, DataSup *>::iterator type_sup_map_it;

    void *data = NULL;

    field_type_map = get_field_type_map();
    type_sup_map = get_type_sup_map();

    field_type_map_it = field_type_map->find(tokn);

    if (field_type_map_it != field_type_map->end()) {

        type_sup_map_it = type_sup_map->find(field_type_map_it->second);

        if (type_sup_map_it != type_sup_map->end()) {

            data = type_sup_map_it->second->read_field_fun(args);
        }
    }
    return data;
}

/*************************************************************************************/

/*************************************************************************************/

void read_vrml()
{
    string tokn;
    ifstream *fp = NULL;

    map<string, DataType> *node_type_map = NULL;

    map<DataType, DataSup *> *type_sup_map = NULL;

    map<string, DataType> *field_type_map = NULL;

    stack<string> *file_stack = NULL;

    vector<Container *> *frame = NULL;

    map<string, Container *> *def = NULL;

    map<string, void *> *def_map2 = NULL;

    void *data = NULL;

    DataType data_type = UNKNOWN;

    init_node_type_map(&node_type_map);
    init_field_type_map(&field_type_map);
    init_type_sup_map(&type_sup_map);
    init_stack(&file_stack);
    init_frame(&frame);
    init_def(&def);
    init_def_map2(&def_map2);

    init_gvar(node_type_map, type_sup_map, field_type_map, file_stack, def, def_map2);

    gvar->frame = frame;

    int i = 0;
    int def_flag = 0;
    string def_tokn;

    //fp = open_file("/home/alepapadop/VRML/5pointset.wrl");
    //fp = open_file("/home/alepapadop/VRML/a.wrl");
    fp = open_file("/home/alepapadop/VRML/good_def_use_example.wrl");

    while (fp->good()) {

        tokn = get_tokn();

        if (gvar->def_flag) {
            def_flag = 1;
            def_tokn = gvar->def_tokn;
            //gvar->def_flag = 0;
            //gvar->def_tokn = "";
        }

        data = call_node_read_function(tokn, NULL);

        if (def_flag && data !=NULL) {
            add_to_def(def_tokn, (Container *)data);
            add_to_def_map(def_tokn, data);
            //(*(gvar->def_map2))[def_tokn] = data;
        }
        if (data != NULL) {
            frame->push_back((Container *)data);
        }
        data = NULL;


        // lthos auto, edw einai pou tha mpainei sto file data to frame
        if (!size_stack()) {
            init_frame(&frame);
            gvar->frame = frame;
        }

        data_type = UNKNOWN;
        i ++;
        if (i == 100) break;
    }
    check_frame(frame);
    debug_stack("\nSTACK \n\n");
//    debug_def();
    debug_def2();
}






