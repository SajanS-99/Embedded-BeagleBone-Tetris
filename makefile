all: 
	arm-linux-gnueabihf-gcc -Wall -g -std=c99 -D_POSIX_C_SOURCE=200809L -Werror main.c button.c joystick_direction.c joystick_read.c gameToMatrix.c board.c timeHelper.c initializeMatrix.c rotate.c -lm -o tetris


clean:

	rm -f tetris

