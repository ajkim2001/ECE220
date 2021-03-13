/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/* 
Alex Kim netid:alexk4 3/12/2021
In this program I had to implement 3 functions: set_seed, start_game, and make_guess.
For set_seed, I just had to print an error message and return 0 if the if statement came true.
Otherwise, I just called srand and returned 1.
For start_game, I just had to use a for loop to create 4 random numbers that I used to select
the names in a pool randomly. To do this, I used an array and strcpy to copy it to another array.
Then I simply initialized max_score and guess_number.
Finally, I had to write make_guess. This function required me to use sscanf to move names from 
the guess string the user inputted to my own arrays where I could check if the guesses were valid
and how they compared to the solutions. The comparison was done using for loops that made use of
strcmp to check through each element. I then either output and error message with return 0 or
output the user's score and result of the guess until all 10 guesses were used or it was guessed
perfectly correct.
*/

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    int seed;
    char post[2];
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
      // your code here
      printf("set_seed: invalid seed\n"); /* prints error message and returns 0 if sscanf does not find 1 integer */
      return 0;
    }
    // your code here
    else { /* if 1 integer was found, call srand with it and return 1 */
    srand(seed);
    return 1;
    }
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    // your code here
    int i;
    for (i = 0; i < 4; i++){ 
        int random = rand() % 8; /* Use rand and % 8 to find a random position in pool */
        strcpy (solutions[i], pool[random]); /* Use the variable in the for loop and strcpy to copy the randomly chose name to solutions */
    }
    max_score = -1; /* initialize variables */
    guess_number = 1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
  // your code here
  int current; /* current score */
  int perfect_match = 0; /* how many perfect matches found */
  int misplaced_match = 0; /* how many misplaced matches found */
  char guess1[10], guess2[10], guess3[10], guess4[10]; /* guesses from guess_str copied over in sscanf */
  char extra[1]; /* extra in guess_str */
  int guess_match[4] = {0, 0, 0, 0,}; /* which guesses were matched */
  int solution_match[4] = {0, 0, 0, 0,}; /* which solutions were matched */
  int ret_val; /* return value of sscanf */

  ret_val = sscanf(guess_str, "%s%s%s%s%1s", guess1,guess2,guess3,guess4,extra); /* Use sscanf to read data and store from guess_str to my arrays */
  if (ret_val == 4) /* keep running if sscanf found exactly 4 items */
  {
    char* guesses[4] = {guess1, guess2, guess3, guess4}; /* array of guesses */
    for (int a = 0; a < 4; a++) 
    {
        if (is_valid(guesses[a]) == 0) /* checks if each guess is a valid guess, if not prints error and returns 0 */
        {
            printf("make_guess: invalid guess\n");
            return 0;
        }
    }
    for (int b = 0; b < 4; b++) /* compares guesses to solutions to see if there is a perfect match in any of the same spots */
    {
        if (strcmp(guesses[b], solutions[b]) == 0)
        {
            solution_match[b] = 1;
            guess_match[b] = 1;
            perfect_match ++;
        }
    }
    for (int c = 0; c < 4; c++)
    {
        if (guess_match[c] == 1) /* checks if the guess was already matched */
        {
            continue;
        }
        for (int d = 0; d < 4; d++) 
        {
            if (solution_match[d] == 1) /* checks if the solution was already matched */
            {
                continue;
            }
            if (strcmp(guesses[c], solutions[d]) == 0) /* compares guesses to solutions to see if there is any misplaced matches in different spots */
            {
                solution_match[d] = 1;
                guess_match[c] = 1;
                misplaced_match ++;  
            }
        }
    }
    current  = (perfect_match*1000) + (misplaced_match*100); /* calculated current score using number of perfect and misplaced matches */
    if (current > max_score){ /* If the current score is larger than the max score, replace max score with current */
        max_score = current;
    }
    if (perfect_match == 4){ /* If 4 perfect matches have been found, return 2 */
        return 2;
    }
    else { /* Otherwise print out the current data of matches and score and increment the number of guesses made and return 1 */
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_match, misplaced_match);
    printf("Your score is %d and cur max score is %d.\n", current, max_score);
    guess_number++;
    return 1;
    }
  }
  else { /* If 4 items not found, print an error and return 0 */
    printf("make_guess: invalid guess\n");
    return 0;
  
  }
}


