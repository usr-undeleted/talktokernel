#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/random.h>
#include "words.h"

/*add support for making sure getrandom works always with ssize_t or something*/

int main (int argc, char* argv[]) {
	int num = 0; /* arg 1 */
	unsigned int len1 = sizeof(words) / sizeof(words[0]);
	unsigned int len2 = sizeof(marks) / sizeof(marks[0]);
	unsigned int len3 = sizeof(basic) / sizeof(basic[0]);

	int r1 = 0; /* random value for words */
	int r2 = 0; /* random value for marks */
	int r3 = 0;

	int seed = 0; /* seed edited in for loop */
	int buf = 0; /* buffer for getrandom(), maybe use memory allocation for that sometime? */

	if (argc == 2) { /* check to see if there are enough args */
		num = atoi(argv[1]); /* only sets it now to prevent checking argv[1] even if it doesnt exist */

		if (num >= 1) { /* check to see if inputted number is valid */
			for (int i = 0; i < num; i++) {
				buf = getrandom(&seed, sizeof(seed), 0);
				srand(seed);
				r1 = rand() % len1; /* words */
				r2 = rand() % len2; /* marks */
				r3 = rand() % len3; /* basics */

				printf(" %s %s", words[r1], basic[r3]); /* word printing */

				if ((int)rand() % 5 == 0) { /* mark printing */
					printf("%s ", marks[r2]);
				} else {
					// crickets
				}
			}
			printf("\n");
			return 0;
		} else {
			printf("Error! Input is invalid or less than 1.\n");
			return 2;
		}
	} else {
		printf("Error! Did you type just a number for the second arg (if you typed an arg...)?\n");
		return 1;
	}
}
