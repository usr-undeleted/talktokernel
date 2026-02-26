#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>

int *mapflags(int argc, char *argv[], int arr[]) {
	/* the flags the program will check */
	const char *pflags[] = {"--help","-h","-i"};
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
