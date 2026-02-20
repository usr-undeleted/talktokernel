#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/random.h>

#include "words.h"

/*add support for making sure getrandom works always with ssize_t or something*/

int main (int const argc, char** argv)
{
    /* Tip. Explain what the arguments do in the error messages */
    if(argc != 2)
    {
        printf("Error! Did you type a number greater than 0 (if you typed an arg...)?\n");
        return 1;
    }

    int const num = atoi(argv[1]);
    if(num < 1)
    {
        printf("Error! Input is invalid or less than 1.\n");
        return 1;

    }

    unsigned int const len1 = sizeof(words) / sizeof(words[0]);
    unsigned int const len2 = sizeof(marks) / sizeof(marks[0]);
    unsigned int const len3 = sizeof(basic) / sizeof(basic[0]);

    /* Tip. Make the names elaborate enough where you aren't required to explain via comments */
    int r1 = 0; /* random value for words */
    int r2 = 0; /* random value for marks */
    int r3 = 0; /* random value for basics */

    int seed = 0; /* seed edited in for loop */
    int buf = 0; /* buffer for getrandom(), maybe use memory allocation for that sometime? */



    for (int i = 0; i < num; i++)
    {
        buf = getrandom(&seed, sizeof(seed), 0);
        srand(seed);
        r1 = rand() % len1; /* words */
        r2 = rand() % len2; /* marks */
        r3 = rand() % len3; /* basics */

        printf(" %s %s", words[r1], basic[r3]); /* word printing */

        if(rand() % 5 == 0)
        {
            printf("%s ", marks[r2]);
        }
    }
    printf("\n--Wise words from the linux kernel...\n");

    return 0;
}
