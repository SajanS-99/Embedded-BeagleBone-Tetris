#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "initializeMatrix.h"

#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"

// code taken from example given by instructor

int initI2cBus(char* bus, int address){

    // configs the 2 pins, code taken from assignment 1
    FILE *pipe = popen("config-pin p9_17 i2c; config-pin p9_18 i2c", "r");
    
    
            if (pipe == NULL){
                printf("Error opening/executing command");
                exit(1);
           }

           pclose(pipe);
    // opems bus. code given by prof
    int i2cFileDesc = open(bus, O_RDWR);
    int result = ioctl(i2cFileDesc, I2C_SLAVE, address);

    if (result < 0) {
        perror("I2C: Unable to set I2C device to slave address.");
        exit(1);
    }
    
    return i2cFileDesc;
}

int initI2cBus2(char* bus, int address){

    // configs the 2 pins, code taken from assignment 1
    FILE *pipe = popen("config-pin p9_19 i2c; config-pin p9_20 i2c", "r");
    
    
            if (pipe == NULL){
                printf("Error opening/executing command");
                exit(1);
           }

           pclose(pipe);
    // opems bus. code given by prof
    int i2cFileDesc = open(bus, O_RDWR);
    int result = ioctl(i2cFileDesc, I2C_SLAVE, address);

    if (result < 0) {
        perror("I2C: Unable to set I2C device to slave address.");
        exit(1);
    }
    
    return i2cFileDesc;
}


// code given to by prof, writes to matrix by sending array of 17 char
void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value[]) {
   
    unsigned char buff[17];
    buff[0] = regAddr;
    for (int i = 1; i <17; i++){
        buff[i] = value[i];
    }

    int res = write(i2cFileDesc, buff, 17);
    if (res != 17) {
        perror("I2C: Unable to write i2c register.");
        exit(1);
    }
}
// code given by prof, reads the current state of matrix
unsigned char readI2cReg(int i2cFileDesc, unsigned char regAddr) {
// To read a register, must first write the address
        int res = write(i2cFileDesc, &regAddr, sizeof(regAddr));

        if (res != sizeof(regAddr)) {
            perror("I2C: Unable to write to i2c register.");
            exit(1);
        }
// Now read the value and return it
        char value = 0;
        res = read(i2cFileDesc, &value, sizeof(value));
        if (res != sizeof(value)) {
            perror("I2C: Unable to read from i2c register");
            exit(1);
        }

    return value;
}