#include "data_types.h"
#include "str_and_math.h"
#include "file_handler.h"
#include "vrml_parser.h"
#include <iostream>

using namespace std;

/*************************************************************************************/

/*************************************************************************************/

void check_def_tokn(string tokn)
{

    if (tokn.find("DEF") != string::npos) {

        gvar->def_flag = 1;
        gvar->def_tokn = get_tokn();

    }

}

/*************************************************************************************/

/*************************************************************************************/


void check_use_tokn(string tokn)
{

    if (tokn.find("USE") != string::npos) {
        gvar->use_flag = 1;


    }

}


/*************************************************************************************/

/*************************************************************************************/


void add_to_def(string tokn, Container *container)
{
    // eukolaki vazeis sto map perneis apo to map
    // o kwdika tha mpei mesa stin get_tokn opote
    // den tha mplexoume me ta alla
    // prepei na kanw kai ta alla na epistrefoun container
    // episi na kanw kai to group
    // poly testing para poly :)

    if (gvar->def_map) {
        (*(gvar->def_map))[tokn] = container;
    }
    gvar->def_flag = 0;
    gvar->def_tokn = "";
}

/*************************************************************************************/

/*************************************************************************************/


void* get_from_def(string tokn)
{
    //otan epistrefo to grafo amesws sto frame mesw tis global var
    Container *container = NULL;
    map<string, Container *>::iterator it;

    if (gvar->def_map) {
        it = gvar->def_map->find(tokn);
        if (it != gvar->def_map->end()) {
            container = it->second;
        }
    }
    gvar->use_flag = 0;

    return container;
}

/*************************************************************************************/

/*************************************************************************************/

