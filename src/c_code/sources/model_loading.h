#ifndef _3D_VIEWER_SRC_MODEL_LOADING_H_
#define _3D_VIEWER_SRC_MODEL_LOADING_H_

#include "../3D_viewer.h"

int getGeometryInfo(const char* filename, geometry_info* pobject);
void getComponentsCount(FILE* fp, geometry_info* pobject);
int getComponents(FILE* fp, geometry_info* pobject);
int getVertex(char* line, geometry_info* pobject, int ID);
int getFacet(char* line, geometry_info* pobject, int ID, int vertex_id_start,
             int vertex_id_end);
void getRange(geometry_info* pobject);

void structClean(geometry_info* pobject);
void rotation_by_ox(geometry_info *vertex, double angle);
void rotation_by_oy(geometry_info *vertex, double angle);
void rotation_by_oz(geometry_info *vertex, double angle);
void move_x(geometry_info *vertex, double a);
void move_y(geometry_info *vertex, double a);
void move_z(geometry_info *vertex, double a);
void scale_model(geometry_info *vertex, double a);

#endif  // _3D_VIEWER_SRC_MODEL_LOADING_H_
