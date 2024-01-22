#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "commands.h"
#include "canvas.h"
#include "input.h"

/**
 * Creates the first canvas struct with the specified dimensions from the command line (if valid), otherwise default to 10 by 10
 * @param argc : int representing number of arguments entered on command line
 * @param argv : array of strings representing arguments entered on command line
 * @return the newly created canvas struct 
 */
canvas create_initial_canvas(int argc, char* argv[]) {
    int num_rows, num_cols;
    if (argc == 3 && (atoi(argv[1]) > 0) && (atoi(argv[2]) > 0)) {
        num_rows = atoi(argv[1]);
        num_cols = atoi(argv[2]);
    }
    else {
        if (argc != 3 && argc != 1) {
        printf("Wrong number of command line arguments entered.\n");
        printf("Usage: ./paint.out [num_rows num_cols]\n");
        printf("Making default board of 10 X 10.\n");
        }
        else if (argc == 3 && atoi(argv[1]) < 1) {
            printf("The number of rows is less than 1.\n");
            printf("Making default board of 10 X 10.\n");
        }
        else if (argc == 3 && atoi(argv[2]) < 1) {
            printf("The number of columns is less than 1.\n");
            printf("Making default board of 10 X 10.\n");
        }
        num_rows = 10;
        num_cols = 10;
    } 
    return create_canvas(num_rows, num_cols);
}

/**
 * Checks if argument has number of arguments needed and if it's the last thing entered (if needed) ignoring whitespace at the end 
 * @param numArgsNeeded: the number of format placeholders that needed to have been read in the last scanf
 * @param numArgsRead: the actual number of placeholders that were read from scanf, ie its return value
 * @param isLastElementOnLine: true if this is the last value that should be on this line of input
 * @return: true if the input is correctly formatted and false otherwise
 */
bool isValidFormat(const int num_args_needed, const int num_args_read,
    bool should_be_last_value_on_line) {
    bool format_is_correct = num_args_read == num_args_needed;
    char last_value;
    if (should_be_last_value_on_line) {
        while (isspace(last_value = getchar()) && last_value != '\n');
        format_is_correct = format_is_correct && (last_value == '\n' || last_value == EOF);
    }
    return format_is_correct;
}

/**
 * Takes a command, or a valid character from the user, to call the appropriate function, otherwise print what's wrong 
 * @param isLastElementOnLine : true if this is the last value that should be on this line of input
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @param savedCanvases : array of canvas structs representing saved canvases
 * @param num_saved_canvases : pointer to int representing the number of canvases saved
 * @return nothing
 * @modifies nothing directly
 */
