#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
	bool sendstate;

	FILE *input_file;
	FILE *output_file;
	input_file = fopen(argv[1], "a+");
	input_file = fopen(argv[1], "r+");
	output_file = fopen(argv[2], "a+");
	if (argc < 3) {
		printf("Error, please two valid file names and a handle as arguments\n");
		return 1;
	}
	char readline[1000];
	char writeline[1000];
	char c;
	if (fgets(readline,1000, input_file)!=NULL) {
		printf("Received: %s ",readline);
		input_file = fopen(argv[1], "w");
		fclose(input_file);
	}
	else {
		printf("Nothing received yet.\n");
	}
	sendstate = true;
	bool cont = true;
	while (true) {
		if (sendstate == true) {
			printf("Send:            ");
			output_file = fopen(argv[2], "w+");
   			fgets(writeline, 1000, stdin);
   			fprintf(output_file, "[%s] %s\n", argv[3], writeline);
  			fclose(output_file);
			sendstate = false;
		}
		else {
			while (cont) {
				input_file = fopen(argv[1], "r+");
				if (fgets(readline,1000, input_file)!=NULL) {
					printf("Received: %s",readline);
					cont = false;
				}
				fclose(input_file);
			}
			cont = true;
			sendstate = true;
			input_file = fopen(argv[1], "w");
			fclose(input_file);
		}
	}

}