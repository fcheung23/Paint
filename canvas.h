#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#ifndef CANVAS_H
#define CANVAS_H

typedef struct canvas_struct{
    int num_rows;
    int num_cols;
    char** pixels;
    char* name;
} canvas;
canvas create_canvas(int num_rows, int num_cols);
void print_canvas(canvas currentCanvas);
typedef struct point_struct{
    int x;
    int y;
} point;
point create_point(int x, int y);   

#endif