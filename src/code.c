#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <signal.h>

#include "words.h"
#include "utils.h"

#define uint unsigned int
#define clear printf("\033c")

/* note that all flag functions must have int num, its a dumb short-coimng of an array of pointers to funcs */
void noflag(int num); /* flagless */
void fhelp(int num); /* -h and --help */
void frandom(int num); /* -r flag */

uint len1, len2, len3; /* arr length for words, marks and basics */
uint r1, r2, r3; /* random value for words, marks and basics */
int seed = 0; /* seed edited in for loop */
int markc; /* used to type a mark at the end everytime */
int buf = 0;

/* int main cus i keep forgetting where it is */
int main (int argc, char* argv[]) {
	int num = 0; /* arg 1*/
	void (*flagfuncs[])(int) = {fhelp,fhelp,frandom}; /* array that contain pointers to functions for flag stuff
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
		printf("Bad usage! See -h or --help for help.\n(ERR: invalid secondary arg)\n flagVal = %d\n", flagVal);
		return 2;
	}

	/* stuff that prints */
	if (argc == 2) {
		noflag(num); /* start default func */
	} else {
		printf("Bad usage! See -h or --help for help.\n(ERR: too many args!)\n");
		return 3;
	}
	return 0;
};

void noflag(int num) {
	len1 = sizeof(words) / sizeof(words[0]);
	len2 = sizeof(marks) / sizeof(marks[0]);
	len3 = sizeof(basic) / sizeof(basic[0]);

	clear; /* clear terminal, check macros for context */
	for (int i = 0; i < num; i++) {
		markc = 0;
		buf = getrandom(&seed, sizeof(seed), 0);
		srand(seed);
		r1 = rand() % len1; /* words */
		r2 = rand() % len2; /* marks */
		r3 = rand() % len3; /* basics */

		printf(" %s %s", words[r1], basic[r3]); /* word printing */

		if (rand() % 5 == 0) { /* mark printing */
			printf("%s ", marks[r2]);
			markc = 1;
		}
		if (rand() % 10 == 0) { /* new line */
			if (markc == 0) printf("%s\n ", marks[r2]);
		}
	}
	buf = getrandom(&seed, sizeof(seed), 0);
	srand(seed);
	if (markc == 0) printf("%s", marks[r2]);
	/*^ prints a mark incase the end doesnt have one*/

	printKernelAuthor();
	system("date +%d.%m.%y");
};

void fhelp(int argc) { /* help func, currently uses argc just for testing purposes, but it might need to take in argv since other funcs will need to take it */
	printf("Thank you for using talktokernel! Usage:\n	<command> <flag> <flaginput>\n By just using <command> <number>, you will use the flagless function and print as usual, using the number in the second argument.\n	-h or --help: Displays this help menu.\n	-r (random): prints nonstop.\n");
	exit(1);
}

void frandom(int num) {
	int markc; /* used to type a mark at the end everytime */

	len1 = sizeof(words) / sizeof(words[0]);
	len2 = sizeof(marks) / sizeof(marks[0]);
	len3 = sizeof(basic) / sizeof(basic[0]);

	clear; /* clear terminal, check macros for context */
	while (true) {
		markc = 0;
		buf = getrandom(&seed, sizeof(seed), 0);
		srand(seed);
		r1 = rand() % len1; /* words */
		r2 = rand() % len2; /* marks */
		r3 = rand() % len3; /* basics */

		printf(" %s %s", words[r1], basic[r3]); /* word printing */

		if (rand() % 5 == 0) { /* mark printing */
			printf("%s ", marks[r2]);
			markc = 1;
		}
		if (rand() % 10 == 0) { /* new line */
			if (markc == 0) printf("%s\n ", marks[r2]);
		}
	}
}
