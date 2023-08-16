#include "model_loading.h"

/// @brief heap memory freeing
/// @param pobject geometric object pointer
void structClean(geometry_info* pobject) {
  if (pobject->vertices != NULL) free(pobject->vertices);

  if (pobject->facets != NULL) {
    for (int i = 0; i < pobject->facets_count + 1; i++) {
      if (pobject->facets[i].vertex_IDs != NULL) {
        free(pobject->facets[i].vertex_IDs);
      }
    }  // for
    free(pobject->facets);
  }
}
