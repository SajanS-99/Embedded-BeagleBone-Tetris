#include <stdio.h>
#include "rotate.h"
#include "board.h"
#include "gameToMatrix.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "initializeMatrix.h"
#include <stdbool.h>
#include "timeHelper.h"
#include "joystick_direction.h"
#include "button.h"
#include <time.h>
// for i2c
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"
#define I2C_DEVICE_ADDRESS 0x70

//board constants
int boardHeightOfGame = 18;
int boardWidthOfGame = 10;

int printHeight = 10;
int printWidth = 18;






int main(int argc, char *argv[]){

    //set up i2c registers
    unsigned char testSetp[1] = {0x00};
    unsigned char zeroClose[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1,I2C_DEVICE_ADDRESS);
    writeI2cReg(i2cFileDesc,0x21, testSetp);
    writeI2cReg(i2cFileDesc,0x81, testSetp);

    
    int i2cFileDesc2 = initI2cBus2(I2CDRV_LINUX_BUS2,I2C_DEVICE_ADDRESS);
    writeI2cReg(i2cFileDesc2,0x21, testSetp);
    writeI2cReg(i2cFileDesc2,0x81, testSetp);
    
    
    //set up piece and board
    int board[boardHeightOfGame][boardWidthOfGame];

    int piece[4][4] = {{ 0, 1, 1, 0},{ 0, 1, 1, 0},{ 0, 0, 0, 0},{ 0, 0, 0, 0}};

    srand((unsigned int)time(NULL)); // seed for rand later


    //set up iniitial piece position
    int xC = 0;
    int yC = boardWidthOfGame/2-2;

  
    // set up board and temp boards for writing
    setUpBoard(boardHeightOfGame,boardWidthOfGame,board);

    int temp_1[boardHeightOfGame][boardWidthOfGame];

    int temp_2[boardWidthOfGame][boardHeightOfGame];

    // flag for game loop
   bool isTertrisOver = false;

    // overall timer to go down
   long long timeFromLastDown = getTimeInMs();
   long long timeCheckToDown = getTimeInMs();

    // used for preventing repreat input from 1 joystick press
   long long timeFromLastDirection = getTimeInMs();
   long long timeCheckToDirection = getTimeInMs();

    // used for button latches to prevent bouncing
   long long button1Last = getTimeInMs();
   long long button1Current = getTimeInMs();

   long long button2Last = getTimeInMs();
   long long button2Current = getTimeInMs(); 

   int score = 0;



    //while not over
   while (!isTertrisOver){


    // read dirction from joystick
    if (timeCheckToDirection - timeFromLastDirection > 100){
        switch (readDirection()) {
        case 0:
            timeFromLastDirection = getTimeInMs();
            break;

        // move left or right if possible
        // check if next right/left index free, if so move to that point(and print to matrix leds)
        case 1:
        if(checkIfPieceFits(4,4,piece,0,xC,yC+1, boardHeightOfGame,boardWidthOfGame,board)){

                yC++;

                prepareCopyOfBoard(4,4,piece,boardHeightOfGame,boardWidthOfGame,board,xC,yC,temp_1,temp_2);

                writeToMatrix(boardHeightOfGame,boardWidthOfGame,temp_2, i2cFileDesc,i2cFileDesc2);

                timeFromLastDirection = getTimeInMs();
                }
            break; 

        case 2:
        if(checkIfPieceFits(4,4,piece,0,xC,yC-1, boardHeightOfGame,boardWidthOfGame,board)){

                yC--;

                prepareCopyOfBoard(4,4,piece,boardHeightOfGame,boardWidthOfGame,board,xC,yC,temp_1,temp_2);

                writeToMatrix(boardHeightOfGame,boardWidthOfGame,temp_2, i2cFileDesc,i2cFileDesc2);

                timeFromLastDirection = getTimeInMs();
                }
            break;

         //else do nothing
        default:

            timeFromLastDirection = getTimeInMs();
            break;
        }
    }
    // >200 ms to prevent bouncing 
    // check read and rotate if possible
    if ((button1Current - button1Last >  200) && (returnReadFromButton1() == 1)){
        if(checkIfPieceFits(4,4,piece,1,xC,yC, boardHeightOfGame,boardWidthOfGame,board)){
            updateRotate(1,4,4,piece);
            button1Last = getTimeInMs();
        }
    }

    if (button2Current - button2Last > 200 && returnReadFromButton2() == 1){
        if(checkIfPieceFits(4,4,piece,2,xC,yC, boardHeightOfGame,boardWidthOfGame,board)){
            updateRotate(2,4,4,piece);
            button1Last = getTimeInMs();
        }
    } 


   

    // if more than .8s have gone, move piece down
    if (timeCheckToDown - timeFromLastDown > 800){

        // if piece can go down, go down 
        if(checkIfPieceFits(4,4,piece,0,xC+1,yC, boardHeightOfGame,boardWidthOfGame,board)){
           
            xC++;

            prepareCopyOfBoard(4,4,piece,boardHeightOfGame,boardWidthOfGame,board,xC,yC,temp_1,temp_2);

            writeToMatrix(boardHeightOfGame,boardWidthOfGame,temp_2, i2cFileDesc, i2cFileDesc2);



            timeFromLastDown = getTimeInMs();
        // else if can't go down, lock current position
        } else {
            lockPiece(4,4,piece,boardHeightOfGame,boardWidthOfGame,board,xC,yC);

            

            prepareCopyOfBoard(4,4,piece,boardHeightOfGame,boardWidthOfGame,board,xC,yC,temp_1,temp_2);

            writeToMatrix(boardHeightOfGame,boardWidthOfGame,temp_2, i2cFileDesc, i2cFileDesc2);

            timeFromLastDown = getTimeInMs();
            // reset position and get new piece
            xC = 0;
            yC = boardWidthOfGame/2-2;

            int r = rand() % 7;

            newPiece(4,4,piece,r);
        
        }

    }






        // if piece instantly cannot move in starting posistion, turn off game
        if(!checkIfPieceFits(4,4,piece,0,xC,yC, boardHeightOfGame,boardWidthOfGame,board)){
            printf("\n\n\nGAME OVER\n");
            isTertrisOver = true;

            prepareCopyOfBoard(4,4,piece,boardHeightOfGame,boardWidthOfGame,board,xC,yC,temp_1,temp_2);

            writeToMatrix(boardHeightOfGame,boardWidthOfGame,temp_2, i2cFileDesc,i2cFileDesc2);
        }
        // check lines, update score
        score += checkUpdatedFullLines(boardHeightOfGame,boardWidthOfGame,board);
        // update latches
        button1Current = getTimeInMs();
        button2Current = getTimeInMs();
        timeCheckToDown = getTimeInMs();
        timeCheckToDirection = getTimeInMs();

   }

    
    
    // print score, turn off led matrices, and close files
    printf("Score was %d\n", score);

    writeI2cReg(i2cFileDesc,0x00,zeroClose);
    writeI2cReg(i2cFileDesc2,0x00,zeroClose);
    close(i2cFileDesc);
    close(i2cFileDesc2);




    return 0;

}