
#ifndef _VIEWER_H_
#define _VIEWER_H_

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>






















// typedef struct f_point{
//     int **points;
//     int *row;
//     int size;
// } f_point;

// typedef struct v_point{
//     double *X;
//     double *Y;
//     double *Z;
//     int size;
// } v_point;

void addItem(double **p, double value, int *size);
void clean_arr(double **p);
int dot_parser(char *filename, double **X, double **Y, double **Z);
// void test_add_item();
// void get_f_points(f_point *conjuction);



#endif // _VIEWER_H_
#include "viewer.h"

int dot_parser(char *filename, v_point *coordinates, f_point *conjunction){
    FILE *p_file = fopen(filename, "r");
    char line[1024];
    int row = 0;
    while (fgets(line, sizeof(line), p_file) != NULL)
    {
        int v_flag = 0, f_flag = 0, u = -1;
        double x, y, z;
        if(line[0] == 'v' && line[1] == ' ') v_flag = 1;
        if(line[0] == 'f' && line[1] == ' ') f_flag = 1;
        if(v_flag) u = sscanf(line+2, "%lf %lf %lf", &x, &y, &z);
        if(v_flag && u == 3) {
            coordinates->X = realloc(coordinates->X, (coordinates->size + 1) * sizeof(double));
            coordinates->X[coordinates->size] = x;
            coordinates->Y = realloc(coordinates->Y, (coordinates->size + 1) * sizeof(double));
            coordinates->Y[coordinates->size] = y;
            coordinates->Z = realloc(coordinates->Z, (coordinates->size + 1) * sizeof(double));
            coordinates->Z[coordinates->size] = z;
            coordinates->size += 1;
        }
        if(f_flag){
            int cnt = 0;
            for (int i  = 2; i < (int)strlen(line); i ++){
                if(line[i] != ' ' && (int)line[i] != '\n' && (i+ 1) != (int)strlen(line)) cnt ++;
            }
            conjunction->points = realloc(conjunction->points, (conjunction->size + 1) * sizeof(int*));
            conjunction->points[conjunction->size] = calloc(cnt, sizeof(int));
            conjunction->row = realloc(conjunction->row, (conjunction->size + 1) * sizeof(int));
            conjunction->row[conjunction->size] = cnt;
            conjunction->size += 1;
            cnt = 0;
            char temp_f[20]; int temp_f_number, col = 0;
            for (int i  = 2; i < (int)strlen(line); i ++){
                if(line[i] != ' ' && line[i] != '\n' && (i+ 1) != (int)strlen(line)){
                    temp_f[cnt++] = line[i];
                } else {
                    temp_f[cnt] = '\0';
                    sscanf(temp_f, "%d", &temp_f_number);
                    temp_f[0] = '\0';
                    cnt = 0;
                    conjunction->points[row][col++] = temp_f_number - 1;
                }
            }
            row++;
        }
    }
    fclose(p_file);
    return 0;
}

int main(){


    v_point coordinates = {0};
    f_point conjunction = {0};

    dot_parser("cube_first.obj", &coordinates, &conjunction);
    for (int i = 0; i < coordinates.size; i ++){
        printf("%lf ", coordinates.X[i]);
        printf("%lf ", coordinates.Y[i]);
        printf("%lf\n", coordinates.Z[i]);
    }
    for (int i = 0; i < conjunction.size; i++){
        for (int j = 0; j < conjunction.row[i]; j++){
            printf("%d ", conjunction.points[i][j]);
        }
        printf("\n");
    }


    for(int i = 0; i < conjunction.size; i ++){
        free(conjunction.points[i]);
    }
    free(conjunction.points);
    free(coordinates.X);
    free(coordinates.Y);
    free(coordinates.Z);
    return 0;
}







// void addItem(double **p, double value, int *size){
//     int old_size = *size;
//     *p = (double*)realloc(*p, (old_size + 1) * sizeof(double));
//     (*p)[old_size] = value;
//     (*size) ++;
// }
// void clean_arr(double **p){free(*p);}
// void test_add_item(){
    
//     v_point coordinates = {0};
//     coordinates.X = realloc(coordinates.X, (coordinates.size + 1) * sizeof(double));
//     coordinates.X[coordinates.size] = 1;
//     coordinates.size += 1;
//     coordinates.X = realloc(coordinates.X, (coordinates.size + 1) * sizeof(double));
//     coordinates.X[coordinates.size] = 2;
//     coordinates.size += 1;
//     coordinates.X = realloc(coordinates.X, (coordinates.size + 1) * sizeof(double));
//     coordinates.X[coordinates.size] = 3;
//     coordinates.size += 1;
// }






// int dot_parser(char *filename, double **X, double **Y, double **Z){
//     FILE *p_file = fopen(filename, "r");
//     char line[1024];
//     int size_x = 0, size_y = 0, size_z = 0;
//     while (fgets(line, sizeof(line), p_file) != NULL)
//     {
//         int v_flag = 0, f_flag = 0, u = -1;
//         double x, y, z;

//         if(line[0] == 'v' && line[1] == ' ') v_flag = 1;
//         if(line[0] == 'f' && line[1] == ' ') f_flag = 1;
//         if(v_flag) u = sscanf(line+2, "%lf %lf %lf", &x, &y, &z);
//         if(v_flag && u == 3) {
//             addItem(X, x, &size_x);
//             addItem(Y, y, &size_y);
//             addItem(Z, z, &size_z);
//             // printf("x = %lf, y = %lf, z = %lf and u = %d\n", x, y, z, u);
//         }
//         f_point dots = {0};
//         if(f_flag){
//         char temp_f[20]; int cnt = 0, temp_f_number;
//         for (int i  = 2; i < (int)strlen(line); i ++){
//             if(line[i] != ' ' && line[i] != '\n' && (i+ 1) != strlen(line)) temp_f[cnt++] = line[i];
//             else{
//                 temp_f[cnt] = '\0';
//                 sscanf(temp_f, "%d", &temp_f_number);
//                 temp_f[0] = '\0'; cnt = 0;
//                 printf("%d ", temp_f_number);
//             }
//         }
//         printf("\n");
//         }
//     }
    
//     return size_x;
// }

