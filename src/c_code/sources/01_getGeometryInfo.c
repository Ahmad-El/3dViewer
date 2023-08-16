#include "model_loading.h"

/// @brief getting geometric object parameters from .obj file
/// @param filename .obj file name
/// @param pobject geometric object pointer
/// @return error code
int getGeometryInfo(const char* filename, geometry_info* pobject) {
  int error = OK;
  FILE* fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    error = NO_SUCH_FILE_OR_DIRECTORY;
  } else {
    getComponentsCount(fp, pobject);
    if (pobject->vertices_count < 3 || pobject->facets_count < 1)
      return INCORRECT_FILE;

    error = getComponents(fp, pobject);
    getRange(pobject);
    fclose(fp);
  }
  return error;
}
