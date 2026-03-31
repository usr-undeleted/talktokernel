// -------NOTES AND OBJECTIVES-------
// 1. put all funcs that need to proccess data in utils.h, words in words.h, and flag functions here

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
void fhelp(); /* -h and --help */
void fsaywords(int num); /* -i flag */
void fprintfile(int num, int argc, char*argv[]); /* -f flag  */
void fcolor(int num, int argc, char *argv[]); /* -c flag */

uint lenwords, lenmarks, lenbasic; /* arr length for words, marks and basics */
int cuslen; /* len of cus */
uint rwords, rmarks, rbasic, rcustom, rclr; /* random value for words, marks, basics and custom words */
int seed = 0; /* seed edited in for loop */

/* replace with single uint8_t and use bitwise stuff to read */
uint markc; /* used to type a mark at the end everytime */
uint usewords = 1; /* used to correctly print words */
uint fileflag = 0; /* determines what words to print (from words.h or custom file) */
uint infexists = 0; /* check if -i exists */
uint clrexists = 0; /* check if -c exists */
uint changenum = 1; /* if num should be changed in the func */

char cus[10000][30]; /* file words */
FILE *fd; /* custom file */

/* funcs match flags in utils.h */
enum flags {
	HELP,
	H,
	I,
	F,
	C
};

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
int firstflag; /* first flag, aka the one that does stuff */
int indexflag = -1; /* index of arr[n] for firstflag */

/* objective: check for validity when calling the command */
int main (int argc, char* argv[]) {

	if (argc < 2) {
		fprintf(stderr, "Too little args! See -h or --help for help.\n");
		return 1;
	}

	int num = atoi(argv[1]); /* num user inputs */
	mapflags(argc,argv,arr); /* arr contains flags */

	// get individual flags after a -
	FOUND_FLAGS s = { 0 };
	s = getflagstruct(argc, argv, s);

	/* determine first flag, for stuff like -f */
	for (int i = 0; i < argc; i++) {
		if (arr[i] != -1) {
			firstflag = arr[i];
			indexflag = i;
			break;
		}
	}

	// determine flag toggles, check for invalidity
	for (int i = 0; i < argc; i++) {
		if (s.I_EXISTS) {
			infexists = 1;
		}

		if (s.C_EXISTS) {
			clrexists = 1;
		}

		if (s.H_EXISTS) {
			fhelp();
			return 0;
		}

		if (s.INVALID_FLAG) {
			//			fprintf(stderr, "Invalid flag! See -h or --help for help.\n");
			//			return 4;
		}

		if (s.NO_FLAG) {
			fprintf(stderr, "No flag inputted! See -h or --help for help.\n");
			return 5;
		}
	}

	/* incase no flag */
	if (arr[1] == -1) {
		noflag(num);
		exit(1);
	}

	enum flags pick = firstflag;
	switch (pick) {
		case 0:
			if (indexflag != -1) {
				fhelp();
			}
			break;
		case 1:
			fhelp();
			break;
		case 2:
			fsaywords(num);
			break;
		case 3:
			fprintfile(num, argc, argv);
			break;
		case 4:
			fcolor(num, argc, argv);
			break;
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

	getrandom(&seed, sizeof(seed), 0);
	srand(seed);

	if (infexists) {
		num = -1;
	}

	if (clrexists) {
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
	}

	for (int j = 0; j != num; j++) {
		markc = 0;
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

	if (markc == 0) fputs(marks[rmarks], stdout);

	printkernel();
	printdate("%d.%m.%y");

	exit(0);
}

void noflag(int num) {
	fsaywords(num);
};

void fhelp() {
	fputs("Thank you for using talktokernel! Usage:\n"
	"	<command> <flag> <flaginput>\n"
	"\n"
	"By just using <command> <number>, you will use the flagless function and print\n"
	"as usual, using the number in the second argument.\n"
	"\n"
	"	-h or --help: Displays this help menu.\n"
	"	-i (infinite): prints nonstop. Takes in no arguments. \n"
	"	-f (read from file) takes words from file and replaces the printable words with the ones in the file.\n"
	"	Usage: ./binary -f <file> <num> <-c>\n"
	"		Num can be either -i for infinite, or any number you desire.\n"
	"		If -c is specified, print with color.\n"
	"	-c (color) EPILEPSY WARNING!!! Prints words/cells with color\n"
	"	Usage: ./binary -c <num>\n"
	"		Num can either be a valid num or -i, and if unset, colors cells for a trippy AND EPILEPSY-INDUCING EFFECT!!! BE AWARE!! I AM GONNA WARN YOU MULITPLE TIMES!! I AM NOT RESPONSIBLE FOR ANY EPILEPSY ATTACKS THE USER MIGHT HAVE!!\n"
	"This is free software, forever, licensed under the GPL-3.0 license.\nsource code: https://github.com/usr-undeleted/talktokernel\nVersion: 5.0.2\n", stderr);
	exit(0);
}

void fprintfile(int num, int argc, char *argv[]) {
	/* get file, separate its words onto strings, and plop them onto an array (data) */
	fd = fopen(argv[indexflag + 1], "r");

	if (argc < 4) {
		fputs("Too little args! See -h or --help for help.\n", stderr);
		exit(2);
	}
	if (fd == NULL) {
		fputs("Error! File couldn't be opened. Does the file exist or you have the proper permissions?\n", stderr);
		exit(10);
	}

	int i = 0;
	while (fscanf(fd, "%s", cus[i]) == 1 && i < 100) {
		i++;
	}
	cuslen = i;

	num = atoi(argv[indexflag + 2]);

	/* incase input truly is invalid */
	if (num < 1 && !infexists) {
		fprintf(stderr, "Invalid number! See -h or --help for help.\n");
		exit(3);
	}

	fileflag = 1;
	fsaywords(num);
	fclose(fd);
	exit(0);
}

void fcolor (int num, int argc , char *argv[]) {
	/* if succesful, set the ansi color values to their appropriate thing so that
	 * when the main func prints, it wont just print nothing when it tries to print
	 * the color codes. */

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

	getrandom(&seed, sizeof(seed), 0);
	srand(seed);

	if (argc == 2) {
		while (1) {
			rclr = rand() % 9;
			printf("%s%s%d%s", colors[rclr], bgs[rclr], rclr, reset);
		}
	}

	num = atoi(argv[indexflag + 1]);
	if (infexists) {
		num = -1;
	}

	if (num < 1 && !infexists) {
		fprintf(stderr, "Invalid number! See -h or --help for help.\n");
		exit(3);
	}

	if (argc < 3) {
		fprintf(stderr, "Too little args! See -h or --help for help.\n");
		exit(1);
	}

	fsaywords(num);

	exit(0);
}
