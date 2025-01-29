all: 
	arm-linux-gnueabihf-gcc -Wall -g -std=c99 -D_POSIX_C_SOURCE=200809L -Werror main.c button.c joystick_direction.c joystick_read.c gameToMatrix.c board.c timeHelper.c initializeMatrix.c rotate.c -lm -o tetris

	cp tetris $(HOME)/cmpt433/public/myApps/

clean:

	rm -f $(HOME)/cmpt433/public/myApps/tetris tertris

cleanAs1:

	rm -f tetris
