#ifndef _VIEWER_H_
#define _VIEWER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct tester
// {
//     float *arr;
// }tester;

// void set_value(tester *temp);

// void remove_struct(tester *temp);



typedef struct f_point{
    int **points;
    int *row;
    int size;
} f_point;

typedef struct v_point{
    double *X;
    double *Y;
    double *Z;
    int size;
} v_point;

int dot_parser(const char *filename, v_point *coordinates, f_point *conjunction);
#endif // _VIEWER_H_
