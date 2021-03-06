#include <stdlib.h>
#include <stdio.h>

/* 
Alex Kim netid:alexk4 2/26/2021
1. The error in is_prime was that the return values were swapped in lines 23 & 26.
When a prime number was found, 0 was returned and if not, 1 was returned. 
I have changed it so that they have been swapped to the correct places.
2. The first error in print_semiprimes was in line 44 where 'k=i%j'.
The mod should be a division symbol to find the other prime number that
makes up the semiprime once the first prime number is found. Once the
symbol is changed, k will be checked to find if both factors are prime.
3. I added 'ret = 1' in line 52 to change the return value to 1 once a 
semiprime is found. Otherwise, the function would always return 0 after
it was initialized in line 45.
4. I added 'break' in line 53 to prevent the 'j' for loop from running 
again once the semiprime number is printed. Otherwise, duplicates could
be printed such as for 2*3 and 3*2. With the break, the inner for loop
is exited to find the next semiprime number.
*/

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
                        ret = 1;
                        break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
