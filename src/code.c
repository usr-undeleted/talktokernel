#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/random.h>

/*add support for making sure getrandom works always with ssize_t or something*/

int main (int argc, char* argv[]) {
	const char *words[] = {"For","While","If","Else","Declare","Allocate","Memory"};
	int num; /* arg 1 */
	unsigned int len = sizeof(words) / sizeof(words[0]); /* gets length of array for more robust-ness */

	int r; /* random value used in for loop */
	int seed; /* seed edited in for loop */
	int buf; /* buffer for getrandom(), maybe use memory allocation for that sometime? */

	if (argc == 2) { /* check to see if there are enough args */
		num = atoi(argv[1]); /* only sets it now to prevent checking argv[1] even if it doesnt exist */

		if (num >= 1) { /* check to see if inputted number is valid */
			for (int i = 0; i < num; i++) {
				buf = getrandom(&seed, sizeof(seed), 0);
				srand(seed);
				r = rand() % len;
				printf("%s ", words[r]);
			}
			printf("\n");
			return 0;
		} else {
			printf("Error! Input is invalid or less than 1.\n");
			return 2;
		}
	} else {
		printf("Error! Did you type just a number for the second arg (if you typed an arg...)?\n");
		return 1;
	}
}
