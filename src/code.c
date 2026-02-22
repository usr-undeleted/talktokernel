#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include "words.h"
#include "words.h"
#include "utils.h"

#define uint unsigned int
#define clear printf("\033c")

void noflag(int num); /* flagless */
int fhelp(int argc); /* -h and --help */

uint len1, len2, len3; /* arr length for words, marks and basics */
uint r1, r2, r3; /* random value for words, marks and basics */
int seed = 0; /* seed edited in for loop */


int main (int argc, char* argv[]) {
	int num = 0; /* arg 1*/
	int (*flagfuncs[])(int) = {fhelp,fhelp}; /* array that contain pointers to functions for flag stuff
	note that the first two are fhelp since theres both --help and -h
	make sure the funcs here match the flags in utils.h */
	int flagVal = flagchk(argc,argv); /* get flag value */

	if (argc < 2) {
		printf("Bad usage! See -h or --help for help.\n(ERR: not enough args)\n");
		return 1;
	}
	num = atoi(argv[1]); /* only set if argv[1] exists - get num from argv[1]*/

	if (flagVal != -1) { /* always place flag check b4 flagless check */
		(*flagfuncs[flagVal])(argc);
		return 0;
	}

	if (flagVal == -1 && num < 1) { /* incase first check fails, send an error message */
		printf("Bad usage! See -h or --help for help.\n(ERR: second arg isn't valid)\n");
		return 2;
	}

	/* stuff that prints */
	noflag(num); /* start default func */
	(*flagfuncs[0])(argc);
	return 0;
};

void noflag(int num) {
	len1 = sizeof(words) / sizeof(words[0]);
	len2 = sizeof(marks) / sizeof(marks[0]);
	len3 = sizeof(basic) / sizeof(basic[0]);
	int buf = 0;

	clear; /* clear terminal, check macros for context */
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
	printKernelAuthor();
	system("date +%d.%m.%y");
};

int fhelp(int argc) { /* help func, currently uses argc just for testing purposes, but it might need to take in argv since other funcs will need to take it */
	printf("This is a help message!\n");
}
