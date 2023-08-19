#include "model_loading.h"

/// @brief heap memory freeing
/// @param pobject geometric object pointer
void structClean(geometry_info* pobject) {
  if (pobject->vertices != NULL) free(pobject->vertices);
  pobject->vertices = NULL;

  if (pobject->facets != NULL) {
    for (int i = 0; i < pobject->facets_count; i++) {
      if (pobject->facets[i].vertex_IDs != NULL) {
        free(pobject->facets[i].vertex_IDs);
      }
    }  // for
    free(pobject->facets);
    pobject->facets = NULL;
  }

  pobject->vertices_count = 0;
  pobject->facets_count = 0;
}
