#include "model_loading.h"

int getFacetVerticesCount(char* line);
int getFacetVertex(char** line, geometry_info* pobject, int ID, int i,
                   int vertex_id_start, int vertex_id_end);

/// @brief getting geometric object facet info from .obj file line
/// @param line .obj file line
/// @param pobject geometric object pointer
/// @param ID facet global ID
/// @param vertex_id_offset duck tape if .obj file has any groups
/// @return error code
int getFacet(char* line, geometry_info* pobject, int ID, int vertex_id_start,
             int vertex_id_end) {
  line++;
  line += strspn(line, " ");
  int facet_vertices_count = getFacetVerticesCount(line);
  if (facet_vertices_count < 1) return INCORRECT_FILE;

  pobject->facets[ID].facet_vertices_count = facet_vertices_count;
  pobject->facets[ID].vertex_IDs =
      (int*)calloc(facet_vertices_count, sizeof(int));
  if (pobject->facets[ID].vertex_IDs == NULL) return RAM_ERROR;

  int error = OK;
  for (int i = 0; i < facet_vertices_count && !error; i++) {
    error =
        getFacetVertex(&line, pobject, ID, i, vertex_id_start, vertex_id_end);
  }

  return error;
}

int getFacetVerticesCount(char* line) {
  int facet_vertices_count = 0;
  while (line && strchr("-0123456789", *line)) {
    facet_vertices_count++;
    line = strpbrk(line, " ");
    if (line) line += strspn(line, " ");
  }
  return facet_vertices_count;
}

int getFacetVertex(char** line, geometry_info* pobject, int ID, int i,
                   int vertex_id_start, int vertex_id_end) {
  int vertex_ID = atoi(*line);
  if (vertex_ID == 0) return INCORRECT_FILE;

  if (vertex_ID < 0) {
    vertex_ID += vertex_id_end + 2;  // ducktape if there are a few groups
  } else {
    vertex_ID += vertex_id_start;  // ducktape if there are a few groups
  }

  if (vertex_ID - 1 > vertex_id_end) return INCORRECT_FILE;

  pobject->facets[ID].vertex_IDs[i] = vertex_ID - 1;

  *line += strspn(*line, " -");
  *line += strspn(*line, "0123456789");
  *line = strpbrk(*line, " ");

  return OK;
}
