#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <map>
#include <string>
#include <vector>

using namespace std;

typedef enum DataType {
    UNKNOWN = 0,
    SHAPE = 1,
    COORDINATE,
    INDEXED_LINE_SET,
    INDEXED_FACE_SET,
    TRANSFORM,
    MATERIAL,
    POINT_SET,
    GROUP,
    APPEARANCE,
    ROTATION,
    TRANSLATION,
    SCALE,
    POINT
} DataType;

typedef struct Container {
    DataType type;
    void *data;
} Container;

typedef struct Info {
    int id;
    DataType type;
} Id;

typedef struct Point {
    struct Info *info;
    double x;
    double y;
    double z;
} Point;

typedef struct CoordIndex {
    struct Info *info;
    vector<int> *coord_index_vec;
} CoordIndex;


typedef struct Coordinate {
    struct Info *info;
    vector<Point *> *coordinate_vec;
} Coord;

typedef struct IndexedLineSet {
    struct Info *info;
    Coordinate *coordinate;
    vector<CoordIndex *> *indexed_line_set_vec;
} IndexedLineSet;

typedef struct IndexedFaceSet {
    struct Info *info;
    Coordinate *coordinate;
    vector<CoordIndex *> *indexed_face_set_vec;
} IndexedFaceSet;


typedef struct Material {
    struct Info *info;
    double diffuse_color[3];
}Material;


typedef struct PointSet {
    struct Info *info;
    Coordinate *coordinate;
} Pointset;


typedef struct Appearance {
    struct Info *info;
    Material *material;
} Appearance;


typedef struct Shape {
    struct Info *info;
    Appearance *appearance;
    Pointset *point_set;
    IndexedLineSet *indexed_line_set;
    IndexedFaceSet *indexed_face_set;
} Shape;

typedef struct Transform {
    struct Info *info;
    double translation[3];
    double rotation[4];
    double scale[3];
    void *children;
} Transform;

typedef struct Group {
    struct Info *info;
    double b_boc_center[3];
    double b_box_size[3];
    void *children;
} Group;



typedef void *(*READ_NODE_FUN)(void *args);
typedef void *(*CREATE_FUN)(void *args);
typedef void *(*READ_FIELD_FUN)(void *args);

typedef struct DataSup {
    string keyword;
    DataType type;
    READ_NODE_FUN read_node_fun;
    READ_FIELD_FUN read_field_fun;
    CREATE_FUN create_fun;
} DataSup;


/* FORWARD DECLARATION */

void init_node_type_map(map<string, DataType> **data_map);
void init_field_type_map(map<string, DataType> **data_map);
void init_type_sup_map(map<DataType, DataSup *> **data_sup_map);
void init_frame(vector<Container *> **frame);
void *read_coordinate(void *data);
void *read_point_set(void *data);
void *read_shape(void *data);
void *read_transform(void *data);
DataType get_container_type(Container *container);
void *get_container_data(Container *container);
void init_def(map<string, Container *> **def);
void check_def_tokn(string tokn);
void check_use_tokn(string tokn);
void add_to_def(string tokn, Container *container);
void* get_from_def(string tokn);
void check_def_use_tokn(string tokn);

void *read_point(void *args);
void *read_translation(void *args);
void *read_rotation(void *args);
void *read_scale(void *args);
int get_node_id(void *node);
DataType get_node_type(void *node);
void init_def_map2(map<string, void *> **def_map2);
void add_to_def_map(string tokn, void *data);







#endif // DATA_TYPES_H
