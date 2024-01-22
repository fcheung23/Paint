#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "commands.h"
#include "canvas.h"
#include "input.h"

/**
 * Creates a new canvas struct with specified dimensions and initializes members
 * @param num_rows : int representing number of rows for canvas
 * @param num_cols : int represenitng number of columns for canvas
 * @return the newly created canvas struct 
 */
canvas create_canvas(int num_rows, int num_cols) {
    canvas canvasStruct;
    canvasStruct.num_rows = num_rows;
    canvasStruct.num_cols = num_cols;
    canvasStruct.pixels = (char**)malloc(num_rows * sizeof(char*));
    for (int i = 0; i < num_rows; i++) {
        canvasStruct.pixels[i] = (char*)malloc(num_cols * sizeof(char));
    }
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {
            canvasStruct.pixels[r][c] = '*';
        }
    }
    return canvasStruct;
}   

/**
 * Creates a new point struct with specified x and y coordinates for x and y members
 * @param x : int representing x value for point
 * @param y : int represenitng y value for point
 * @return the newly created point struct
 */
point create_point(int x, int y) {
    point pointStruct;
    pointStruct.x = x;
    pointStruct.y = y;
    return pointStruct;
}   

/** 
 * Displays a "canvas" by printing all elements in the the struct's member pixels, a 2d array, along with x and y axis labels
 * @param currentCanvas : canvas struct representing canvas to print
 * @return nothing
 * @modifies nothing
 */
void print_canvas(canvas currentCanvas) {
    int y_axis_label = currentCanvas.num_rows - 1;
    for (int r = 0; r < currentCanvas.num_rows; r++) {
        printf("%d ", y_axis_label);
        y_axis_label--;
        for (int c = 0; c < currentCanvas.num_cols; c++) {
            printf("%c ", currentCanvas.pixels[r][c]);
        }
        printf("\n");
    }
    printf("  ");
    for (int c = 0; c < currentCanvas.num_cols; c++) {
        printf("%d ", c);
    }
}

