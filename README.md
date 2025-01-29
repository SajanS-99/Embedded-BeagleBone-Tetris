# Embedded-BeagleBone-Tetris

A tetris clone written for the BeagleBone Green single board computer written in C.

The various files are used to interface with buttons, a joystick, and 2 8*8 LED matrices stacked on top of one another. 

The core game loop is simply tetris. Each piece has a 4 by 4 bounding box where each update it is checked around. If any piece colides with another piece or the bottom of the board, it stops updating that piece, and sets it down. Then a new piece is spawned and the user repeats that cylce. 

The makefile targets an arm core since the BeagleBone uses an arm cpu.

