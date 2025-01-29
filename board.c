#include <stdio.h>
#include "board.h"
#include "rotate.h"

//initializes edges of board with 1
void setUpBoard(int boardHeight, int boardWidth, int board[boardHeight][boardWidth]){
    for (int i = 0; i < boardHeight; i++){
        for (int j = 0; j < boardWidth; j++){
            if (j == 0 || j == boardWidth-1 || i == boardHeight-1){
                board[i][j] = 1;
            } else {
                board[i][j] = 0;
            }
        }
    }
}

// check for seeing if we can increment to a new position
//gets the relative position of the piece
// and checks it with respect to the board array
//if board array == 1, it means there is a collision since
// something is there before hand
bool checkIfPieceFits(int sizeX, int sizeY, int pieceArr[sizeX][sizeY], int rotation, int boardX, int boardY, int boardHeight, int boardWidth, int boardArr[boardHeight][boardWidth]){

    for (int row = 0; row < sizeX; row++){
        for (int col = 0; col < sizeY; col++){

                // get index to check
               int currentRotatePieceToCheck = checkRotateIndex(row,col,rotation,sizeX,sizeY,pieceArr);

                int posFieldX = row+boardX;

                int posFieldY = col+boardY;
                // check over board array positon, if both piece and board don't equal 0, means there was a
                // an overlap of pieces, so you can place
                // if both do equal 1, then return false since there is an overlap
                if (posFieldX >= 0 && posFieldX < boardHeight){
                    if (posFieldY >= 0 && posFieldY < boardWidth){
                        if (currentRotatePieceToCheck != 0 && boardArr[posFieldX][posFieldY] != 0){
                        return false;
                        }
                    }
                } 
        }
    }

    return true;

}
// get piece's relative position to board, and write it to the board array
// this essentally means piece is now placed on board, and next piece should start moving
void lockPiece(int sizeX, int sizeY, int pieceArr[sizeX][sizeY], int boardHeight, int boardWidth, int boardArr[boardHeight][boardWidth], int currentXPos, int currentYPos){

    for (int i = 0; i < sizeX; i++){
        for (int j = 0; j < sizeY; j++){
            int xToPlace = i+currentXPos;
            int yToPlace = j+currentYPos;

            // write 1 if space not empty(ie piece is present on that index)
            if (pieceArr[i][j] != 0){
                boardArr[xToPlace][yToPlace] = 1;
            }
        }
    }


}

//check for any fulls lines, if so remove and return number of lines removed(for score later)
int checkUpdatedFullLines(int boardHeight, int boardWidth, int board[boardHeight][boardWidth]){
    int score = 0;
    int tracker = 0;
    //check row by row, increment tracker by 1 if spot is full in row
    for (int i = 0; i < boardHeight-1; i++){
        for(int j = 1; j < boardWidth-1; j++){
            if (board[i][j] == 1){
                tracker++;
            }
        }
        // 8 == full line
        // this implies we should remove current row
        if (tracker == 8){
            score += 1;
            //set row to 0
            for(int j = 1; j < boardWidth-1; j++){
                board[i][j] = 0;
                
            }
            // move above rows down by 1
            for(int k = i; k >= 1; k-- ){
                for (int j = 1; j < boardWidth-1; j++){
                    board[k][j] = board[k-1][j];
        
                }
            }
        
        }
        //reset row tracker
        tracker = 0;
    }

    return score;

}

//write piece array to new piece
//called after locking old piece
void newPiece(int sizeX, int sizeY, int piece[sizeX][sizeY], int random){

    switch (random)
    {
    case 0:
        piece[0][0] = 0; piece[0][1] = 1; piece[0][2] = 1; piece[0][3] = 0;
        piece[1][0] = 0; piece[1][1] = 1; piece[1][2] = 1; piece[1][3] = 0;
        piece[2][0] = 0; piece[2][1] = 0; piece[2][2] = 0; piece[2][3] = 0;
        piece[3][0] = 0; piece[3][1] = 0; piece[3][2] = 0; piece[3][3] = 0;
        break;
    case 1:
        piece[0][0] = 0; piece[0][1] = 1; piece[0][2] = 0; piece[0][3] = 0;
        piece[1][0] = 0; piece[1][1] = 1; piece[1][2] = 0; piece[1][3] = 0;
        piece[2][0] = 0; piece[2][1] = 1; piece[2][2] = 0; piece[2][3] = 0;
        piece[3][0] = 0; piece[3][1] = 1; piece[3][2] = 0; piece[3][3] = 0;
        break;
    case 2:
        piece[0][0] = 0; piece[0][1] = 1; piece[0][2] = 1; piece[0][3] = 0;
        piece[1][0] = 1; piece[1][1] = 1; piece[1][2] = 0; piece[1][3] = 0;
        piece[2][0] = 0; piece[2][1] = 0; piece[2][2] = 0; piece[2][3] = 0;
        piece[3][0] = 0; piece[3][1] = 0; piece[3][2] = 0; piece[3][3] = 0;
        break;
    case 3:
        piece[0][0] = 0; piece[0][1] = 0; piece[0][2] = 1; piece[0][3] = 0;
        piece[1][0] = 0; piece[1][1] = 0; piece[1][2] = 1; piece[1][3] = 0;
        piece[2][0] = 0; piece[2][1] = 1; piece[2][2] = 1; piece[2][3] = 0;
        piece[3][0] = 0; piece[3][1] = 0; piece[3][2] = 0; piece[3][3] = 0;
        break;
    case 4:
        piece[0][0] = 0; piece[0][1] = 1; piece[0][2] = 1; piece[0][3] = 0;
        piece[1][0] = 0; piece[1][1] = 0; piece[1][2] = 1; piece[1][3] = 0;
        piece[2][0] = 0; piece[2][1] = 0; piece[2][2] = 1; piece[2][3] = 0;
        piece[3][0] = 0; piece[3][1] = 0; piece[3][2] = 0; piece[3][3] = 0;
        break;
    case 5:
        piece[0][0] = 0; piece[0][1] = 0; piece[0][2] = 1; piece[0][3] = 0;
        piece[1][0] = 0; piece[1][1] = 1; piece[1][2] = 1; piece[1][3] = 0;
        piece[2][0] = 0; piece[2][1] = 0; piece[2][2] = 1; piece[2][3] = 0;
        piece[3][0] = 0; piece[3][1] = 0; piece[3][2] = 0; piece[3][3] = 0;
        break;
    case 6:
        piece[0][0] = 0; piece[0][1] = 1; piece[0][2] = 1; piece[0][3] = 0;
        piece[1][0] = 0; piece[1][1] = 0; piece[1][2] = 1; piece[1][3] = 1;
        piece[2][0] = 0; piece[2][1] = 0; piece[2][2] = 0; piece[2][3] = 0;
        piece[3][0] = 0; piece[3][1] = 0; piece[3][2] = 0; piece[3][3] = 0;
        break;    
    
    default:
        printf("FATAL ERROR IN WRITING PIECE\n");
        break;
    }

}

//helper function for debugging
void print2dArray(int sx, int sy, int array[sx][sy]){
    for (int i = 0; i < sx; i++){
        for (int j = 0; j < sy; j++){
            printf(" %d ", array[i][j]);
        }
        printf("\n");
    }

    printf("\n");

}