void getValidCommand(const bool isLastElementOnLine, canvas* currentCanvas, canvas* savedCanvases, int* num_saved_canvases) {
  const int numArgsNeeded = 1;
  int numArgsRead;
  char* string = (char*)malloc(25*sizeof(char));
  int canvasLoaded;
  numArgsRead = scanf(" %s", string);
  if (string[1] == '\0' && isValidFormat(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
    if (string[0] == 'w') write(currentCanvas);
    if (string[0] == 'h') {
        print_help();
        print_canvas(*currentCanvas);
    }
    if (string[0] == 'e') erase(currentCanvas);
    if (string[0] == 'r') resize(currentCanvas);
    if (string[0] == 'a') add(currentCanvas);
    if (string[0] == 'd') delete(currentCanvas);
    if (string[0] == 's') save_canvas(&savedCanvases, currentCanvas, num_saved_canvases);
    if (string[0] == 'l') load_canvas(savedCanvases, currentCanvas, *num_saved_canvases, &canvasLoaded);
    if (string[0] == 'q') quit(currentCanvas, savedCanvases, *num_saved_canvases, canvasLoaded); 
  }
  else {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if (string[0] == 'w') printf("Improper draw command.\n"); 
    else if (string[0] == 'e') printf("Improper erase command.\n");
    else if (string[0] == 'r') printf("Improper resize command.\n");
    else if (string[0] == 'a') printf("Improper add command.\n");
    else if (string[0] == 'd') printf("Improper delete command.\n");
    else if (string[0] == 's') printf("Improper save command or file could not be created.\n");
    else if (string[0] == 'l') printf("Improper load command or file could not be opened.\n");
    else printf("Unrecognized command. Type h for help.\n"); 
    print_canvas(*currentCanvas);
  }
}

/**
 * Get a valid string from the user but return null if not valid
 * @param isLastElementOnLine : true if this is the last value that should be on this line of input
 * @return a valid string or null if not valid
 */
char* getValidStr(const bool isLastElementOnLine) {
  const int numArgsNeeded = 1;
  int numArgsRead;
  char* string = (char*)malloc(25*sizeof(char));

  numArgsRead = scanf(" %s", string);
  if (isValidFormat(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
    return string;
  } else {
    free(string);
    return NULL; // if not a valid string
  }
}

/**
 * Get an integer from the user but return an int representing an error if not valid
 * @param isLastElementOnLine : true if this is the last value that should be on this line of input
 * @return a valid integer or -2 if an int is not entered
 */
int getValidInt(const bool isLastElementOnLine) {
  const int numArgsNeeded = 1;
  int numArgsRead;
  int num;

  numArgsRead = scanf(" %d", &num);
  
  if (isValidFormat(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
    return num;
  } else {
    return -2; // if not an int
  }
}

/**
 * Get an positive integer from the user or returns a int representing an error if not valid
 * @param isLastElementOnLine : true if this is the last value that should be on this line of input
 * @return a valid positive integer or -2 if not an int or none entered or -1 if not positive
 */
int getPosInt(const bool isLastElementOnLine) {
  // first get a valid integer
  int num = getValidInt(isLastElementOnLine);
  // then check it meets the desired conditions
  if (num >= 0) {
    return num;
  }
  else if (num == -2) {
    return -2; // if not an int
 }
  else {
    return -1; // if not positive
  }
}

/**
 * Checks if two points exist within a "canvas"
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : canvas struct representing the current canvas being dealt with/modified 
 * @return true if both points (structs representing points on the canvas) are within its dimensions
 */
bool is_points_in_canvas(point firstPoint, point secondPoint, canvas currentCanvas) {
    if ((firstPoint.y < currentCanvas.num_rows && firstPoint.x < currentCanvas.num_cols) && (secondPoint.y < currentCanvas.num_rows && secondPoint.x < currentCanvas.num_cols)) return true;
    else return false;
}

/**
 * Checks if two points form a horizontal line and exist within the currentCanvas
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : canvas struct representing the current canvas being dealt with/modified 
 * @return true if the points form a horizontal line and are within the currentCanvas dimensions
 */
bool is_horizontal_line(point firstPoint, point secondPoint, canvas* currentCanvas) {
    if ((firstPoint.y == secondPoint.y) && (is_points_in_canvas(firstPoint, secondPoint, *currentCanvas))) return true;
    else return false;
}

/**
 * Checks if two points form a vertical line and exist within the currentCanvas
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : canvas struct representing the current canvas being dealt with/modified 
 * @return true if the points form a vertical line and are within the currentCanvas dimensions
 */
bool is_vertical_line(point firstPoint, point secondPoint, canvas* currentCanvas) {
    if ((firstPoint.x == secondPoint.x) && (is_points_in_canvas(firstPoint, secondPoint, *currentCanvas))) return true;
    else return false;
}

/**
 * Checks if two points form a left diagonal line (slope of 1) and exist within the currentCanvas
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : canvas struct representing the current canvas being dealt with/modified 
 * @return true if the points form a left diagonal line and are within the currentCanvas dimensions
 */
bool is_left_diagonal_line(point firstPoint, point secondPoint, canvas* currentCanvas) {
    if (((double) (secondPoint.y - firstPoint.y) / (double) (secondPoint.x - firstPoint.x) == 1) && (is_points_in_canvas(firstPoint, secondPoint, *currentCanvas))) return true;
    else return false;
}

/**
 * Checks if two points form a right diagonal line (slope of -1) and exist within the currentCanvas
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : canvas struct representing the current canvas being dealt with/modified 
 * @return true if the points form a right diagonal line and are within the currentCanvas dimensions
 */
bool is_right_diagonal_line(point firstPoint, point secondPoint, canvas* currentCanvas) {
    if (((double) (secondPoint.y - firstPoint.y) / (double) (secondPoint.x - firstPoint.x) == -1) && (is_points_in_canvas(firstPoint, secondPoint, *currentCanvas))) return true;
    else return false;
}

/**
 * Checks what kind of line two points form on currentCanvas (if any)
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : canvas struct representing the current canvas being dealt with/modified 
 * @return a char representing the type of line the points form, or '!' if none
 */
char type_of_line(point firstPoint, point secondPoint, canvas* currentCanvas) {
    char result = '!';
    if (is_horizontal_line(firstPoint, secondPoint, currentCanvas)) {
        result = 'H';
    }
    else if (is_vertical_line(firstPoint, secondPoint, currentCanvas)) {
        result = 'V';
    }
    else if (is_left_diagonal_line(firstPoint, secondPoint, currentCanvas)) {
        result = 'L';
    }
    else if (is_right_diagonal_line(firstPoint, secondPoint, currentCanvas)) {
        result = 'R';
    }
    return result;
}

