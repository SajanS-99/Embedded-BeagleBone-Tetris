#include "button.h"
#include <stdio.h>
#include <stdlib.h>

// pins used
#define USER_BUTTON_PATH1 "/sys/class/gpio/gpio66/value"
#define USER_BUTTON_PATH2 "/sys/class/gpio/gpio67/value"
#define USER_BUTTON_PATH3 "/sys/class/gpio/gpio69/value"
//reads gpio value and returns it. Reused from assignment 1/2
// code was provided by prof
// no claim to ownership of code
int returnReadFromButton1(){
    FILE *pFILE = fopen(USER_BUTTON_PATH1, "r");
    if (pFILE == NULL){
        printf("Unabled to open file (%s) to read\n", USER_BUTTON_PATH1);
        exit(1);
    }

    int value;
    fscanf(pFILE, "%d", &value);

    fclose(pFILE);

    return value;
}

int returnReadFromButton2(){
    FILE *pFILE = fopen(USER_BUTTON_PATH2, "r");
    if (pFILE == NULL){
        printf("Unabled to open file (%s) to read\n", USER_BUTTON_PATH2);
        exit(1);
    }

    int value;
    fscanf(pFILE, "%d", &value);

    fclose(pFILE);

    return value;
}

int returnReadFromButton3(){
    FILE *pFILE = fopen(USER_BUTTON_PATH3, "r");
    if (pFILE == NULL){
        printf("Unabled to open file (%s) to read\n", USER_BUTTON_PATH3);
        exit(1);
    }

    int value;
    fscanf(pFILE, "%d", &value);

    fclose(pFILE);

    return value;
}