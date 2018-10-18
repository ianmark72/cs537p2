#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "queue.h"

void* read(void* q) {
	//Queue* queue = (Queue*) q;
	const int BUF_SIZE = 1024;
	char* string;
// commented out enque for testing	
	char input = getchar();
	if ( input != '\0' && input != EOF ) {
		char* buffer = (char*)calloc(BUF_SIZE, sizeof(char));
		int ctr = 0;
		while ( input != EOF && input != '\0') {
			if ( ctr >= BUF_SIZE - 1) {
				buffer[ctr] = '\0';
				fprintf(stderr, "exceeded buffer size");
			}
			if ( input != '\n') {
				buffer[ctr] = input;
				input = getchar();
				ctr++;
			} else {
				//buffer[ctr] = input;
				string = (char*)calloc(BUF_SIZE, sizeof(char));
				if(string == NULL) { fprintf(stderr, "error calloc");}
				strncpy(string, buffer, BUF_SIZE);
				//EnqueueString(queue, string);
				memset(buffer, 0, BUF_SIZE);
				ctr = 0;
				input = getchar();
			}
		}
		free(buffer);
	}
	return NULL;
}
