#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "commands.h"
#include "canvas.h"
#include "input.h"

/**
 * Quits program by freeing all allocated memory and exits
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @param savedCanvases : array of canvas structs representing saved canvases
 * @param num_saved_canvases : int representing the number of canvases saved
 * @param canvasLoaded : int representing index in SavedCanvases of the canvas loaded (to avoid double free)
 * @return nothing
 * @modifies frees memory from currentCanvas and savedCanvases
 */
void quit(canvas* currentCanvas, canvas* savedCanvases, int num_saved_canvases, int canvasLoaded) {
    if (num_saved_canvases == 0) {
        for (int r = 0; r < currentCanvas->num_rows; r++) {
            free(currentCanvas->pixels[r]);
        }
        free(currentCanvas->pixels);
    } else {
        for (int i = 0; i < num_saved_canvases; i++) {
            if (i != canvasLoaded) {
                for (int r = 0; r < savedCanvases[i].num_rows; r++) {
                    free(savedCanvases[i].pixels[r]);
                }
                free(savedCanvases[i].pixels);
                free(savedCanvases[i].name);
            }
        }
        free(savedCanvases);   
        savedCanvases = NULL;
    }
    exit(0);
}

/**
 * Prints "help", a list of all the commands and how to use them
 * @param none : none
 * @return nothing
 * @modifies nothing
 */
