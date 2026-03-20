#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <ctype.h>

// both flag funcs are used in tandem

// will check for literal strings
int *mapflags(int argc, char *argv[], int arr[]) {
	/* the flags the program will check */
	const char *pflags[] = {"--help","-h","-i", "-f", "-c"};
	const int tflags = sizeof(pflags) / sizeof(pflags[0]);

	for (int i = 0; i < argc; i++) {
		arr[i] = -1; /* by default, entry is -1 as it didnt find a match */

		for (int j = 0; j < tflags; j++) {
			if (strcmp(argv[i], pflags[j]) == 0) {
				arr[i] = j;
				break; /* for i loop restarts for j loop */
			}
		}
	}
	return arr;
}

typedef struct {
	int H_EXISTS;
	int I_EXISTS;
	int C_EXISTS;
	int INVALID_FLAG; // incase user puts wrong input
	int NO_FLAG; // incase no flag is even inputted
} FOUND_FLAGS;

// will check for stuff after -
static inline FOUND_FLAGS getflagstruct (int argc, char *argv[], FOUND_FLAGS s) {

	// toggle that will see if no valid flags
	// were found (therefore, chk = 0)
	int chk = 0;

	// first loop will cycle trough all args
	for (int i = 1; i < argc; i++) {

		// check if '-' exists
		if (argv[i][0] == '-') {

			// second loop to check all chars
			// after '-'
			for (int j = 0; j < strlen(argv[i]); j++) {

				if (argv[i][1] == '\0') { // incase no flag is even inputted
					s.NO_FLAG = 1;
					break;
				}

				// add flags here as needed
				chk = 0;
				if (argv[i][j] == 'h') {
					s.H_EXISTS = 1;
					chk++;
				} else if (argv[i][j] == 'i') {
					s.I_EXISTS = 1;
					chk++;
				} else if (argv[i][j] == 'c') {
					s.C_EXISTS = 1;
					chk++;
				} else if (argv[i][j] == 'f') {
					// blank
				}
			}
		}
	}

	// incase an invalid flag is found
	if (!chk) {
		s.INVALID_FLAG = 1;
	}

	return s;
}


void printdate(char* fmt) {
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	char buf[64];

	strftime(buf, sizeof(buf), fmt, t);
	fputs(buf, stderr);
	fputs("\n", stderr);

	return;
}

void printkernel() { /* print kernel name and stuff */
	struct utsname unamebuf;
	if (uname(&unamebuf)) {
		perror("uname");
		exit(EXIT_FAILURE);
	}
	printf("\n\n-- %s, %s\n", unamebuf.release, unamebuf.sysname);
} /* thank you tinolm for writing this, i couldnt figure out how uname works myself, so this really helps!  */

#endif
