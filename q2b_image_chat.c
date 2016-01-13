#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int encode(char *firstfile, char *secondfile, char *message)
{
	const int bmp_header_size = 54;
	const int max_msg_size = 1000;
	int i;
	int curr_message_position=0;
	int read_code;
	int msg_idx = 0;
	int img_idx = 0;
	int bit_idx = 0;
	char c;
	char msg[max_msg_size];
	FILE *img_in = NULL;
	FILE *img_out = NULL;
	
	img_in = fopen( firstfile, "rb" );
	if( img_in == NULL ){
		printf( "Could not open the input image file.\n" );
		return 1;
	}

	img_out = fopen( secondfile, "wb" );
	if( img_out == NULL ){
		printf( "Could not open the output file.\n" );
		return 1;
	}	

	//for( i=0; message[i] != '\0'; i++ ){
		strcpy( msg+curr_message_position, message );
		curr_message_position += strlen(message);

		if( message[i+1] != '\0')
			msg[curr_message_position] = ' ';
			curr_message_position++;
	//}
	msg[curr_message_position] = '\0';

	while( ( read_code = fgetc( img_in )) != EOF ){
		c = (char)read_code;

		if( img_idx >= bmp_header_size && msg_idx <= strlen( msg ) ){
			char bit_mask = 1 << bit_idx;
			
			if( ( msg[msg_idx] & bit_mask) > 0 )
				c |= 1;
			else
				c &= 254;

			bit_idx++;

			if( bit_idx >= 8 ){
				bit_idx = 0;
				msg_idx++;
			}			
		}

		fputc( c, img_out );
		img_idx++;
	}

	//printf( "I have hidden the secret within an image of %d bytes.\n", img_idx );

	fclose(img_in);
	fclose(img_out);

	return 0;
}

int decode(char *filename)
{
	const int bmp_header_size = 54;
	const int max_msg_size = 1000;

	int i;
	int c;
	int img_idx = 0;
	int msg_idx = 0;
	int bit_idx = 0;

	char msg[max_msg_size];
	FILE *img_in = NULL;
	
	img_in = fopen( filename, "rb" );

	if( img_in == NULL ){
		printf( "Could not open the input image file.\n" );
		return 1;
	}

	for( i=0; i < max_msg_size; i++ )
		msg[i] = 0;

	while( ( c = fgetc( img_in )) != EOF ){
		if( img_idx >= bmp_header_size ){
			char bit_mask = 0;
			if( ( c & 1 )  > 0 )
				bit_mask |= 1 << bit_idx;

			msg[msg_idx] |= bit_mask;

			bit_idx++;

			if( bit_idx >= 8 ){
				if( msg[msg_idx] == '\0' )
					break;
				bit_idx = 0;
				msg_idx++;
			}			
		}
		
		img_idx++;
	}

	//printf( "Processed %d bytes.\n", img_idx );
	if (msg[0] != '\0' && strncmp(msg, " ", 1) != 0) {
		printf( "Received: %s", msg );
		fclose(img_in);
		return 0;
	}
	else {
		fclose(img_in);
		return 1;
	}
}

int main(int argc, char *argv[])
{
	bool sendstate;
	char *arg1 = argv[1];
	char *arg2 = argv[2];
	if (argc < 3) {
		printf("Error, please two valid file names and a handle as arguments\n");
		return 1;
	}
	//encode("mars3.bmp", arg2, "");
	if (decode(arg1) != 0) {
		printf("Nothing received yet.\n");
	}
	char readline[1000];
	char writeline[1000];
	char string[1000];
	sendstate = true;
	bool cont = true;
	while (true) {
		if (sendstate == true) {
			printf("Send:            ");
			fgets(writeline, 1000, stdin);
			strcpy(string, "[");
			strcat(string, argv[3]);
			strcat(string, "] ");
			strcat(string, writeline);
			encode("mars3.bmp", arg2, string);
			printf("");
			sendstate = false;
			encode("mars3.bmp", arg1, "");
		}
		else {
			while (cont) {
				if (decode(arg1) != 1) {
					
					cont = false;
				}
			}
			cont = true;
			sendstate = true;
		}
	}

}