#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char a[128][2*128+1];

void basictriangle(height, row, column) {
	for (int i = 0; i < height; i++)
	{
		a[row+i][column] = '*';
		for (int j = 0; j <= i; j++)
		{
			a[row+i][column-j] = '*';
			a[row+i][column+j] = '*';
		}
	}
}

void sierpinski(height, row, column, fractal) {
	if (fractal == 0) {
		basictriangle(height, row, column-1);
	}
	else {
		sierpinski(height/2, row, column, fractal-1);
		sierpinski(height/2, row + height/2, column + height/2, fractal-1);
		sierpinski(height/2, row + height/2, column - height/2, fractal-1);
	}
}

int main(int argc, char **argv) {
		
	if (argv[1] == NULL || argv[2] == NULL) {
		printf("ERROW: missing command line argument. \n");
		exit(1);
	}

	char *ptr;
	char *ptr2;
	long input1 = (int)strtol(argv[1], &ptr, 10);
	int height = (int)input1;
	long input2 = (int)strtol(argv[2], &ptr2, 10);
	int fractal = (int)input2;

	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 2*128 + 1; j++)
		{
			a[i][j] = ' ';
		}
	}

	if (ptr[0] != '\0') {
		printf("ERROR: Height must be integer. \n");
	}
	else if  (height > 128) {
		printf("ERROR: Height too large. \n");
	}
	else if  (height < 1) {
		printf("ERROR: Height too small. \n");
	}
	else if (height % (1 << fractal) != 0 && fractal != 0) {
		printf("ERROR: Height not divisible by 2^fractal_levels. \n");
	}
	else {
		sierpinski(height, 0, height, fractal);
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < 2*height + 1; j++)
		{
			printf("%c", a[i][j]);
		}
		printf("\n");
	}
}