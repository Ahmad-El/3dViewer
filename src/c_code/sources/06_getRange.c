#include "model_loading.h"

/// @brief getting geometric object range
/// @param pobject geometric object pointer
void getRange(geometry_info* pobject) {
  vertex_t* vertices = pobject->vertices;
  double x_max = vertices[1].x;
  double x_min = vertices[1].x;
  double y_max = vertices[1].y;
  double y_min = vertices[1].y;
  double z_max = vertices[1].z;
  double z_min = vertices[1].z;

  int last_vertex_ID = pobject->vertices_count;
  for (int i = 0; i < last_vertex_ID; i++) {
    if (vertices[i].x > x_max) x_max = vertices[i].x;
    if (vertices[i].x < x_min) x_min = vertices[i].x;
    if (vertices[i].y > y_max) y_max = vertices[i].y;
    if (vertices[i].y < y_min) y_min = vertices[i].y;
    if (vertices[i].z > z_max) z_max = vertices[i].z;
    if (vertices[i].z < z_min) z_min = vertices[i].z;
  }

  pobject->x_max = x_max;
  pobject->x_min = x_min;
  pobject->y_max = y_max;
  pobject->y_min = x_min;
  pobject->z_max = z_max;
  pobject->z_min = z_min;
}
