# ENGR103finalgame
Color-matching game for an ENGR 103 final at Oregon State University, using an Adafruit Circuit Playground Express. 

## Author
Noah Fisher

Color Matching Game

This game is like golf - you want to get as low a score as possible. 
The serial monitor will start by outputting level 1. Get ready! This means the game is about to begin.
A color is shown for 5 seconds the board will beep for each second the color is shown, in a descending scale. The color is cleared.

To submit your score, press both buttons. 

The right button increases the green value by a small increment until the value is 170, then it resets to 0. 255 is too white and not discernable from any other color; the game would be near impossible if it asked you to match pure white. 
If the switch is on, the left button increases the blue led. If it's off, the left button increases the red led. 
If the circuit board is shaken, all values get reset to 0 (board is cleared, etch-a-sketch style). 
If both buttons are pressed, active values are subtracted by one increment (to account for difference offset) and, if uncommented, these values will be printed to the serial monitor. Otherwise, the values are checked against the shown color, and points are given based on how far each value is from the original. 

Game resets with the reset button. It will show the same color each time regardless unless copied to a new file.

This code can be expanded upon. Ideas:
Level change -
Serial monitor outputs level 2, A color is shown for 1 second. The color is cleared. The point system repeated. Total points are shown.
Serial monitor outputs level 3, A color is shown for .5 seconds. The color is cleared. The point system repeated. Total points are shown.
Serial monitor outputs level 4, A color is shown for .25 seconds. The color is cleared. The point system repeated. Total points are shown.
Serial monitor outputs level 5, A color is shown for .1 seconds. The color is cleared. The point system repeated. Total points are shown.


User inputs/outputs 

Inputs
Left Button (switch off): Increases blue (0-160)
Left Button (switch on): Increases red (0-160)
Right button: Increases green (1-160)
Shake: Clear all colors (0)
Left and right button: print RGB values

Outputs
Sound: will indicate if time
Light: Main component of the game, mixed to match the shown value
