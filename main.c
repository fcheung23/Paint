#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <math.h>
#include "canvas.h" 
#include "commands.h"
#include "input.h"

/**
 * Text-based "drawing" program that uses "canvases" made of 2d arrays and takes commands from user
 * @param argc : int representing number of arguments entered on command line
 * @param argv : array of strings representing arguments entered on command line
 * @return 0
 * @modifies nothing directly
 */
int main(int argc, char* argv[]) {
    canvas* savedCanvases = (canvas*)malloc(sizeof(canvas));
    int num_saved_canvases = 0;
    canvas currentCanvas = create_initial_canvas(argc, argv); 
    print_canvas(currentCanvas); 
    while(1) {
        printf("\nEnter your command: ");
        getValidCommand(false, &currentCanvas, savedCanvases, &num_saved_canvases);
    }
    return 0;
}

