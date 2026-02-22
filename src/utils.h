#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>

int flagchk(int argc, char *argv[]) {
	/* int used in returns, return -1 if failed, rest is added on */
	int flagVal = -1;

	/* array that contains all flags used in the project this will be in
	 *	 starts with -h and --help by default, remove if those are uneeded */
	const char *pflags[] = {"--help","-h", "-r"};
	const int arrlen = sizeof(pflags) / sizeof(pflags[0]);

	/* argc check, returns 0 if there is just one arg */
	if (argc < 2) return flagVal;

	/* while loop that compares flag arg to entries in pflags then updates and returns the appropriate flagval */
	for (int i = 0; i < arrlen; i++) {
		if (strcmp(argv[1], pflags[i]) == 0) {
			flagVal = i;
			return flagVal;
		}
	}
	return flagVal;
}

static void printKernelAuthor() { /* print kernel name and stuff */
	struct utsname kernelNameBuffer;
	if (uname(&kernelNameBuffer)) {
		perror("uname");
		exit(EXIT_FAILURE);
	}
	printf("\n\n-- %s, %s\n", kernelNameBuffer.release, kernelNameBuffer.sysname);
} /* thank you tinolm for writing this, i couldnt figure out how uname works myself, so this really helps!  */

#endif