void print_help() {
  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

/**
 * Draws a horizontal line specified by two points on a "canvas"
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @return nothing
 * @modifies currentCanvas
 */
void draw_horizontal_line(point firstPoint, point secondPoint, canvas* currentCanvas) {
    for (int c = firstPoint.x; c <= secondPoint.x; c++) {
        if (currentCanvas->pixels[currentCanvas->num_rows - firstPoint.y - 1][c] == '*') currentCanvas->pixels[currentCanvas->num_rows - firstPoint.y - 1][c] = '-';
        else if (currentCanvas->pixels[currentCanvas->num_rows - firstPoint.y - 1][c] != '-') currentCanvas->pixels[currentCanvas->num_rows - firstPoint.y - 1][c] = '+';
        }
    print_canvas(*currentCanvas); 
}

/**
 * Draws a vertical line specified by two points on a "canvas"
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @return nothing
 * @modifies currentCanvas
 */
void draw_vertical_line(point firstPoint, point secondPoint, canvas* currentCanvas) {
    for (int r = firstPoint.y; r <= secondPoint.y; r++) {
        if (currentCanvas->pixels[currentCanvas->num_rows - r - 1][firstPoint.x] == '*') currentCanvas->pixels[currentCanvas->num_rows - r - 1][firstPoint.x] = '|';
        else if (currentCanvas->pixels[currentCanvas->num_rows - r - 1][firstPoint.x] != '|') currentCanvas->pixels[currentCanvas->num_rows - r - 1][firstPoint.x] = '+';
        }
    print_canvas(*currentCanvas); 
}

/**
 * Draws a left diagonal line specified by two points on a "canvas"
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @return nothing
 * @modifies currentCanvas
 */
void draw_left_diagonal_line(point firstPoint, point secondPoint, canvas* currentCanvas) {
    int i = firstPoint.y;
    for (int c = firstPoint.x; c <= secondPoint.x; c++) {
        if (currentCanvas->pixels[currentCanvas->num_rows - i - 1][c] == '*') currentCanvas->pixels[currentCanvas->num_rows - i - 1][c] = '/';
        else if (currentCanvas->pixels[currentCanvas->num_rows - i - 1][c] != '/') currentCanvas->pixels[currentCanvas->num_rows - i - 1][c] = '+';
        i++;
    }
    print_canvas(*currentCanvas); 
}

/**
 * Draws a right diagonal line specified by two points on a "canvas"
 * @param firstPoint : point struct representing the "first point"
 * @param secondPoint : point struct representing the "second point" 
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @return nothing
 * @modifies currentCanvas
 */
void draw_right_diagonal_line(point firstPoint, point secondPoint, canvas* currentCanvas) {
    int i = firstPoint.y;
    for (int c = firstPoint.x; c <= secondPoint.x; c++) {
        if (currentCanvas->pixels[currentCanvas->num_rows - i - 1][c] == '*') currentCanvas->pixels[currentCanvas->num_rows - i - 1][c] = '\\';
        else if (currentCanvas->pixels[currentCanvas->num_rows - i - 1][c] != '\\') currentCanvas->pixels[currentCanvas->num_rows - i - 1][c] = '+';
        i--;
    }
    print_canvas(*currentCanvas); 
}

/**
 * Writes or "draws" a line on a "canvas", checking what kind of line two points taken from the user represent (if any) first, otherwise prints whats wrong
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @return nothing
 * @modifies currentCanvas
 */
void write(canvas* currentCanvas) {
    int c;
    int x1 = getPosInt(false);
    int y1 = getPosInt(false);
    int x2 = getPosInt(false);
    int y2 = getPosInt(true);
    if (y2 < 0) {
        printf("Improper draw command.\n");
        print_canvas(*currentCanvas); 
        while ((c = getchar()) != '\n' && c != EOF);
    } 
    else {
        point firstPoint = create_point(y1, x1);
        point secondPoint = create_point(y2, x2);
        char lineType = type_of_line(firstPoint, secondPoint, currentCanvas);
        if (lineType == 'H') {
            if (firstPoint.x <= secondPoint.x) draw_horizontal_line(firstPoint, secondPoint, currentCanvas);
            else draw_horizontal_line(secondPoint, firstPoint, currentCanvas);
        }
        else if (lineType == 'V') {
            if (firstPoint.y <= secondPoint.y) draw_vertical_line(firstPoint, secondPoint, currentCanvas);
            else draw_vertical_line(secondPoint, firstPoint, currentCanvas);
        }
        else if (lineType == 'L') {
            if (firstPoint.y <= secondPoint.y) draw_left_diagonal_line(firstPoint, secondPoint, currentCanvas);
            else draw_left_diagonal_line(secondPoint, firstPoint, currentCanvas);
        }
        else if (lineType == 'R') {
            if (firstPoint.y >= secondPoint.y) draw_right_diagonal_line(firstPoint, secondPoint, currentCanvas);
            else draw_right_diagonal_line(secondPoint, firstPoint, currentCanvas);
        }
        else if (lineType == '!') {
            printf("Improper draw command.\n");
            print_canvas(*currentCanvas); 
        } 
    }  
}

/**
 * Erases a "pixel" on a "canvas" by taking input from user (if valid) sets a char element on the 2d array back to '*', otherwise prints what's wrong
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @return nothing
 * @modifies currentCanvas
 */
void erase(canvas* currentCanvas) {
    int c;
    int x = getPosInt(false);
    int y = getPosInt(true);
    if (y < 0) {
        printf("Improper erase command.\n");
        print_canvas(*currentCanvas); 
        while ((c = getchar()) != '\n' && c != EOF);
    } 
    else {
        point erasePoint = create_point(y, x);
        if (is_points_in_canvas(erasePoint, erasePoint, *currentCanvas)) {
            currentCanvas->pixels[currentCanvas->num_rows - erasePoint.y - 1][erasePoint.x] = '*';
            print_canvas(*currentCanvas); 
        }
    }
}

/**
 * Adds a row to a "canvas" by allocating memory for another row, shifting rows to make room, and setting the row's elements to '*'
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @param rowPos : int representing which row position (bottom row being zero) to insert a new row
 * @return nothing
 * @modifies currentCanvas
 */
void add_row(canvas* currentCanvas, int rowPos) {
    currentCanvas->pixels = (char**)realloc(currentCanvas->pixels, (currentCanvas->num_rows + 1) * sizeof(char*));
    currentCanvas->pixels[currentCanvas->num_rows] = (char*)malloc((currentCanvas->num_cols) * sizeof(char));
    for (int c = 0; c < currentCanvas->num_cols; c++) {
        currentCanvas->pixels[currentCanvas->num_rows][c] = '*';
    }
    currentCanvas->num_rows++;
    if (rowPos == currentCanvas->num_rows - 1) {
        for (int r = currentCanvas->num_rows - 1; r > 0; r--) {
            for (int c = 0; c < currentCanvas->num_cols; c++) {
                    currentCanvas->pixels[r][c] = currentCanvas->pixels[r - 1][c];
            }
        }
    }
    else {
        for (int r = currentCanvas->num_rows - 1; r >= currentCanvas->num_rows - rowPos - 1; r--) {
            for (int c = 0; c < currentCanvas->num_cols; c++) {
                currentCanvas->pixels[r][c] = currentCanvas->pixels[r - 1][c];
            }
        }
    }
    for (int c = 0; c < currentCanvas->num_cols; c++) {
        currentCanvas->pixels[currentCanvas->num_rows - rowPos - 1][c] = '*'; 
    }
}

/**
 * Adds a column to a "canvas" by allocating memory for another element on every row, shifting columns to make room, and setting the columns's elements to '*'
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @param colPos : int representing which column position (left-most being zero) to insert a new column
 * @return nothing
 * @modifies currentCanvas
 */
void add_col(canvas* currentCanvas, int colPos) {
    for (int r = 0; r < currentCanvas->num_rows; r++) {
        currentCanvas->pixels[r] = realloc(currentCanvas->pixels[r], (currentCanvas->num_cols + 1) * sizeof(char));
        currentCanvas->pixels[r][currentCanvas->num_cols] = '*';
    }
    currentCanvas->num_cols++;
    for (int r = 0; r < currentCanvas->num_rows; r++) {
        for (int c = currentCanvas->num_cols - 1; c >= colPos; c--) {
            currentCanvas->pixels[r][c] = currentCanvas->pixels[r][c - 1];
        }
    }
    for (int r = 0; r < currentCanvas->num_rows; r++) {
        currentCanvas->pixels[r][colPos] = '*';
    }
}

/**
 * Adds a row or column depending on input taken from the user (if valid), otherwise prints what's wrong
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @return nothing
 * @modifies currentCanvas
 */
void add(canvas* currentCanvas) {
    char selection;
    scanf(" %c", &selection);
    if (selection == 'r') {
        int rowPos = getPosInt(false);
        if (rowPos >= 0 && rowPos <= currentCanvas->num_rows) {
            add_row(currentCanvas, rowPos);
            print_canvas(*currentCanvas);
        }
        else {
            printf("Improper add command.\n");
            print_canvas(*currentCanvas);
        }
    }
    else if (selection == 'c') {
        int colPos = getPosInt(false);
        if (colPos >= 0 && colPos <= currentCanvas->num_cols) {
            add_col(currentCanvas, colPos);
            print_canvas(*currentCanvas);
        }
        else {
            printf("Improper add command.\n");
            print_canvas(*currentCanvas);
        }
    }
    else {
        printf("Improper add command.\n");
        print_canvas(*currentCanvas);
    }
}

/**
 * Deletes a row from a "canvas" by moving rows to fill in gap and deallocating memory 
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @param rowPos : int representing which row (bottom row being zero) to delete
 * @return nothing
 * @modifies currentCanvas
 */
void delete_row(canvas* currentCanvas, int rowPos) {
    free(currentCanvas->pixels[currentCanvas->num_rows - rowPos - 1]);
    for (int r = currentCanvas->num_rows - rowPos - 1; r < currentCanvas->num_rows - 1; r++) {
        currentCanvas->pixels[r] = currentCanvas->pixels[r + 1];
    }
    currentCanvas->pixels = (char**)realloc(currentCanvas->pixels, (currentCanvas->num_rows - 1) * sizeof(char*));
    currentCanvas->num_rows--;
}

/**
 * Deletes a column from a "canvas" by moving columns to fill in gap and deallocating memory (one element per row) 
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @param colPos : int representing which column (bottom row being zero) to delete
 * @return nothing
 * @modifies currentCanvas
 */
void delete_col(canvas* currentCanvas, int colPos) {
    for (int r = 0; r < currentCanvas->num_rows; r++) {
        for (int c = colPos; c < currentCanvas->num_cols; c++) {
            currentCanvas->pixels[r][c] = currentCanvas->pixels[r][c + 1]; 
        }
    currentCanvas->pixels[r] = realloc(currentCanvas->pixels[r], (currentCanvas->num_cols - 1) * sizeof(char));
    }
    currentCanvas->num_cols--;
}

/**
 * Deletes a row or column depending on input taken from the user (if valid), otherwise prints what's wrong
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @return nothing
 * @modifies currentCanvas
 */
void delete(canvas* currentCanvas) {
    char selection;
    int c;
    scanf(" %c", &selection);
    if (selection == 'r') {
        int rowPos = getPosInt(true); // -2 for not int -1 for not positive num
        if (rowPos >= 0 && rowPos < currentCanvas->num_rows) {
            delete_row(currentCanvas, rowPos);
            print_canvas(*currentCanvas);
        }
        else {
            printf("Improper delete command.\n");
            print_canvas(*currentCanvas); 
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    else if (selection == 'c') {
        int colPos = getPosInt(true);
        if (colPos >= 0 && colPos < currentCanvas->num_cols) {
            delete_col(currentCanvas, colPos);
            print_canvas(*currentCanvas);
        }
        else {
            printf("Improper delete command.\n");
            print_canvas(*currentCanvas); 
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    else {
        printf("Improper delete command.\n");
        print_canvas(*currentCanvas); 
    }
}

/**
 * Resizes a "canvas" depending on dimensions taken from user (if valid) using add and delete function calls, otherwise prints what's wrong
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @return nothing
 * @modifies currentCanvas
 */
void resize(canvas* currentCanvas) {
    int c;
    int numRows = getValidInt(false);
    int numCols = getValidInt(true);
    if (numCols == -2) {
        printf("Improper resize command.\n"); 
        print_canvas(*currentCanvas); 
        while ((c = getchar()) != '\n' && c != EOF);
    }
    else {
        int numRowsAdd = numRows - currentCanvas->num_rows;
        int numColsAdd = numCols - currentCanvas->num_cols;
        if (numRows != -2 && numRows != -1 && numCols != -2 && numCols != -1 && numRows != 0 && numCols != 0) {
            if (numRowsAdd >= 0) {
                for (int r = 0; r < numRowsAdd; r++) {
                    add_row(currentCanvas, currentCanvas->num_rows);
                }
            }
            if (numColsAdd >= 0) {
                for (int c = 0; c < numColsAdd; c++) {
                    add_col(currentCanvas, currentCanvas->num_cols);
                }
            }
            if (numRowsAdd < 0) {
                for (int r = 0; r < (numRowsAdd * -1); r++) {
                    delete_row(currentCanvas, currentCanvas->num_rows - 1);
                }
            }
            if (numColsAdd < 0) {
                for (int c = 0; c < (numColsAdd * -1); c++) {
                    delete_col(currentCanvas, currentCanvas->num_cols - 1);
                }
            }     
            print_canvas(*currentCanvas);
        }
        else if (numRows == -2) {
            printf("The number of rows is not an integer.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else if (numRows == -1) {
            printf("The number of rows is less than 1.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else if (numCols == -2) {
            printf("The number of columns is not an integer.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else if (numCols == -1) {
            printf("The number of columns is less than 1.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else {
            printf("Improper resize command.\n");
            print_canvas(*currentCanvas); 
        }
    }
}

/**
 * "Saves" a canvas by taking a "name" from the user (if valid) and adding a copy of the currentCanvas canvas struct to savedCanvases, otherwise prints what's wrong
 * @param savedCanvases : pointer to array of canvas structs representing saved canvases
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @param num_saved_canvases : pointer to int representing the number of canvases saved
 * @return nothing
 * @modifies savedCanvases, num_saved_canvases
 */
void save_canvas(canvas** savedCanvases, canvas* currentCanvas, int* num_saved_canvases) {
    char* input = getValidStr(false);
    if (input != NULL) {
        *savedCanvases = realloc(*savedCanvases, (*num_saved_canvases + 1) * sizeof(canvas));
        *num_saved_canvases += 1;
        (*savedCanvases)[*num_saved_canvases - 1] = create_canvas(currentCanvas->num_rows, currentCanvas->num_cols);
         for (int i = 0; i < currentCanvas->num_rows; i++) {
            strcpy((*savedCanvases)[*num_saved_canvases - 1].pixels[i], currentCanvas->pixels[i]);
        }
        (*savedCanvases)[*num_saved_canvases - 1].name = strdup(input);
        print_canvas(*currentCanvas);    
    } else {
        printf("Improper save command or file could not be created.\n");
    }
   if (input != NULL) free(input); 
}

/**
 * "Loads" a canvas by taking a "name" from the user (if valid) and setting currentCanvas to the name matching canvas from SavedCanvases (after printing it), otherwise prints what's wrong
 * @param savedCanvases : array of canvas structs representing saved canvases
 * @param currentCanvas : pointer to canvas struct representing the current canvas being dealt with/modified 
 * @param num_saved_canvases : pointer to int representing the number of canvases saved
 * @param canvasLoaded : pointer to int representing index of the canvas "loaded" in savedCanvases
 * @return nothing
 * @modifies savedCanvases, currentCanvas, num_saved_canvases, canvasLoaded
 */
void load_canvas(canvas* savedCanvases, canvas* currentCanvas, int num_saved_canvases, int* canvasLoaded) {
    char* input = getValidStr(false);
    bool fileFound = false;
    if (strcmp(input, "Invalid") != 0) {
        for (int i = 0; i < num_saved_canvases; i++) {
            if (strcmp(input, savedCanvases[i].name) == 0) {
                print_canvas(savedCanvases[i]); 
                *currentCanvas = savedCanvases[i];
                *canvasLoaded = i;
                fileFound = true;
                break;
            }
        } 
        if (fileFound == false) printf("Improper load command or file could not be opened.\n");
    }
    else {
        printf("Improper load command or file could not be opened.\n");
    }
    if (input != NULL) free(input); 
}