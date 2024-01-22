# Paint

## Versatile console based drawing program 

## How to Use
1. Create a "canvas" by calling the program with a specified size, or default to 10 X 10
2. Use the multitude of commands the program allows:
    1. Help: h | Prints all available commands
    2. Quit: q | Quits program
    3. Draw line: w row_start col_start row_end col_end | Draws a line on the canvas (horizontal, vertical, or diagonal)
    4. Resize: r num_rows num_cols | Resizes the canvas to a specified size
    5. Add row or column: a [r | c] pos | Adds a row or column to a specified position
    6. Delete row or column: d [r | c] pos | Deletes a row or column from a specified position
    7. Erase: e row col\n | Erases a spot (makes blank)
    8. Save: s file_name | Saves a canvas by a specified name
    9. Load: l file_name | Access a previously saved canvas by a specified name

## Features
1. Robust input validation and error messaging (wrong use of commands, explains to user, accounts for all cases)
2. Dynamically allocated 2D arrays that are stored by 3D array (save feature)
3. All functions use dynamically allocated memory and free memory accordingly

 ## Demo Screenshots
_Draw Command_
![Draw](https://github.com/fcheung23/Paint/blob/main/screenshots/Draw%20-%20Paint.png)

_Help_
![Help](https://github.com/fcheung23/Paint/blob/main/screenshots/Help%20-%20Paint.png)

_Save and Load Commands_
![Save and Load](https://github.com/fcheung23/Paint/blob/main/screenshots/Save%20and%20Load%20-%20Paint.png)

_Resize Command_
![Resize](https://github.com/fcheung23/Paint/blob/main/screenshots/Resize%20-%20Paint.png)



