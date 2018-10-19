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
// commented out enque for testing	
// add null pointer with EOF
		char input;
		char* buffer = (char*)calloc(BUF_SIZE, sizeof(char));
		int ctr = 0;
		int capacity = 0;
		//reorganize loop condition 
		do {
			if ( ctr >= BUF_SIZE -1 ) {
				capacity = 1;
				char c;
				while( c != '\n'){ c = getchar();}
				fprintf(stderr, "Line longer than %i\n", BUF_SIZE);
				memset(buffer, 0, BUF_SIZE);
				ctr = 0;
			}
			input = getchar();
			if ( input != '\n' && input != EOF && capacity != 1) {
				buffer[ctr] = input;
				ctr++;
			} else { // change adding EOF to NULL
				//buffer[ctr] = input
				if(input != EOF) {
				string = (char*)calloc(BUF_SIZE, sizeof(char));
				if(string == NULL) { fprintf(stderr, "error calloc");}
				printf("%s\n", buffer);
				strncpy(string, buffer, BUF_SIZE);
				
			//	EnqueueString(queue, string);
				memset(buffer, 0, BUF_SIZE);
				ctr = 0;
				} else{ 
					string = NULL;
				//	EnqueueString(queue, string);
				}
			}
		} while ( input != EOF);

		free(buffer);
	pthread_exit(0);
	return NULL;
}
