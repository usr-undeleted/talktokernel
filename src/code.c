#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/random.h>
#include <sys/utsname.h>
#include <signal.h>
#include <time.h>

#include "words.h"
#include "utils.h"

typedef unsigned int uint;
#define CLEAR() printf("\033c")

/* note that all flag functions must have int num, its a dumb short-coimng of an array of pointers to funcs */
void noflag(int num); /* flagless */
void fhelp(int num); /* -h and --help */
void fsaywords(int num); /* -i flag */

uint lenwords, lenmarks, lenbasic; /* arr length for words, marks and basics */
uint rwords, rmarks, rbasic; /* random value for words, marks and basics */
int seed = 0; /* seed edited in for loop */
int markc; /* used to type a mark at the end everytime */
int usewords = 1; /* used to correctly print words */

int shouldstop = 0; /* the loop should stop */

int main (int argc, char* argv[]) {
	int num = 0; /* arg 1*/
	void (*flagfuncs[])(int) = {fhelp,fhelp,fsaywords}; /* funcs match flags in utils.h */
	int arr[argc]; /* previous flagVal */
	mapflags(argc,argv,arr);

	if (argc < 2) {
		fputs("Not enough arguments! See -h or --help for help.\n", stderr);
		return 1;
	}
	num = atoi(argv[1]); /* only set if argv[1] exists - get num from argv[1]*/

	if (arr[1] != -1) { /* always place flag check b4 flagless check */
		(*flagfuncs[arr[1]])(argc);
		return 0;
	}

	if (arr[1] == -1 && num < 1) { /* incase first check fails, send an error message */
		fprintf(stderr, "Secondary argument isn't valid! See -h or --help for help.\n");
		return 2;
	}

	/* stuff that prints */
	if (argc == 2) {
		noflag(num); /* start default func */
	} else {
		fputs("Too many arguments! See -h or --help for help.\n", stderr);
		return 3;
	}
	return 0;
};

void fsaywords(int num) {
	CLEAR(); /* clear terminal, check macros for context */

	int i = 0;
	int markc; /* used to type a mark at the end everytime */

	lenwords = sizeof(words) / sizeof(words[0]);
	lenmarks = sizeof(marks) / sizeof(marks[0]);
	lenbasic = sizeof(basic) / sizeof(basic[0]);

	while (1) {
		if (shouldstop) {
			i++;
			if (i >	num) break;
		}

		markc = 0;
		getrandom(&seed, sizeof(seed), 0);
		srand(seed);
		rwords = rand() / 2 % lenwords;
		rmarks = rand() % lenmarks;
		rbasic = rand()  / 2 % lenbasic;

		/* print words */
		if (usewords) {
			usewords = 0;
			printf(" %s",words[rwords]);
		} else {
			usewords = 1;
			printf(" %s",basic[rbasic]);
		}

		if (rand() % 5 == 0) { /* mark printing */
			printf("%s",marks[rmarks]);
			markc = 1;
		}
		if (rand() % 10 == 0) { /* new line */
			if (markc == 0) printf("%s\n",marks[rmarks]);
		}
	}

	getrandom(&seed, sizeof(seed), 0);
	srand(seed);

	if (markc == 0) fputs(marks[rmarks], stdout);

	printkernel();
	printdate("%d.%m.%y");
}

void noflag(int num) {
	shouldstop = 1;
	fsaywords(num);
};

void fhelp(int argc) { /* help func, currently uses argc just for testing purposes, but it might need to take in argv since other funcs will need to take it */
	fputs("Thank you for using talktokernel! Usage:\n"
	"	<command> <flag> <flaginput>\n"
	"\n"
	"By just using <command> <number>, you will use the flagless function and print\n"
	"as usual, using the number in the second argument.\n"
	"\n"
	"	-h or --help: Displays this help menu.\n"
	"	-i (infinite): prints nonstop. Takes in no arguments. \n", stderr);
	exit(1);
}



/* currently code only checks argv[1], but implementation is less complicated by using the tools in utils.h */
