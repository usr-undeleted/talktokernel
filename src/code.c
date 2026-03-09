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
void fcolor(int num); /* -c flag */

uint lenwords, lenmarks, lenbasic; /* arr length for words, marks and basics */
uint rwords, rmarks, rbasic, rcustom; /* random value for words, marks, basics and custom words */
int seed = 0; /* seed edited in for loop */
int markc; /* used to type a mark at the end everytime */

int usewords = 1; /* used to correctly print words */
int shouldstop = 0; /* the loop should stop */
int fileflag = 0; /* determines what words to print (from words.h or custom file) */

char cus[10000][30]; /* file words */
int cuslen; /* len of cus */
FILE *fd; /* custom file */

int globargc; /* global argc */
int rclr; /* decides random colors */

/* ansi colors for normal text colors, bg colors, and resetting the color */
/* intentionally only edited later */
char *colors[] = {
	"", // \033[30m
	"", // \033[31m
	"", // \033[32m
	"", // \033[33m
	"", // \033[34m
	"", // \033[35m
	"", // \033[36m
	"", // \033[37m
	"", // \033[30m
	/* keep the last repeated entry */
};

char *bgs[] = {
	"", // \033[40m
	"", // \033[41m
	"", // \033[42m
	"", // \033[43m
	"", // \033[44m
	"", // \033[45m
	"", // \033[46m
	"", // \033[47m
	"", // \033[40m
	/* keep the last repeated entry */
};


char *reset = "\033[0m";

int arr[10]; /* contains the vals for the flags */

/* objective: check for validity when calling the command */
int main (int argc, char* argv[]) {
	int num = 0; /* arg 1*/
	globargc = argc;
	void (*flagfuncs[])(int) = {fhelp,fhelp,fsaywords,fprintfile,fcolor}; /* funcs match flags in utils.h */
	mapflags(argc,argv,arr);

	fd = fopen(argv[2], "r");

	if (argc < 2) {
		fputs("Not enough arguments! See -h or --help for help.\n", stderr);
		return 1;
	}

	int infexists = 0; /* use this for loop to also check if -i exists */
	int clrexists = 0; /* check if -c exists */

	for (int i = 0; i < argc; i++) {
		if (arr[i] == 2) {
			infexists = 1;
		}
		if (arr[i] == 4) {
			clrexists = 1;
		}
	}

	/* get the value of num by checking the next num after a flag like -c */
	if (argc > 2) {
		for (int i = 0; i < argc; i++) {
			num = atoi(argv[1]);


			if (arr[i] != -1) {
				num = atoi(argv[i + 1]);
				break;
			}
		}
	} else {
		num = atoi(argv[1]);
	}

	for (int i = 0; i < argc; i++) {
		if (arr[i] == 0 || arr[i] == 1) {
			fhelp(argc);
			return 0;
		}
	}

	/* i am so, so sorry */
	if (num < 1 && infexists == 0 && clrexists == 0) {
		fprintf(stderr, "Number is not valid! See -h or --help for help.\n");
		return 6;
	}

	/* if the flag is -f, set num appropriately */
	if (!strcmp(argv[1], "-f") && argc >= 4) {
		fileflag = 1;
		num = atoi(argv[3]);
		if (strcmp(argv[3], "-i")) {
			shouldstop = 1;
		}
	}

	if (arr[1] != -1) { /* always place flag check b4 flagless check */
		(*flagfuncs[arr[1]])(num);
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
	/* cuslen is edited b4 this */

	if (shouldstop == 0) {
		num = -1;
	}

	for (int j = 0; j != num; j++) {
		markc = 0;
		getrandom(&seed, sizeof(seed), 0);
		srand(seed);
		rwords = rand() / 2 % lenwords;
		rmarks = rand() % lenmarks;
		rbasic = rand()  / 2 % lenbasic;
		rclr = rand() % 9;

		if (fileflag == 1) {
			rcustom = rand()  / 2 % cuslen;
		}

		/* print words */
		if (usewords) {
			usewords = 0;
			if (fileflag == 1) {
				printf(" %s%s%s", colors[rclr], cus[rcustom], reset);
			} else {
				printf(" %s%s%s", colors[rclr], words[rwords], reset);
			}
		} else {
			usewords = 1;
			printf(" %s%s%s", colors[rclr], basic[rbasic], reset);
		}

		if (rand() % 5 == 0) { /* mark printing */
			printf("%s",marks[rmarks]);
			markc = 1;
		}
		if (rand() % 14 == 0) { /* new line */
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
	"	-f (read from file) takes words from file and replaces the printable words with the ones in the file.\n"
	"	Usage: ./binary -f <file> <num>\n"
	"		Num can be either -i for infinite, or any number you desire.\n"
	"	-c (color) EPILEPSY WARNING!!! Prints words/cells with color\n"
	"	Usage: ./binary -c <num>\n"
	"		Num can either be a valid num or -i, and if unset, colors cells for a trippy AND EPILEPSY-INDUCING EFFECT!!! BE AWARE!! I AM GONNA WARN YOU MULITPLE TIMES!! I AM NOT RESPONSIBLE FOR ANY EPILEPSY ATTACKS THE USER MIGHT HAVE!!\n", stderr);
	exit(0);
}

void fprintfile(int num) {
	/* get file, separate its words onto strings, and plop them onto an array (data) */

	if (fd == NULL) {
		fputs("Error! File couldn't be opened. Does the file exist or you have the proper permissions?\n", stderr);
		exit(1);
	}

	if (globargc < 4) {
		fputs("Too little args! See -h or --help for help.\n", stderr);
		exit(4);
	}

	int i = 0;
	while (fscanf(fd, "%s", cus[i]) == 1 && i < 100) {
		i++;
	}
	cuslen = i;

	fsaywords(num);

	fclose(fd);
}

void fcolor (int num) {
	/* if succesful, set the ansi color values to their appropriate thing so that
	when the main func prints, it wont just print nothing when it tries to print
	the color codes. */
	colors[0] = "\033[30m";
	colors[1] = "\033[31m";
	colors[2] = "\033[32m";
	colors[3] = "\033[33m";
	colors[4] = "\033[34m";
	colors[5] = "\033[35m";
	colors[6] = "\033[36m";
	colors[7] = "\033[37m";
	colors[8] = "\033[30m";

	bgs[0] = "\033[40m";
	bgs[1] = "\033[41m";
	bgs[2] = "\033[42m";
	bgs[3] = "\033[43m";
	bgs[4] = "\033[44m";
	bgs[5] = "\033[45m";
	bgs[6] = "\033[46m";
	bgs[7] = "\033[47m";
	bgs[8] = "\033[40m";

	if (globargc == 2) {
		while (1) {
			getrandom(&seed, sizeof(seed), 0);
			srand(seed);
			rclr = rand() % 9;
			printf("%s%s%d%s", colors[rclr], bgs[rclr], rclr, reset);
		}
	}

	if (globargc < 3) {
		printf("Too little args! See -h or --help for help.\n");
		exit(4);
	}

	if (arr[2] == 2) { // if -i
		shouldstop = 0;
	} else if (arr[2] == -1) { // if just regular num
		shouldstop = 1;
	} else {
		printf("Incorrect usage! See -h or --help for help.\n");
		exit(5);
	}

	fsaywords(num);
}
