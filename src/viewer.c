#include "viewer.h"

// void set_value(tester *temp){
//     temp->arr = malloc(3 * sizeof(float));
//     temp->arr[0] = 1.f;
//     temp->arr[1] = 2.f;
//     temp->arr[2] = 3.f;
// }


// void remove_struct(tester *temp){
//     free(temp->arr);
// }
//  "/Users/daniellm/goinfre/Projects/3d_second/simple_cube.obj"
int dot_parser(const char *filename, v_point *coordinates, f_point *conjunction){
    v_point first = {0}; 
    f_point second = {0};
    *coordinates = first;
    *conjunction = second;
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
        // printf("this is working");
        if(f_flag){
            int cnt = 0;
            for (int i  = 2; i < (int)strlen(line); i ++){
                if(line[i] != ' ' && (int)line[i] != '\n' && (i+ 1) != (int)strlen(line)) cnt ++;
            }
            conjunction->points = realloc(conjunction->points, (conjunction->size + 1) * sizeof(int*));
            conjunction->points[conjunction->size] = calloc(cnt, sizeof(int));
            conjunction->row = (int*)realloc(conjunction->row, (conjunction->size + 1) * sizeof(int));
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