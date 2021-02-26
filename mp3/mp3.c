/* 
Alex Kim netid:alexk4 2/26/2021
This program will print out a row in Pascal's triangle depending on user input.
It makes use of a loop to print out each value so that the number of values in a row
are row + 1. The loop first checks to see if it is the first value to print 1. 
Otherwise, the loop will use a given equation to calculate binomial coefficients.
The loop is completed when all coefficients are printed, a new line is printed 
(for style), and the program returns.  
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  int i; /* Initializes i to be used in the equation and loop */
  unsigned long coef = 1; /* Initializes coef to 1 to be used in the equation as last result */
  for (i = 0; i <= row; i++) { /* This loop iterates to print each number in the line */
    if (i == 0 || row == 0) /* 1 should be printed if in the first value */
      coef = 1; 
    else 
      coef = coef * (row - i + 1) / i; /* Uses the equation to calculate the binomial coefficient */
    printf("%lu ", coef); /* Prints the result of the equation */
    }
  printf("\n"); /* Prints a new line after to look nice */
  return 0; /* Ends code */
}
