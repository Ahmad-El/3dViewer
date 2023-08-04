#include "viewer.h"



int main(){
    v_point first; 
    f_point second;
    int result = dot_parser("simple_cube.obj", &first, &second);
    printf("%d\n", first.size);
    printf("%d\n", second.size);
    printf("%d\n", result);
    
    return 0;
}