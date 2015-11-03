# MarsRovers_C 

1 - Extract all files to the same folder.

2 - Double click "MarsRovers.exe" to execute.

3 - Enter upper-right coordinates of the plateau (x y) separated by space and press enter. Bottom-left coordinates are (0 0)
(Click example1.png for and example)

4 - Enter Rover position (x y) within the range determined in "3". 
Enter Rover orientation of N (for north), S (for south), E (for east), W (for west).
All 3 inputs are separated by space.

5 - Enter Rover comands strings by entering L, R (for 90 degrees left or right rotation, respectively) and M for one grid movement.
(No space)

6 - Press anykey and enter to enter another Rover or just enter to execute.

----

The program will output a ERROR message if:

. Any input value type is different from expected -> Program will request re-input.
. Rover input position is outsite of the plateau range -> Program will request re-input.
. Orientation input is not 'N', 'S', 'E' or 'W' -> Program will request re-input.
. Comand string include char that are not 'L', 'R' or 'M' -> Program will request re-input.
. Rover comand sends it outside of the plateau -> Rover movement will stop.
. Rover comand put it into collision with another Rover -> Rover movement will stop.
. Initial position of a Rover coincides with final position of previous Rover -> Program will request re-input.