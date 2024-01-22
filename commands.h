#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "canvas.h"
#ifndef COMMANDS_H
#define COMMANDS_H

void quit(canvas* currentCanvas, canvas* savedCanvases, int num_saved_canvases, int canvasLoaded);
void write(canvas* currentCanvas);
void draw_horizontal_line(point firstPoint, point secondPoint, canvas* currentCanvas);
void draw_vertical_line(point firstPoint, point secondPoint, canvas* currentCanvas);
void draw_left_diagonal_line(point firstPoint, point secondPoint, canvas* currentCanvas);
void erase(canvas* currentCanvas);
void resize(canvas* currentCanvas);
void add_row(canvas* currentCanvas, int rowPos);
void add_col(canvas* currentCanvas, int colPos);
void add(canvas* currentCanvas);
void delete_row(canvas* currentCanvas, int rowPos);
void delete_col(canvas* currentCanvas, int colPos);
void delete(canvas* currentCanvas); 
void print_help();
void save_canvas(canvas** savedCanvases, canvas* currentCanvas, int* num_saved_canvases);
void load_canvas(canvas* savedCanvases, canvas* currentCanvas, int num_saved_canvases, int* canvasLoaded);

#endif