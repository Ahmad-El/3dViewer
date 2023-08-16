#include "model_loading.h"

int getFacetVerticesCount(char* line);
int getFacetVertex(char** line, geometry_info* pobject, int ID, int i);

/// @brief getting geometric object facet info from .obj file line
/// @param line .obj file line
/// @param pobject geometric object pointer
/// @param ID facet global ID
/// @return error code
int getFacet(char* line, geometry_info* pobject, int ID) {
  line++;
  line += strspn(line, " ");
  int vertices_count = getFacetVerticesCount(line);
  if (vertices_count < 2) return INCORRECT_FILE;

  pobject->facets[ID].facet_vertices_count = vertices_count;
  pobject->facets[ID].vertex_IDs = (int*)calloc(vertices_count, sizeof(int));
  if (pobject->facets[ID].vertex_IDs == NULL) return RAM_ERROR;

  int error = OK;
  for (int i = 0; i < vertices_count && !error; i++) {
    error = getFacetVertex(&line, pobject, ID, i);
  }

  return error;
}

int getFacetVerticesCount(char* line) {
  int vertices_count = 0;
  while (line && strchr("-0123456789", *line)) {
    vertices_count++;
    line = strpbrk(line, " ");
    if (line) line += strspn(line, " ");
  }
  return vertices_count;
}

int getFacetVertex(char** line, geometry_info* pobject, int ID, int i) {
  int vertex_ID = atoi(*line);
  if (vertex_ID == 0) return INCORRECT_FILE;

  if (vertex_ID < 0) vertex_ID += pobject->vertices_count + 1;
  pobject->facets[ID].vertex_IDs[i] = vertex_ID - 1;
//  pobject->facets[ID].vertex_IDs[i] = fabs(vertex_ID) - 1;

  *line += strspn(*line, " -");
  *line += strspn(*line, "0123456789");
  *line = strpbrk(*line, " ");

  return OK;
}
