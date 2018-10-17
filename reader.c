#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void* read(void* q) {
	Queue* queue = (Queue*) q;

	const int BUF_SIZE = 1024;
	char input = getchar();
	if ( input != '\0' && input != EOF ) {
		char* buffer = calloc(BUF_SIZE, sizeof(char));
		int ctr = 0;
		while ( input != EOF && input != '\0') {
			if ( ctr > BUF_SIZE) { 
				//send error to std
			}
			if ( input != '\n') {
			buffer[ctr] = input;
			input = getchar();
			ctr++;
			}
			else {
				EnqueueString(queue, buffer);
				buffer = calloc(BUF_SIZE, sizeof(char));
				ctr = 0;
			}
		}
	}
	return NULL;
}
