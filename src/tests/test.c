#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// #include "s21_3DViewer.h"
#include "../c_code/3D_viewer.h"
#include "../c_code/sources/model_loading.h"

START_TEST(affine_test_1) {
  double arg;
  arg = 3.1415926535 / 2;
  geometry_info vertex = {0};
  vertex.vertices_count = 12;
  vertex.vertices = calloc(vertex.vertices_count, sizeof(vertex_t));

  for (int i = 0; i < vertex.vertices_count; ++i) {
    vertex.vertices[i].x = 1;
    vertex.vertices[i].y = 1;
    vertex.vertices[i].z = 1;
  }
  rotation_by_ox(&vertex, arg);
  for (int i = 0; i < vertex.vertices_count; ++i) {
    ck_assert_double_eq(vertex.vertices[i].x, 1);
    ck_assert_double_eq(vertex.vertices[i].y, cos(arg) - sin(arg));
    ck_assert_double_eq(vertex.vertices[i].z, sin(arg) + cos(arg));
  }
  free(vertex.vertices);
}

START_TEST(affine_test_2) {
  double arg;
  arg = 3.1415926535 / 2;
  geometry_info vertex = {0};
  vertex.vertices_count = 12;
  vertex.vertices = calloc(vertex.vertices_count, sizeof(vertex_t));

  for (int i = 0; i < vertex.vertices_count; ++i) {
    vertex.vertices[i].x = 1;
    vertex.vertices[i].y = 1;
    vertex.vertices[i].z = 1;
  }
  rotation_by_oy(&vertex, arg);
  for (int i = 0; i < vertex.vertices_count; ++i) {
    ck_assert_double_eq(vertex.vertices[i].x, cos(arg) + sin(arg));
    ck_assert_double_eq(vertex.vertices[i].y, 1);
    ck_assert_double_eq(vertex.vertices[i].z, -sin(arg) + cos(arg));
  }
  free(vertex.vertices);
}

START_TEST(affine_test_3) {
  double arg;
  arg = 3.1415926535 / 2;
  geometry_info vertex = {0};
  vertex.vertices_count = 12;
  vertex.vertices = calloc(vertex.vertices_count, sizeof(vertex_t));

  for (int i = 0; i < vertex.vertices_count; ++i) {
    vertex.vertices[i].x = 1;
    vertex.vertices[i].y = 1;
    vertex.vertices[i].z = 1;
  }
  rotation_by_oz(&vertex, arg);
  for (int i = 0; i < vertex.vertices_count; ++i) {
    ck_assert_double_eq(vertex.vertices[i].x, cos(arg) - sin(arg));
    ck_assert_double_eq(vertex.vertices[i].y, sin(arg) + cos(arg));
    ck_assert_double_eq(vertex.vertices[i].z, 1);
  }
  free(vertex.vertices);
}

START_TEST(affine_test_4) {
  double arg = 1.0;
  geometry_info vertex = {0};
  vertex.vertices_count = 12;
  vertex.vertices = calloc(vertex.vertices_count, sizeof(vertex_t));

  for (int i = 0; i < vertex.vertices_count; ++i) {
    vertex.vertices[i].x = 1.0;
    vertex.vertices[i].y = 2.0;
    vertex.vertices[i].z = 3.0;
  }
  move_x(&vertex, arg);
  for (int i = 0; i < vertex.vertices_count; ++i) {
    ck_assert_double_eq(vertex.vertices[i].x, 2);
  }
  free(vertex.vertices);
}

START_TEST(affine_test_5) {
  double arg = 2.0;
  geometry_info vertex = {0};
  vertex.vertices_count = 12;
  vertex.vertices = calloc(vertex.vertices_count, sizeof(vertex_t));

  for (int i = 0; i < vertex.vertices_count; ++i) {
    vertex.vertices[i].x = 1.0;
    vertex.vertices[i].y = 2.0;
    vertex.vertices[i].z = 3.0;
  }
  move_y(&vertex, arg);
  for (int i = 0; i < vertex.vertices_count; ++i) {
    ck_assert_double_eq(vertex.vertices[i].y, 4);
  }
  free(vertex.vertices);
}

START_TEST(affine_test_6) {
  double arg = 3.0;
  geometry_info vertex = {0};
  vertex.vertices_count = 12;
  vertex.vertices = calloc(vertex.vertices_count, sizeof(vertex_t));

  for (int i = 0; i < vertex.vertices_count; ++i) {
    vertex.vertices[i].x = 1.0;
    vertex.vertices[i].y = 2.0;
    vertex.vertices[i].z = 3.0;
  }
  move_z(&vertex, arg);
  for (int i = 0; i < vertex.vertices_count; ++i) {
    ck_assert_double_eq(vertex.vertices[i].z, 6);
  }
  free(vertex.vertices);
}

START_TEST(affine_test_7) {
  double arg = 2.0;
  geometry_info vertex = {0};
  vertex.vertices_count = 12;
  vertex.vertices = calloc(vertex.vertices_count, sizeof(vertex_t));

  for (int i = 0; i < vertex.vertices_count; ++i) {
    vertex.vertices[i].x = 1.0;
    vertex.vertices[i].y = 2.0;
    vertex.vertices[i].z = 3.0;
  }
  scale_model(&vertex, arg);
  for (int i = 0; i < vertex.vertices_count; ++i) {
    ck_assert_double_eq(vertex.vertices[i].x, 2.0);
    ck_assert_double_eq(vertex.vertices[i].y, 4.0);
    ck_assert_double_eq(vertex.vertices[i].z, 6.0);
  }
  free(vertex.vertices);
}

START_TEST(parser_1) {
  geometry_info object = {0};
  const char *filename = "c_code/obj.txt";
  getGeometryInfo(filename, &object);
  ck_assert_int_eq(8, object.vertices_count);
  structClean(&object);
}

START_TEST(parser_2) {
  geometry_info object = {0};
  const char *filename = "c_code/sources/simple_cube_no_file.obj";
  int error = getGeometryInfo(filename, &object);
  ck_assert_int_eq(1, error);
  structClean(&object);
}

// getGeometryInfo(argv[1], &object);
Suite *s21_3Dviever_suite() {
  Suite *suite;

  suite = suite_create("s21_3Dviever");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, affine_test_1);
  tcase_add_test(tcase_core, affine_test_2);
  tcase_add_test(tcase_core, affine_test_3);
  tcase_add_test(tcase_core, affine_test_4);
  tcase_add_test(tcase_core, affine_test_5);
  tcase_add_test(tcase_core, affine_test_6);
  tcase_add_test(tcase_core, affine_test_7);
  tcase_add_test(tcase_core, parser_1);
  tcase_add_test(tcase_core, parser_2);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main() {
  Suite *suite = s21_3Dviever_suite();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_VERBOSE);

  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
