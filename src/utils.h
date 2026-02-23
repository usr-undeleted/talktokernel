#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>

/* get arr from caller */
int *mapflags(int argc, char *argv[], int arr[]) {
	/* the flags the program will check */
	const char *pflags[] = {"--help","-h","-i"};
	const int tflags = sizeof(pflags) / sizeof(pflags[0]);
	/* set all entries to -1 by default */
	memset(arr,-1,sizeof(*arr));

	for (int i = 0; i < argc; i++) {
		arr[i] = -1; /* by default, entry is -1 as it didnt find a match */

		for (int j = 0; j < tflags; j++) { /* j will be the entry of pflags incase there is a match */
			if (strcmp(argv[i], pflags[j]) == 0) { /* if the entry matches one of the entries inside pflags*/
				arr[i] = j; /* pflags gets translated into an int (j) and then put into map */
				break;
			}
		}
	}
	return arr;
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
