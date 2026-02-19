]#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[]) {
	char *words[] = {"For","While","If","Else","Declare","Allocate","Memory"};
	int num = atoi(argv[1]);

	if (argc == 2) {
		if (num >= 1) {

		} else {
			printf("Error! Input is invalid or less than 1.");
			return 2;
		}
	} else {
		printf("Error! Did you type just a number for the second arg (if you typed an arg...)?");
		return 1;
	}
}
