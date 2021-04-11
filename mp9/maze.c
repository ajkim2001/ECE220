#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
Alex Kim netid:alexk4 4/11/2021
In this program I had to implement 4 functions to solve mazes.
In createMaze, I had to open the maze file and allocate the appropriate memory to copy it down into my maze struct.
In destroyMaze, I had to free all the memory allocated previously across the entire maze struct.
In printMaze, I had to print each cell I had copied over to my maze struct.
In solveMazeDFS, I had to make use of the DFS algorithm to check base conditions and 
recursively call to check each possible direction and solve the maze.
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */

maze_t * createMaze(char * fileName)
{
    FILE *file = fopen(fileName, "r"); //creates file pointer and opens file

    maze_t *maze = (maze_t *)malloc(sizeof(maze_t)); //creates maze pointer and allocates space
    
    //initialize variables
    int row, col, i, j;
    char k;

    fscanf(file, "%d %d", &row, &col); //reads file to get width and height
    maze->width = col;
    maze->height = row;

    //allocate memory for each row and col
    maze->cells = (char**)malloc(sizeof(char*) * row); 
    for(i = 0; i < row; i++){
        maze->cells[i] = (char*)malloc(sizeof(char) * col);
    }

    //get rid of unnecessary newline
    fscanf(file, "%c", &k);

    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            fscanf(file, "%c", &k); //scan through each cell in the file to put in cells
            maze->cells[i][j] = k; 
            if(maze->cells[i][j] == 'S'){ //if its the start, put in start variables
                maze->startRow = i;
                maze->startColumn = j;
            }
            if(maze->cells[i][j] == 'E'){ //if its the end, put in end variables
                maze->endRow = i;
                maze->endColumn = j;
            }
        }
        fscanf(file, "%c", &k); //get rid of newline at the end of each row
    }
    
    fclose(file); //dont forget to close file
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int i;
    for(i = 0; i < maze->height; i++){ //free cell memory
        free(maze->cells[i]);
    }
    free(maze->cells); //free the entire maze structure
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i;
    int j;
    for(i = 0; i < maze->height; i++){
        for(j = 0; j < maze->width; j++){
            printf("%c", maze->cells[i][j]); //print out each cell
        }
        printf("\n"); //print new line at the end of each row
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if(col < 0 || row < 0 || col >= maze->width || row >= maze->height){
        return 0; //If (col, row) outside bounds of the maze return false
    }
    if (maze->cells[row][col]!='S' && maze->cells[row][col]!='E' && maze->cells[row][col]!= ' '){
        return 0; //if (col, row) is not an empty cell or start/end return false
    }
    if(maze->cells[row][col] == 'E'){
        maze->cells[maze->startRow][maze->startColumn] = 'S';
        return 1; //if (col, row) is the end of the maze return true and restore start
    }

    maze->cells[row][col] = '*'; //set (col, row) as part of the solution path in the maze

    //check all directions to see if any are true
    if(solveMazeDFS(maze, col+1, row)){
        return 1; 
    }
    if(solveMazeDFS(maze, col-1, row)){
        return 1;
    }
    if(solveMazeDFS(maze, col, row+1)){
        return 1;
    }
    if(solveMazeDFS(maze, col, row-1)){
        return 1;
    }
    
    maze->cells[row][col] = '~'; //unmark (col, row) as part of solution and mark as visited

    return 0; //return false
}
