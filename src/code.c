#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include "words.h"
#include "words.h"
#include "utils.h"

#define uint unsigned int
#define clear printf("\033[H\033[J")

void noflag(int num);

int fhelp(int argc);

struct defaultRandomValues {
	uint len1;
	uint len2;
	uint len3;
	uint r1; /* random value for words */
	uint r2 ; /* random value for marks */
	uint r3; /* random value for basics */
	int seed; /* seed edited in for loop */
};
struct defaultRandomValues rvals;

int main (int argc, char* argv[]) {
	int num = 0; /* arg 1*/
	int (*flagfuncs[])(int) = {fhelp}; /* array that contain pointers to functions for flag stuff */

	if (argc < 2) {
		printf("Bad usage! See -h or --help for help.\n(ERR: not enough args)\n");
		return 1;
	}
	num = atoi(argv[1]); /* only set if argv[1] exists - get num from argv[1]*/
	int flagVal = flagchk(argc,argv); /* get flag value */

	if (num < 1) {
		printf("Bad usage! See -h or --help for help.\n(ERR: input too small)\n");
		return 2;
	}

	/* stuff that prints */
	noflag(num); /* start default func */
	(*flagfuncs[0])(argc);
	return 0;
};

void noflag(int num) {
	rvals.len1 = sizeof(words) / sizeof(words[0]);
	rvals.len2 = sizeof(marks) / sizeof(marks[0]);
	rvals.len3 = sizeof(basic) / sizeof(basic[0]);
	int buf = 0;

	printf("\033c"); /* clear terminal */
	for (int i = 0; i < num; i++) {
		buf = getrandom(&rvals.seed, sizeof(rvals.seed), 0);
		srand(rvals.seed);
		rvals.r1 = rand() % rvals.len1; /* words */
		rvals.r2 = rand() % rvals.len2; /* marks */
		rvals.r3 = rand() % rvals.len3; /* basics */

		printf(" %s %s", words[rvals.r1], basic[rvals.r3]); /* word printing */

		if (rand() % 5 == 0) { /* mark printing */
			printf("%s ", marks[rvals.r2]);
		}
	}
	printKernelAuthor();
	system("date +%d.%m.%y");
};

int fhelp(int argc) {
	printf("%d\n",argc);
	return 10;
}
