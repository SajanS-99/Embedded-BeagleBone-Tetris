#include "joystick_direction.h"
#include "joystick_read.h"
#include <stdio.h>


//assumes will be using pin 2/3 for X/Y respectively, but can easily be changed later

// NOT Selected = 0
// LEFT = 1
// RIGHT = 2
// UP = 3
// DOWN = 4
// If both X/Y direction pressed at same time, chooses the Y direction over X every time

// Assume orientiation of joystick is:

//      + Y X -    
// A                <- Y
// N                     X   
// A                     | 
// L                     ^
// O
// G
// This is bottom of board, direction user faces is up toward top



int readDirection(){

    // Around x == 2000 and y == 2000 is centered, so +/- 1000 for each direction is
    // arbitrately chosen for the direction cutoffs

    int readX = readJoyStickX(2);
    int readY = readJoyStickY(3);

    if (readY > 3000){
        return 1; // return LEFT is joystick to left
    } else if (readY < 1000){
        return 2; // return RIGHT
    } else if (readX < 1000){
        return 3; // return UP
    } else if (readX > 3000){
        return 4; //return DOWN
    } else {
        return 0; //else return unpressed
    }
}