/*

Main driver file for the led 8x8 matrix.

Has functions for setting up the matrix, writing an arbitary array, and reading 
from the matrix

*/

#ifndef INITIALIZEMATRIX_H
#define INITIALIZEMATRIX_H

int initI2cBus(char* bus, int address);

int initI2cBus2(char* bus, int address);


void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value[]);

unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr);

#endif
