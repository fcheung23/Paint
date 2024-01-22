# Paint

## Versatile console based drawing program 

## How to Use
1. Create a "canvas" by calling the program with a specified size, or default to 10 X 10
2. Use the multitude of commands the program allows:
  a. Help: h | Prints all available commands
  b. Quit: q | Quits program
  c. Draw line: w row_start col_start row_end col_end | Draws a line on the canvas (horizontal, vertical, or diagonal)
  d. Resize: r num_rows num_cols | Resizes the canvas to a specified size
  e. Add row or column: a [r | c] pos | Adds a row or column to a specified position
  f. Delete row or column: d [r | c] pos | Deletes a row or column from a specified position
  g. Erase: e row col\n | Erases a spot (makes blank)
  h. Save: s file_name | Saves a canvas by a specified name
  i. Load: l file_name | Access a previously saved canvas by a specified name

## Features
1. Robust input validation and error messaging (wrong use of commands, explains to user, accounts for all cases)
2. Dynamically allocated 2D arrays that are stored by 3D array (save feature)
3. All functions use dynamically allocated memory and free memory accordingly

 ## Gameplay Screenshots
_Tutorial Screen_
![Tutorial](https://github.com/fcheung23/Battleship/blob/main/screenshots/Tutorial%20-%20BattleShip.png)

_Ship Placement_
![Ship Placement](https://github.com/fcheung23/Battleship/blob/main/screenshots/Ship%20Placement%20-%20BattleShip.png)

_Ship Status_
![Ship Status](https://github.com/fcheung23/Battleship/blob/main/screenshots/Ship%20Status%20-%20BattleShip.png)

_Hit Screen_
![Hit Screen](https://github.com/fcheung23/Battleship/blob/main/screenshots/Hit%20Screen%20-%20BattleShip.png)

_Miss Screen_
![Miss Screen](https://github.com/fcheung23/Battleship/blob/main/screenshots/Miss%20Screen%20-%20BattleShip.png)

_Win Screen_
![Win Screen](https://github.com/fcheung23/Battleship/blob/main/screenshots/Win%20Screen%20-%20BattleShip.png)


