#include "model_loading.h"

/// @brief getting geometric object vertex info from .obj file line
/// @param line .obj file line
/// @param pobject geometric object pointer
/// @param ID vertex global ID
/// @return error code
int getVertex(char* line, geometry_info* pobject, int ID) {
  double x, y, z;
  if (sscanf(line, "v %lf %lf %lf", &x, &y, &z) != 3) return INCORRECT_FILE;

  pobject->vertices[ID].x = x;
  pobject->vertices[ID].y = y;
  pobject->vertices[ID].z = z;

  return OK;
}
