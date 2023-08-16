#include "model_loading.h"

/// @brief Counting vertices and facets number
/// @param fp .obj file pointer
/// @param pobject geometric object pointer
void getComponentsCount(FILE* fp, geometry_info* pobject) {
  char* line = NULL;
  size_t line_len = 0;

  while (getline(&line, &line_len, fp) != -1) {
    if (line[0] == 'v' && line[1] == ' ') pobject->vertices_count++;
    if (line[0] == 'f' && line[1] == ' ') pobject->facets_count++;
  }
  if (line) free(line);

  fseek(fp, 0, SEEK_SET);
}
