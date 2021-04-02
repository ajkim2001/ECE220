/*
Alex Kim netid:alexk4 4/2/2021
In this program I had to implement 8 functions to create the 2048 game.
In make_game I iterated through each cell and initialize them all to empty (-1).
In remake_game, I created new rows and cols where all the cells were initalized empty.
In get_cell, I checked if the cell was in bounds before returning its pointer.
In the 4 move functions, I had to iterate through all rows and columns. I checked for a filled cell, 
then checked the cells before it to find empty cells to move it to and same valued cells to merge it with.
In legal_move_check, I looked for an empty cell or if any moves could be made before returning 1.
*/
#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;
    mygame->cols = cols;
    mygame->score = 0; //initialize rows, columns, and score
    int i;
    for(i = 0; i < rows * cols; i++){ //iterate through each cell
        mygame->cells[i] = -1; //initialize all cells to be empty
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows;
    (*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)->score = 0; //reinitialize rows, columns, and score
    int i;
    for(i = 0; i < new_rows * new_cols; i++){ //iterate through each new cell
        (*_cur_game_ptr)->cells[i] = -1; //initialize all new cells to be empty
    }
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if(cur_game->rows <= row || cur_game->cols <= col || row < 0 || col < 0){
        return NULL; //in the case when row or col is out of bounds return NULL
    }
    return cur_game->cells + (row * cur_game->cols + col); //otherwise return pointer
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int i, j, k; //initialize variables
    int cols = cur_game->cols;
    int rows = cur_game->rows;
    int valid = 0; 
    int merged = 0;
    for(j = 0; j < cols; j++){ //iterate througwh columns
        merged = -422021; //initialize for each column
        for(i = 0; i < rows; i++){ //iterate through rows
            if(cur_game->cells[i * cols + j] != -1){ //if the cell isn't empty
                for(k = 0; k < i && cur_game->cells[k * cols + j] != -1; k++){
                } //find a cell that is empty above current row
                if(k < i){ //if found above, move current cell into new cell and empty current cell
                    cur_game->cells[k * cols + j] = cur_game->cells[i * cols + j];
                    cur_game->cells[i * cols + j] = -1;
                    valid = 1; //update valid 
                } //if row above was not merged and the cells are equal, 
                if((k - 1) != merged && cur_game->cells[k * cols + j] == cur_game->cells[(k - 1) * cols + j]){ 
                    cur_game->cells[(k - 1) * cols + j] = cur_game->cells[k * cols + j] * 2; //merge cells
                    cur_game->cells[k * cols + j] = -1; //empty old cell
                    merged = k - 1; //update merged to row above
                    cur_game->score += cur_game->cells[(k - 1) * cols + j]; //update score, adding value of new cell
                    valid = 1; //update valid
                }
            }
        }
    }
    return valid; //return whether a valid move was made or not
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int i, j, k; //initialize variables
    int cols = cur_game->cols;
    int rows = cur_game->rows;
    int valid = 0; 
    int merged = 0;
    for(j = cols - 1; j >= 0; j--){ //iterate  backwards through columns
        merged = rows; //initialize for each column
        for(i = rows - 1; i >= 0; i--){ //iterate backward through rows
            if(cur_game->cells[i * cols + j] != -1){ //if the cell isn't empty
                for(k = rows - 1; k > i && cur_game->cells[k * cols + j] != -1; k--){
                } //find a cell that is empty below current row
                if(k > i){ //if found below, move cell down
                    cur_game->cells[k * cols + j] = cur_game->cells[i * cols + j];
                    cur_game->cells[i * cols + j] = -1;
                    valid = 1; //update valid 
                } //if row below was not merged and the cells are equal,
                if((k + 1) != merged && cur_game->cells[k * cols + j] == cur_game->cells[(k + 1) * cols + j]){
                    cur_game->cells[(k + 1) * cols + j] = cur_game->cells[k * cols + j] * 2; //merge cells
                    cur_game->cells[k * cols + j] = -1; //empty old cell
                    merged = k + 1; //update merged to row below
                    cur_game->score += cur_game->cells[(k + 1) * cols + j]; //update score, adding value of new cell
                    valid = 1; //update valid
                }
            }
        }
    }
    return valid; //return whether a valid move was made or not
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int i, j, k; //initialize variables
    int cols = cur_game->cols;
    int rows = cur_game->rows;
    int valid = 0; 
    int merged = 0;
    for(i = 0; i < rows; i++){ //iterate through rows
        merged = -1; //initialize for each row
        for(j = 0; j < cols; j++){ //iterate through columns
            if(cur_game->cells[i * cols + j] != -1){ //if the cell isn't empty
                for(k = 0; k < j && cur_game->cells[i * cols + k] != -1; k++){
                } //find a cell that is empty left of current column
                if(k < j){ //if found to left, move current cell into new cell and empty current cell
                    cur_game->cells[i * cols + k] = cur_game->cells[i * cols + j];
                    cur_game->cells[i * cols + j] = -1;
                    valid = 1; //update valid
                } //if col left was not merged and the cells are equal, 
                if((k - 1) != merged && cur_game->cells[i * cols + k] == cur_game->cells[i * cols + (k - 1)]){ 
                    cur_game->cells[i * cols + (k - 1)] = cur_game->cells[i * cols + k] * 2; //merge cells
                    cur_game->cells[i * cols + k] = -1; //empty old cell
                    merged = k - 1; //update merged to col left
                    cur_game->score += cur_game->cells[i * cols + (k - 1)]; //update score, adding value of new cell
                    valid = 1; //update valid
                }
            }
        }
    }
    return valid; //return whether a valid move was made or not
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int i, j, k; //initialize variables
    int cols = cur_game->cols;
    int rows = cur_game->rows;
    int valid = 0; 
    int merged = 0;
    for(i = rows - 1; i >= 0; i--){ //iterate backward through rows
        merged = cols; //initialize for each row
        for(j = cols - 1; j >= 0; j--){ //iterate backward through columns
            if(cur_game->cells[i * cols + j] != -1){ //if the cell isn't empty
                for(k = cols - 1; k > j && cur_game->cells[i * cols + k] != -1; k--){
                } //find a cell that is empty right of current column
                if(k > j){ //if found to right, move current cell into new cell and empty current cell
                    cur_game->cells[i * cols + k] = cur_game->cells[i * cols + j];
                    cur_game->cells[i * cols + j] = -1;
                    valid = 1; //update valid
                } //if col right was not merged and the cells are equal, 
                if((k + 1) != merged && cur_game->cells[i * cols + k] == cur_game->cells[i * cols + (k + 1)]){
                    cur_game->cells[i * cols + (k + 1)] = cur_game->cells[i * cols + k] * 2; //merge cells
                    cur_game->cells[i * cols + k] = -1; //empty old cell
                    merged = k + 1; //update merged to col right
                    cur_game->score += cur_game->cells[i * cols + (k + 1)]; //update score, adding value of new cell
                    valid = 1; //update valid
                }
            }
        }
    }
    return valid; //return whether a valid move was made or not
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int i, j; //initialize variables
    int cols = cur_game->cols;
    int rows = cur_game->rows;
    for(i = 0; i < rows; i++){ //iterate through each row and col
        for(j = 0; j <cols; j++){
            if(cur_game->cells[i * cols + j] == -1){ // if any cells are empty, return 1
                return 1;
            }
        }
    }
    if(move_w(cur_game) || move_a(cur_game) || move_s(cur_game) || move_d(cur_game)){ //if any moves are still valid, return 1
        return 1;
    }
    return 0; //otherwise return 0
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
