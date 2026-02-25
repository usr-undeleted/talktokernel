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
void finfinite(int num); /* -i flag */

uint lenwords, lenmarks, lenbasic; /* arr length for words, marks and basics */
uint ranwords, ranmarks, ranbasics; /* random value for words, marks and basics */
int seed = 0; /* seed edited in for loop */
int markc; /* used to type a mark at the end everytime */

int main (int argc, char* argv[]) {
	int num = 0; /* arg 1*/
	void (*flagfuncs[])(int) = {fhelp,fhelp,finfinite}; /* funcs match flags in utils.h */
	int arr[argc]; /* previous flagVal */
	mapflags(argc,argv,arr);

	if (argc < 2) {
		printf("Bad usage! See -h or --help for help.\n(ERR: not enough args)\n");
		return 1;
	}
	num = atoi(argv[1]); /* only set if argv[1] exists - get num from argv[1]*/

	if (arr[1] != -1) { /* always place flag check b4 flagless check */
		(*flagfuncs[arr[1]])(argc);
		return 0;
	}

	if (arr[1] == -1 && num < 1) { /* incase first check fails, send an error message */
		printf("Bad usage! See -h or --help for help.\n(ERR: invalid secondary arg)\n arr[1] = %d\n", arr[1]);
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
	lenwords = sizeof(words) / sizeof(words[0]);
	lenmarks = sizeof(marks) / sizeof(marks[0]);
	lenbasic = sizeof(basic) / sizeof(basic[0]);

	clear; /* clear terminal, check macros for context */
	for (int i = 0; i < num; i++) {
		markc = 0;
		getrandom(&seed, sizeof(seed), 0);
		srand(seed);
		ranwords = rand() % lenwords; /* words */
		ranmarks = rand() % lenmarks; /* marks */
		ranbasics = rand() % lenbasic; /* basics */

		printf(" %s %s", words[ranwords], basic[ranbasics]); /* word printing */

		if (rand() % 5 == 0) { /* mark printing */
			printf("%s ", marks[ranmarks]);
			markc = 1;
		}
		if (rand() % 10 == 0) { /* new line */
			if (markc == 0) printf("%s\n ", marks[ranmarks]);
		}
	}
	getrandom(&seed, sizeof(seed), 0);
	srand(seed);
	if (markc == 0) printf("%s", marks[ranmarks]);
	/*^ prints a mark incase the end doesnt have one*/

	printKernelAuthor();
	system("date +%d.%m.%y");
};

void fhelp(int argc) {
	fputs("Thank you for using talktokernel! Usage:\n"
	"    <command> <flag>\n"
	"\n"
	"By just using <command> <number>, you will use the flagless function and print\n"
	"as usual, using the number in the second argument.\n"
	"\n"
	"    -h or --help: Displays this help menu.\n"
	"    -i (infinite): prints nonstop. Takes in no arguments. \n", stderr);
	exit(1);
}

void finfinite(int num) {
	int markc; /* used to type a mark at the end everytime */

	lenwords = sizeof(words) / sizeof(words[0]);
	lenmarks = sizeof(marks) / sizeof(marks[0]);
	lenbasic = sizeof(basic) / sizeof(basic[0]);

	clear; /* clear terminal, check macros for context */
	while (1) {
		markc = 0;
		getrandom(&seed, sizeof(seed), 0);
		srand(seed);
		ranwords = rand() % lenwords; /* words */
		ranmarks = rand() % lenmarks; /* marks */
		ranbasics = rand() % lenbasic; /* basics */

		printf(" %s %s", words[ranwords], basic[ranbasics]); /* word printing */

		if (rand() % 5 == 0) { /* mark printing */
			printf("%s ", marks[ranmarks]);
			markc = 1;
		}
		if (rand() % 10 == 0) { /* new line */
			if (markc == 0) printf("%s\n ", marks[ranmarks]);
		}
	}
}

/* currently code only checks argv[1], but implementation is less complicated by using the tools in utils.h */
