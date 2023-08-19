#include "model_loading.h"
#include <math.h>
/*void rotation_by_ox(matrix_t *A, double angle) {
    for (int i = 0; i < A->rows; i++) {
        double temp_y = A->matrix[i][1];
        double temp_z = A->matrix[i][2];
        A->matrix[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
        A->matrix[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
    }
}

void rotation_by_oy(matrix_t *A, double angle) {
    for (int i = 0; i < A->rows; i++) {
        double temp_x = A->matrix[i][0];
        double temp_z = A->matrix[i][2];
        A->matrix[i][0] = cos(angle) * temp_x + sin(angle) * temp_z;
        A->matrix[i][2] = -sin(angle) * temp_x + cos(angle) * temp_z;
}
   
void rotation_by_oz(matrix_t *A, double angle) {
        for (int i = 0; i < A->rows; i++) {
            double temp_x = A->matrix[i][0];
            double temp_y = A->matrix[i][1];
            A->matrix[i][0] = cos(angle) * temp_x - sin(angle) * temp_y;
            A->matrix[i][1] = -sin(angle) * temp_x + cos(angle) * temp_y;
        }
    
    void move_x(matrix_t *A, double a) {
        for (int i = 0; i < A->rows; i++)
            A->matrix[i][0] += a;
    }

    void move_y(matrix_t *A, double a) {
        for (int i = 0; i < A->rows; i++)
            A->matrix[i][1] += a;
    }
    
    void move_z(matrix_t *A, double a) {
        for (int i = 0; i < A->rows; i++)
            A->matrix[i][2] += a;
    }
    

    void scale_model(matrix_t *A, double alp) {
      if (alp)
        for (int i = 0; i < A->rows; i++) {
          A->matrix[i][0] *= alp;
          A->matrix[i][1] *= alp;
          A->matrix[i][2] *= alp;
        }
    }*/
    
void rotation_by_ox(geometry_info *vertex, double angle) {
    for (int i = 0; i < vertex->vertices_count; i++) {
      double temp_y = vertex->vertices[i].y;
      double temp_z = vertex->vertices[i].z;
    vertex->vertices[i].y = cos(angle) * temp_y - sin(angle) * temp_z;
    vertex->vertices[i].z = sin(angle) * temp_y + cos(angle) * temp_z;
    }
}
    
    
void rotation_by_oy(geometry_info *vertex, double angle) {
    for (int i = 0; i < vertex->vertices_count; i++) {
        double temp_x = vertex->vertices[i].x;
        double temp_z = vertex->vertices[i].z;
    vertex->vertices[i].x = cos(angle) * temp_x + sin(angle) * temp_z;
    vertex->vertices[i].z = -sin(angle) * temp_x + cos(angle) * temp_z;
    }
}
    
void rotation_by_oz(geometry_info *vertex, double angle) {
    for (int i = 0; i < vertex->vertices_count; i++) {
        double temp_x = vertex->vertices[i].x;
        double temp_y = vertex->vertices[i].y;
    vertex->vertices[i].x = cos(angle) * temp_x - sin(angle) * temp_y;
    vertex->vertices[i].y = sin(angle) * temp_x + cos(angle) * temp_y;
    }
}
    
void move_x(geometry_info *vertex, double a) {
  for (int i = 0; i < vertex->vertices_count; i++) {
      vertex->vertices[i].x += a;
  }
}
    
void move_y(geometry_info *vertex, double a) {
  for (int i = 0; i < vertex->vertices_count; i++) {
      vertex->vertices[i].y += a;
  }
}

void move_z(geometry_info *vertex, double a) {
  for (int i = 0; i < vertex->vertices_count; i++) {
      vertex->vertices[i].z += a;
  }
}

void scale_model(geometry_info *vertex, double a) {
    if (a) {
    for (int i = 0; i < vertex->vertices_count; i++) {
        vertex->vertices[i].x *= a;
        vertex->vertices[i].y *= a;
        vertex->vertices[i].z *= a;
    }
    }
}
