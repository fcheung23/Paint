#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#ifndef INPUT_H
#define INPUT_H

canvas create_initial_canvas(int argc, char* argv[]);
bool isValidFormat(const int num_args_needed, const int num_args_read,
	bool should_be_last_value_on_line);
void getValidCommand(const bool isLastElementOnLine, canvas* currentCanvas, canvas* savedCanvases, int* num_saved_canvases);
char* getValidStr(const bool isLastElementOnLine);
int getValidInt(const bool isLastElementOnLine);
int getPosInt(const bool isLastElementOnLine);  

bool is_points_in_canvas(point firstPoint, point secondPoint, canvas currentCanvas);
bool is_horizontal_line(point firstPoint, point secondPoint, canvas* currentCanvas);
bool is_vertical_line(point firstPoint, point secondPoint, canvas* currentCanvas);
bool is_left_diagonal_line(point firstPoint, point secondPoint, canvas* currentCanvas);
bool is_right_diagonal_line(point firstPoint, point secondPoint, canvas* currentCanvas);
char type_of_line(point firstPoint, point secondPoint, canvas* currentCanvas);

#endif
