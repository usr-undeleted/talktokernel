#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include "words.h"
#include "flagutils.h"
#include "words.h"

#define uint unsigned int

int main (int argc, char* argv[]) {
	int num = 0; /* arg 1*/
	const uint len1 = sizeof(words) / sizeof(words[0]);
	const uint len2 = sizeof(marks) / sizeof(marks[0]);
	const uint len3 = sizeof(basic) / sizeof(basic[0]);

	uint r1 = 0; /* random value for words */
	uint r2 = 0; /* random value for marks */
	uint r3 = 0; /* random value for basics */

	int seed = 0; /* seed edited in for loop */
	uint buf = 0; /* buffer for getrandom(), maybe use memory allocation for that sometime? */

	if (argc != 2) {
		printf("Error! Did you type a number greater than 0 (if you typed an arg...)?\n");
		return 1;
	}

	num = atoi(argv[1]); /* only sets it now to prevent checking argv[1] even if it doesnt exist */

	if (num <= 0) { /* check to see if inputted number is valid */
		printf("Error! Input is invalid or less than 1.\n");
		return 2;
	}

	for (int i = 0; i < num; i++) {
		buf = getrandom(&seed, sizeof(seed), 0);
		srand(seed);
		r1 = rand() % len1; /* words */
		r2 = rand() % len2; /* marks */
		r3 = rand() % len3; /* basics */

		printf(" %s %s", words[r1], basic[r3]); /* word printing */

		if (rand() % 5 == 0) { /* mark printing */
			printf("%s ", marks[r2]);
		}
	}
	printf("\n--Wise words from the linux kernel...\n");
	return 0;
}
