#include "joystick_read.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// code from example, given by instructor. Not claimed to be own code
// code for file opening and reading/returning given by instructor
// also reused from assignment 2 for project
#define A2D_FILE_VOLTAGE0  "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"

int readJoyStickX(int Num){
    
    char buffer[50];
    
    // put file path of the Num of A2D pin you're reading from to buffer for file
    snprintf(buffer, 50, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", Num);

    FILE *f = fopen(buffer, "r");
    if (!f) {
		printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
		printf("       Check /boot/uEnv.txt for correct options.\n");
		exit(-1);
	}

	// Get reading
	int a2dReadingX = 0;
	int itemsRead = fscanf(f, "%d", &a2dReadingX);
	if (itemsRead <= 0) {
		printf("ERROR: Unable to read values from voltage input file.\n");
		exit(-1);
	}

	// Close file
	fclose(f);

	return a2dReadingX;

}

int readJoyStickY(int Num){
    
    char buffer[50];
    
    // put file path of the Num of A2D pin you're reading from to buffer for file
    snprintf(buffer, 50, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", Num);

    FILE *f = fopen(buffer, "r");
    if (!f) {
		printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
		printf("       Check /boot/uEnv.txt for correct options.\n");
		exit(-1);
	}

	// Get reading
	int a2dReadingY = 0;
	int itemsRead = fscanf(f, "%d", &a2dReadingY);
	if (itemsRead <= 0) {
		printf("ERROR: Unable to read values from voltage input file.\n");
		exit(-1);
	}

	// Close file
	fclose(f);

	return a2dReadingY;

}