#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *ptr;
	long input = (int)strtol(argv[1], &ptr, 10);
	int rows = (int)input;

	if (ptr[0] != '\0') {
		printf("ERROR: Height must be integer. \n");
	}
	else if (rows > 128) {
		printf("ERROR: Height too large. \n");
	}
	else if (rows < 1) {
		printf("ERROR: Height too small. \n");
	}
	else {
		int spaces = rows - 1;
		int stars = 0;
		for (int i = 0; i<rows; i++) {
			for(int j = 0; j<spaces; j++) {
				printf(" ");
			}
			stars = 2*i + 1;
			for(int k = 0; k<stars; k++) {
				printf("*");
			}
			printf("\n");
			spaces--;
		}
	}
}
