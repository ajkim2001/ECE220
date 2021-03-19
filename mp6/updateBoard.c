/* 
Alex Kim netid:alexk4 3/19/2021
In this program I had to implement 3 functions: countLiveNeighbor, updateBoard, and aliveStable.
For countLiveNieghbor, I incremented through each row within bounds, then each column within bounds,
and then made sure I wasn't on the main cell to check if there were any living neighbor cells. 
If I found one, I would increment my variable alive to be returned.
For updateBoard, I created a temporary array in which I copied the current board. 
Then I incremented through the entire board, using the countLiveNeighbor function, in order to check
whether the current cell should die or live or stay the same.
For aliveStable, I created another temporary array that I copied the current board to.
Then I called update board with the temporary array to compare the old board to the next one.
I then incremented through every cell to check that everything was the same. If they were identical,
I would return 1. Otherwise, I returned a 0.
*/

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int alive = 0; //number of live neighbors
for(int i = row - 1; i <= row + 1; i++){ //checks row above to below
    if(i >= 0 && i < boardRowSize){ //row must be within board
        for(int j = col-1; j <= col+1; j++){ //checks column left to right
            if(j >= 0 && j < boardColSize){ //column must be within board
                if(i != row || j != col){ //as long as we are not on the main cell
                    if(board[i*boardColSize + j] == 1){ //if current cell alive, increment alive
                        alive += 1;
                    }
                }
            }
        }
    }
}
return alive;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int tempBoard[boardRowSize*boardColSize]; //temporary board checked to create next board
    int alive; //number of neighbors alive
    for(int i = 0; i < boardRowSize; i++){ //goes through each row
        for (int j = 0; j < boardColSize; j++){ //goes through each column
            tempBoard[i*boardColSize + j] = board[i*boardColSize + j]; //copies board onto tempboard
        }
    }
    for(int j = 0; j < boardRowSize*boardColSize; j++){ //goes through the whole board
        alive = countLiveNeighbor(tempBoard, boardRowSize, boardColSize, j/boardColSize, j%boardColSize); //call function to check number of live neighbors
        if(alive < 2 || alive > 3){
            *(board + j) = 0; //cell dies if less than 2 or more than 3
        }
        else if(alive == 3){
            *(board + j) = 1; //cell lives if exactly 3, otherwise stays same
        }
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int nextBoard[boardRowSize*boardColSize]; //temporary board to check the next board
    for(int i = 0; i < boardRowSize; i++){ //goes through each row
        for (int j = 0; j < boardColSize; j++){ //goes through each column
            nextBoard[i*boardColSize + j] = board[i*boardColSize + j]; //copies board onto nextboard
        }
    }
    updateBoard(nextBoard, boardRowSize, boardColSize); //calls function to create the nextBoard
    for(int k = 0; k < boardColSize*boardRowSize; k++){ // checks all through boards
        if(board[k] != nextBoard[k]){ // if any part of the boards aren't the same, return 0
            return 0;
        }
    }
    return 1; //otherwise return 1 if all is same
}