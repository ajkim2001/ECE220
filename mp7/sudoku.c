#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

/* 
Alex Kim netid:alexk4 3/23/2021
In this program I had to implement 5 functions: is_val_in_row, is_val_in_col,
is_val_in_3x3_zone, is_val_valid, and solve_sudoku.
For is_val_in_row and is_val_in_col, I iterated through each square in the line to check
for val and returned appropriately. The same was done for is_val_in_3x3_zone, but
I also had to use C division to round the row and column number to 0, 3, or 6
so I could increment through the 3x3 from 0 to 3 in the square. 
For is_val_valid, I put all the previous functions into an if statment to see if one of
them was true to return 0 or if all were false to return 1.
For solve_sudoku I had to first check in the base case if there were any unfilled cells.
I used a flag to break out of the loop if there was an unfilled cell at (i,j), 
which I would then fill by incrementing 1-9 and checking each number in the 
recursive case where I called solve_sudoku. I did this until the base case was fulfilled
and no cell was empty.
*/

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int col =  0; col < 9; col++){ //increments through each column in the row
    if(sudoku[i][col] == val) //checks to see if in each spot, val already exists
      return 1; //if it does already exist, return 1
  }
  return 0; //if nothing is found, return 0
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int row =  0; row < 9; row++){ //increments through each row in the column
    if(sudoku[row][j] == val) //checks to see if in each spot, val already exists
      return 1; //if it does already exist, return 1
  }
  return 0; //if nothing is found, return 0
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  assert(j>=0 && j<9);
  //division in C rounds down to 0
  int row = (i / 3) * 3; //Rounds down the row number to 0, 3, or 6
  int col = (j / 3) * 3; //Rounds down the col number to 0, 3, or 6
  
  for(int k = row; k <= row + 2; k++){ //increments through each square in 3x3
    for(int l = col; l <= col + 2; l++){
      if(sudoku[k][l] == val){ //if that square already has val, return 1
	return 1;
      }
    }
  }
  return 0; // if not, return 0
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku)){ //combines all the past checks of row, column, and 3x3 into 1
    return 0; //if any of them are true, return 0
  }
  return 1; //if all of them are false, return 1
  // END TODO
}


// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int emptyCell = 0; //flag that checks for an empty cell
  int i, j;
  for(i = 0; (i < 9) && (emptyCell == 0); i++){ //increments through each row and checks for flag
    for(j = 0; (j < 9) && (emptyCell == 0); j++){ //increments through each column and checks for flag
      if(sudoku[i][j] == 0){ //if an empty cell is found, update flag and break out of loop
	  emptyCell = 1;
	  break;
	}
      }
    if(emptyCell == 1){ //if empty cell is found break out of loop
      break;
    }
    }
  if(emptyCell == 0){ //if empty cell isn't found, return 1
    return 1;
  }
  
  for(int k = 1; k <= 9; k++){ //checks for each value that can be used 1-9
    if(is_val_valid(k, i, j, sudoku)){ //calls is_val_valid to check if val is valid
      sudoku[i][j] = k; //if valid, put in square
      if(solve_sudoku(sudoku)){ //recursive call for solve_sudoku and return 1 if true
	return 1;
      }
      sudoku[i][j] = 0; //if it didn't work, change square to 0 to go through again
    }
  }
  return 0; //return 0
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





