// -------NOTES AND OBJECTIVES-------
// 1. all flag funcs have to take in *some* int due to limitations of an array of pointers to funcs
// 2. current code only checks argv[1] for a flag
// 3. put all funcs that need to proccess data in utils.h, words in words.h, and flag functions here
// ***4. WORK ON -F FLAG:
// implement picking wether output is infinite or not (check if -i is somewhere)***
// have one of the args be the number of words outputted

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/random.h>
#include <sys/utsname.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "words.h"
#include "utils.h"

typedef unsigned int uint;
#define CLEAR() printf("\033c")

void noflag(int num); /* flagless */
void fhelp(int num); /* -h and --help */
void fsaywords(int num); /* -i flag */
void fprintfile(int argc); /* -f flag  */

void procdata(char *data); /* make data (-f flag) global */

uint lenwords, lenmarks, lenbasic; /* arr length for words, marks and basics */
uint rwords, rmarks, rbasic, rcustom; /* random value for words, marks, basics and custom words */
int seed = 0; /* seed edited in for loop */
int markc; /* used to type a mark at the end everytime */
int usewords = 1; /* used to correctly print words */
int fileflag; /* to pick beetwen -f or flagless  */

char argv2[256]; /* global third arg */
char argv3[256]; /* global fourth arg */
char *data[8192] = { 0 }; /* global custom word data */
int garc; /* global argc */

int shouldstop = 0; /* the loop should stop */
int fileflag = 0; /* determines what words to print (from words.h or custom file) */

/* objective: check for validity when calling the command */
int main (int argc, char* argv[]) {
	fileflag = 0;
	int num = 0; /* arg 1*/
	void (*flagfuncs[])(int) = {fhelp,fhelp,fsaywords,fprintfile}; /* funcs match flags in utils.h */
	int arr[argc]; /* previous flagVal */
	mapflags(argc,argv,arr);

	/* make global values */
	garc = argc;
	if (argc >= 3) {
		for (int i = 0; i < strlen(argv[2]); i++) {
			argv2[i] = argv[2][i];
		}
	}
	if (argc >= 4) {
		for (int i = 0; i < strlen(argv[3]); i++) {
			argv3[i] = argv[3][i];
		}
	}

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
			if (!fileflag) {
				printf(" %s",words[rwords]);
			} else {
				printf(" %s",data[rcustom]);
			}
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

void fhelp(int argc) { /* has to take in *some* int */
	fputs("Thank you for using talktokernel! Usage:\n"
	"	<command> <flag> <flaginput>\n"
	"\n"
	"By just using <command> <number>, you will use the flagless function and print\n"
	"as usual, using the number in the second argument.\n"
	"\n"
	"	-h or --help: Displays this help menu.\n"
	"	-i (infinite): prints nonstop. Takes in no arguments. \n"
	"	-f (read from file) takes words from file and replaces the printable words with the ones in the file.\n", stderr);
	exit(0);
}

void fprintfile(int argc) {
	/* get file, separate its words onto strings, and plop them onto an array (data) */
	if (argc < 3) {
		fputs("Too little arguments! See -h or --help for help.\n",stderr);
		exit(1);
	}
	FILE *fd = fopen(argv2, "r'");

	if (fd == NULL) {
		fputs("Error! File couldn't be opened. Does the file exist or you have the proper permissions?\n", stderr);
		exit(1);
	}
	char data[8192];

	rewind(fd); /* set pointer back before getting data */
	while (fgets(data, sizeof(data) / sizeof(char), fd)) {
		/* get data from file and put it onto data */
	}
	char *ptr = strtok(data, " "); /* separate words */

	while (ptr != NULL) {
		// do stuff b4 strtok
		ptr = strtok(NULL, " ");
	}
	procdata(data);
	fclose(fd);
	fileflag = 1;
	shouldstop = 1;
	fsaywords(garc);
	exit(0);
}

void procdata (char *indata) {
	*data = indata;
}