Container *new_container()
{
    Container *container = NULL;

    container = new Container;

    return container;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_container(Container *container)
{
    delete container;
}

/*************************************************************************************/

/*************************************************************************************/

void set_container_type(Container *container, DataType type)
{
    if (container) {
        container->type = type;
    }
}

/*************************************************************************************/

/*************************************************************************************/

void set_container_data(Container *container, void *data)
{
    if (container) {
        container->data = data;
    }
}

/*************************************************************************************/

/*************************************************************************************/

DataType get_container_type(Container *container)
{
    DataType type = UNKNOWN;

    if (container) {
        type = container->type;
    }
    return type;
}

/*************************************************************************************/

/*************************************************************************************/

void *get_container_data(Container *container)
{
    void *data = NULL;

    if (container) {
        data = container->data;
    }
    return data;
}

/*************************************************************************************/

/*************************************************************************************/

void init_node_type_map(map<string, DataType> **node_type_map)
{
    if (*node_type_map == NULL) {
        *node_type_map = new map<string, DataType>;
    }

    (**node_type_map)["Shape"] = SHAPE;
    (**node_type_map)["Group"] = GROUP;
    (**node_type_map)["Coordinate"] = COORDINATE;
    (**node_type_map)["IndexedLineSet"] = INDEXED_LINE_SET;
    (**node_type_map)["IndexedFaceSet"] = INDEXED_FACE_SET;
    (**node_type_map)["Transform"] = TRANSFORM;
    (**node_type_map)["Material"] = MATERIAL;
    (**node_type_map)["PointSet"] = POINT_SET;
    (**node_type_map)["Appearance"] = APPEARANCE;


}

/*************************************************************************************/

/*************************************************************************************/


void init_field_type_map(map<string, DataType> **field_type_map)
{
    if (*field_type_map == NULL) {
        *field_type_map = new map<string, DataType>;
    }

    (**field_type_map)["translation"] = TRANSLATION;
    (**field_type_map)["rotation"] = ROTATION;
    (**field_type_map)["scale"] = SCALE;
    (**field_type_map)["point"] = POINT;
}

/*************************************************************************************/

/*************************************************************************************/

DataSup *add_type_sup_map(string keyword, DataType type, READ_NODE_FUN read_node_fun,
                          READ_FIELD_FUN read_field_fun, CREATE_FUN create_fun)
{
    DataSup *data_sup = NULL;

    data_sup = new DataSup;

    if (data_sup) {
        data_sup->keyword = keyword;
        data_sup->type = type;
        data_sup->read_node_fun = read_node_fun;
        data_sup->read_field_fun = read_field_fun;
        data_sup->create_fun = create_fun;
    }

    return data_sup;
}


/*************************************************************************************/

/*************************************************************************************/

void init_type_sup_map(map<DataType, DataSup *> **type_sup_map)
{

    if (*type_sup_map == NULL) {
        *type_sup_map = new map<DataType, DataSup *>;
    }

    /* NODE FUNCTIONS */
    (**type_sup_map)[COORDINATE] = add_type_sup_map("Coordinate", COORDINATE ,read_coordinate, NULL, NULL);
    (**type_sup_map)[POINT_SET] = add_type_sup_map("PointSet", POINT_SET ,read_point_set, NULL, NULL);
    (**type_sup_map)[SHAPE] = add_type_sup_map("Shape", SHAPE ,read_shape, NULL, NULL);
    (**type_sup_map)[TRANSFORM] = add_type_sup_map("Transform", TRANSFORM, read_transform, NULL, NULL);

    /* FIELD FUNCTIONS */
    (**type_sup_map)[TRANSLATION] = add_type_sup_map("translation", TRANSLATION, NULL, read_translation, NULL);
    (**type_sup_map)[ROTATION] = add_type_sup_map("rotation", ROTATION, NULL, read_rotation, NULL);
    (**type_sup_map)[SCALE] = add_type_sup_map("scale", SCALE, NULL, read_scale, NULL);
    (**type_sup_map)[POINT] = add_type_sup_map("point", POINT, NULL, read_point,  NULL);
}




/*************************************************************************************/

/*************************************************************************************/

void init_frame(vector<Container *> **frame)
{
    if (*frame == NULL) {
        *frame =new vector<Container *>;
    }
}

/*************************************************************************************/

/*************************************************************************************/

void init_def(map<string, Container *> **def)
{
    if (*def == NULL) {
        *def = new map<string, Container *>;
    }
}


/*************************************************************************************/

/* Point */

/*************************************************************************************/

Point *new_point()
{
    Point *point = NULL;

    point = new Point;
    return point;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_point(Point *point)
{
    delete point;
}

/*************************************************************************************/

/*************************************************************************************/

void debug_read_point(vector<Point *> *coordinate_vec)
{
    vector<Point *>::iterator it;
    Point *point;

    for (it = coordinate_vec->begin(); it != coordinate_vec->end(); ++it) {
        point = *it;
        if (point)
            cout << "value: x = " << point->x << " y = " << point->y << " z = " << point->z << endl;
    }


}

/*************************************************************************************/

/*************************************************************************************/

void *read_point(void *args)
{
    Point *point = NULL;
    string tokn = "";
    double tmp;
    int valid_flag;
    int flag = 0;
    int count = 0;
    double x, y, z;
    vector<Point *> *coordinate_vec = NULL;

    cout << "Hello read point" << endl;

    coordinate_vec = new vector<Point *>;

    while (tokn.find("]") == string::npos) {

        tokn = get_tokn();

        flag = 0;

        if (find_comma_and_remove_it(&tokn) || tokn.find(",") != string::npos || count == 3) {
            //cout << "tokn " << tokn << endl;
            flag = 1;
        }

        if (is_number(tokn)) {
            valid_flag = 1;

            tmp = str2double(tokn, &valid_flag);

            if (valid_flag) {

                if (count == 0) {
                    x = tmp;
                } else if (count == 1) {
                    y = tmp;
                } else if (count == 2) {
                    z = tmp;
                }
            }
            count ++;
        }

        if (flag == 1) {
            point = new_point();
            if (point) {
                point->x = x;
                point->y = y;
                point->z = z;
                count = 0;
                flag = 0;
                //cout << "read point value: x = " << point->x << " y = " << point->y << " z = " << point->z << endl;
            }

            if (coordinate_vec) {

                coordinate_vec->push_back(point);

            }
            point = NULL;
        }
    }

    //debug_read_point(coordinate_vec);
    return coordinate_vec;
}

/*************************************************************************************/

/* CoordIndex */

/*************************************************************************************/

CoordIndex *new_coord_index()
{
    CoordIndex *coord_index = NULL;
    vector<int> *coord_index_vec = NULL;

    coord_index = new CoordIndex;

    if (coord_index) {
        coord_index_vec = new vector<int>;
        coord_index->coord_index_vec = coord_index_vec;
    }
    return coord_index;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_coord_index(CoordIndex *coord_index)
{
    delete coord_index->coord_index_vec;
    delete coord_index;
}

/*************************************************************************************/

/* Coordinate */

/*************************************************************************************/

Coordinate *new_coordinate()
{
    Coordinate *coordinate = NULL;
    vector<Point *> *coordinate_vec = NULL;

    coordinate = new Coordinate;

    if (coordinate) {
        //coordinate_vec = new vector<Point *>;
        coordinate->coordinate_vec = coordinate_vec;
    }
    return coordinate;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_coordinate(Coordinate *coordinate)
{
    vector<Point *>::iterator it;
    vector<Point *> *coordinate_vec;

    coordinate_vec = coordinate->coordinate_vec;

    for (it = coordinate_vec->begin(); it != coordinate_vec->end(); ++it) {
        delete_point(*it);
    }

    delete coordinate->coordinate_vec;
    delete coordinate;
}

/*************************************************************************************/

/*************************************************************************************/

void debug_read_coordinate(Coordinate *coordinate)
{
    vector<Point *> *coordinate_vec = NULL;
    vector<Point *>::iterator it;
    Point *point = NULL;

    if (coordinate) {
        coordinate_vec = coordinate->coordinate_vec;

        if (coordinate_vec) {
            for (it = coordinate_vec->begin(); it != coordinate_vec->end(); ++it) {
                point = *it;
                if (point)
                    cout << "read_coordinate value: x = " << point->x << " y = " << point->y << " z = " << point->z << endl;
            }
        }
    }
}

/*************************************************************************************/

/*************************************************************************************/


void *read_coordinate(void *data) {

    cout << "Hello coordinate" << endl;

    string tokn = "";
    Coordinate *coordinate = NULL;

    coordinate = new_coordinate();

    if (coordinate) {

        while (tokn.find("}") == string::npos) {

            tokn = get_tokn();

            if (tokn.find("point") != string::npos) {

                coordinate->coordinate_vec = (vector<Point *> *)read_point(coordinate);
            }

        }
    }

    //debug_read_coordinate(coordinate);
    return coordinate;
}


/*************************************************************************************/

/* IndexedLineSet */

/*************************************************************************************/

IndexedLineSet *new_indexed_line_set()
{
    IndexedLineSet *indexed_line_set = NULL;
    Coordinate *coordinate = NULL;
    vector<CoordIndex *> *indexed_line_set_vec = NULL;

    indexed_line_set = new IndexedLineSet;

    if (indexed_line_set) {
        coordinate = new_coordinate();
        indexed_line_set_vec = new vector<CoordIndex *>;

        indexed_line_set->coordinate = coordinate;
        indexed_line_set->indexed_line_set_vec = indexed_line_set_vec;
    }
    return indexed_line_set;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_indexed_line_set(IndexedLineSet *indexed_line_set)
{
    vector<CoordIndex *>::iterator it;
    vector<CoordIndex *> *indexed_line_set_vec;

    indexed_line_set_vec = indexed_line_set->indexed_line_set_vec;

    for (it = indexed_line_set_vec->begin(); it != indexed_line_set_vec->end(); ++it) {
        delete_coord_index(*it);
    }

    delete_coordinate(indexed_line_set->coordinate);
    delete indexed_line_set;

}

/*************************************************************************************/

/* IndexedFaceSet */

/*************************************************************************************/

IndexedFaceSet *new_indexed_face_set()
{
    IndexedFaceSet *indexed_face_set = NULL;
    Coordinate *coordinate = NULL;
    vector<CoordIndex *> *indexed_face_set_vec = NULL;

    indexed_face_set = new IndexedFaceSet;

    if (indexed_face_set) {
        coordinate = new_coordinate();
        indexed_face_set_vec = new vector<CoordIndex *>;

        indexed_face_set->coordinate = coordinate;
        indexed_face_set->indexed_face_set_vec = indexed_face_set_vec;
    }
    return indexed_face_set;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_indexed_face_set(IndexedFaceSet *indexed_face_set)
{
    vector<CoordIndex *>::iterator it;
    vector<CoordIndex *> *indexed_face_set_vec;

    indexed_face_set_vec = indexed_face_set->indexed_face_set_vec;

    for (it = indexed_face_set_vec->begin(); it != indexed_face_set_vec->end(); ++it) {
        delete_coord_index(*it);
    }

    delete_coordinate(indexed_face_set->coordinate);
    delete indexed_face_set;
}

/*************************************************************************************/

/* Material */

/*************************************************************************************/

Material *new_material()
{
    Material *material = NULL;

    material = new Material;
    return material;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_material(Material *material)
{
    delete material;
}

/*************************************************************************************/

/* PointSet */

/*************************************************************************************/

PointSet *new_point_set()
{
    PointSet *point_set = NULL;
    Coordinate *coordinate = NULL;

    point_set = new PointSet;
    if (point_set) {
        //coordinate = new_coordinate();
        point_set->coordinate = coordinate;
    }
    return point_set;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_point_set(PointSet *point_set)
{
    delete_coordinate(point_set->coordinate);
    delete point_set->coordinate;
}

/*************************************************************************************/

/*************************************************************************************/

void debug_read_point_set(PointSet *point_set)
{
    Coordinate *coordinate = NULL;
    vector<Point *> *coordinate_vec = NULL;
    vector<Point *>::iterator it;
    Point *point = NULL;

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

/*************************************************************************************/

/*************************************************************************************/

void *read_point_set(void *args)
{
    cout << "Hello point set" << endl;

    PointSet *point_set = NULL;
    string tokn = "";
    Shape *shape = NULL;

    shape = (Shape *)args;

    point_set = new_point_set();

    if (point_set) {

        while (tokn.find("}") == string::npos) {
            tokn = get_tokn();

            //call_node_read_function(tokn, point_set);

            if (tokn.find("Coordinate") != string::npos) {

                point_set->coordinate = (Coordinate *)read_coordinate(point_set);

            } else if (tokn.find("Color") != string::npos) {
                ;
            }
        }
    }
    if (shape) {
        shape->point_set = point_set;
    }

    //debug_read_point_set(point_set);
    return point_set;

}

/*************************************************************************************/

/* Appearance */

/*************************************************************************************/

Appearance *new_appearance()
{
    Appearance *appearance = NULL;

    appearance = new Appearance;
    return appearance;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_appearance(Appearance *appearance)
{
    delete appearance;
}

/*************************************************************************************/

/* Shape */

/*************************************************************************************/

Shape *new_shape()
{
    Shape *shape = NULL;

    shape = new Shape;
    if (shape) {
        //shape->appearance = new_appearance();
        //shape->point_set = new_point_set();
        //shape->indexed_line_set = new_indexed_line_set();
        //shape->indexed_face_set = new_indexed_face_set();

        shape->appearance = NULL;
        shape->point_set = NULL;
        shape->indexed_line_set = NULL;
        shape->indexed_face_set = NULL;
    }
    return shape;
}


/*************************************************************************************/

/*************************************************************************************/

void delete_shape(Shape *shape)
{
    //delete_appearance(shape->appearance);
    //delete_point_set(shape->point_set);
    //delete_indexed_line_set(shape->indexed_line_set);
    //delete_indexed_face_set(shape->indexed_face_set);
    delete shape;
}


/*************************************************************************************/

/*************************************************************************************/


void debug_read_shape(Container *container)
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

void *read_shape(void *data)
{
    cout << "Hello Shape" << endl;

    Shape *shape = NULL;
    Container *container = NULL;
    string tokn = "";

    shape = new_shape();
    container = new_container();

    if (gvar->def_flag) {
        add_to_def(gvar->def_tokn, container);
    }

    if (shape) {

        while (tokn.find("}") == string::npos) {
            tokn = get_tokn();
            // na pernaw mesa to pedio oxi to struct tha lysei polla provlimata
            call_node_read_function(tokn, shape);

            /*if (tokn.find("PointSet") != string::npos) {

                //shape->point_set = (PointSet *)read_point_set(shape);
                read_point_set(shape);

            } else if (tokn.find("IndexedLineSet") != string::npos) {
                ;
            } else if (tokn.find("IndexedFaceSet") != string::npos) {
                ;
            }*/
        }

        if (container) {
            set_container_type(container, SHAPE);
            set_container_data(container, shape);
        }

    }

    //debug_read_shape(container);
    return container;

}


/*************************************************************************************/

/* Transform */

/*************************************************************************************/

Transform *new_transform()
{
    Transform *transform = NULL;

    transform = new Transform;
    if (transform) {
        transform->children = NULL;
    }
    return transform;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_transform(Transform *transform)
{
    delete transform;
}


/*************************************************************************************/

/*************************************************************************************/

void *read_translation(void *args)
{
    string tokn = "";
    int valid_flag = 1;
    double tmp;
    int i = 0;
    double *translation = NULL;
    Transform *transform = NULL;

    //translation = (double *)args;
    transform = (Transform *)args;

    if (transform) {
        translation = transform->translation;
    }

    if (translation) {
        for (i = 0; i < 3; ++i) {
            tokn = get_token();
            if (is_number(tokn)) {
                tmp = str2double(tokn, &valid_flag);
                if (valid_flag) {
                    translation[i] = tmp;
                }
            }
        }
    }
    return translation;
}

/*************************************************************************************/

/*************************************************************************************/


void *read_scale(void *args)
{
    string tokn = "";
    int valid_flag = 1;
    double tmp;
    int i = 0;
    double *scale = NULL;
    Transform *transform = NULL;

    //scale = (double *)args;
    transform = (Transform *)args;

    if (transform) {
        scale = transform->rotation;
    }

    if (scale) {
        for (i = 0; i < 3; ++i) {
            tokn = get_token();
            if (is_number(tokn)) {
                tmp = str2double(tokn, &valid_flag);
                if (valid_flag) {
                    scale[i] = tmp;
                }
            }
        }
    }
    return scale;
}

/*************************************************************************************/

/*************************************************************************************/


void *read_rotation(void *args)
{
    string tokn = "";
    int valid_flag = 1;
    double tmp;
    int i = 0;
    double *rotation = NULL;
    Transform *transform = NULL;

    //rotation = (double *)args;
    transform = (Transform *)args;

    if (transform) {
        rotation = transform->rotation;
    }
    if (rotation) {
        for (i = 0; i < 4; ++i) {
            tokn = get_token();
            if (is_number(tokn)) {
                tmp = str2double(tokn, &valid_flag);
                if (valid_flag) {
                    rotation[i] = tmp;
                }
            }
        }
    }
    return rotation;
}

/*************************************************************************************/

/*************************************************************************************/

void debug_read_transform(Container *container)
{
    Transform *transform = NULL;
    int i = 0;

    if (container) {


        if (get_container_type(container) == SHAPE)
        {
            cout << "-----" << endl;

            debug_read_shape(container);


        } else if (get_container_type(container) == TRANSFORM) {


                transform = (Transform *)get_container_data(container);

                if (transform) {

                    for (i = 0; i < 3; i++) {
                        cout << "translation[" << i << "] -> " << transform->translation[i] << endl;
                    }


                    for (i = 0; i < 3; i++) {
                        cout << "scale[" << i << "] -> " << transform->scale[i] << endl;
                    }


                    for (i = 0; i < 4; i++) {
                        cout << "rotation[" << i << "] -> " << transform->rotation[i] << endl;
                    }
                }
                Container *tmp_container = NULL;

                tmp_container = (Container *)transform->children;

                debug_read_transform(tmp_container);

        }
    }
}


/*************************************************************************************/

/*************************************************************************************/

void *read_transform(void *data)
{
    cout << "Hello Transform" << endl;

    Transform *transform = NULL;
    string tokn = "";
    Container *container = NULL;

    transform = new_transform();

    if (transform) {

        while (tokn.find("children") == string::npos && tokn.find("}") == string::npos) {

            tokn = get_tokn();

            call_field_read_function(tokn, transform);

            /*if (tokn.find("translation") != string::npos) {

                read_translation(transform->translation);

            } else if (tokn.find("rotation") != string::npos) {

                read_rotation(transform->rotation);

            } else if (tokn.find("scale") != string::npos) {

                read_scale(transform->scale);

            }*/
        }

        if (tokn.find("children") != string::npos) {

            container = new_container();

            if (gvar->def_flag) {
                add_to_def(gvar->def_tokn, container);
                gvar->def_flag = 0;
            }


            while(tokn.find("]") == string::npos) {

                tokn = get_tokn();

                transform->children = call_node_read_function(tokn, NULL);

                if (container) {

                    set_container_type(container, TRANSFORM);
                    set_container_data(container, transform);

                }

                /*if (tokn.find("Shape") != string::npos) {

                    transform->children = read_shape(transform);

                    //container = new_container();

                    if (container) {


                        set_container_type(container, TRANSFORM);
                        set_container_data(container, transform);

                    }

                } else if (tokn.find("Group") != string::npos) {

                    ;

                } else if (tokn.find("Transform") != string::npos) {

                    //container = new_container();



                    transform->children = read_transform(transform);

                    if (container) {


                        set_container_type(container, TRANSFORM);
                        set_container_data(container, transform);

                    }

                } */

            }

        }

    }


    //debug_read_transform(container);
    return container;

}

/*************************************************************************************/

/* Group */

/*************************************************************************************/

Group *new_group()
{
    Group *group = NULL;

    group = new Group;
    if (group) {
        group->children = NULL;
    }
    return group;
}

/*************************************************************************************/

/*************************************************************************************/

void delete_group(Group *group)
{
    delete group;
}

/*************************************************************************************/

/*************************************************************************************/





