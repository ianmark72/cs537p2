#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include <pthread.h>

void* read(void* q) {
	Queue* queue = (Queue*) q;
	const int BUF_SIZE = 1024;
	char* string;
	char input;
	char* buffer = (char*)calloc(BUF_SIZE, sizeof(char));
	int ctr = 0;
	char c;
	int noNewLine = 1;

	do {
		if ( ctr >= BUF_SIZE - 1 ) {	
			do{
				c = getchar();
			}while( c != '\n');
			fprintf(stderr, "Line longer than %i\n", BUF_SIZE);
			memset(buffer, 0, BUF_SIZE);
			ctr = 0;
			noNewLine = 1;
		}
		input = getchar();
		//Everything else
		if ( input != '\n' && input != EOF) {
			buffer[ctr] = input;
			ctr++;
			noNewLine = 1;
		} else { //newline
			if(input != EOF) {
				string = (char*)calloc(BUF_SIZE, sizeof(char));
				if(string == NULL) { fprintf(stderr, "error calloc");}

				strncpy(string, buffer, BUF_SIZE);
				EnqueueString(queue, string);
				memset(buffer, 0, BUF_SIZE);

				ctr = 0;
				noNewLine = 0;
			} else{ //EOF
				if(noNewLine == 1) {
					string = (char*)calloc(BUF_SIZE, sizeof(char));
					strncpy(string, buffer, BUF_SIZE);
					EnqueueString(queue, string);
				}
				string = NULL;
				EnqueueString(queue, string);
			}
		}
	} while ( input != EOF);

	pthread_exit(0);
	return NULL;
}
