#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void* read(Queue* queue) {

	const int BUF_SIZE;
	char input = getchar();
	if ( first != '/0' && first != EOF ) {
		char* buffer = calloc(BUF_SIZE, sizeof(char));
		int ctr = 0;
		while ( c != EOF && c != '/0') {
			if ( ctr > BUF_SIZE) { 
				//send error to std
			}
			if ( input != '/n') {
			buffer[ctr] = input;
			input = getchar();
			ctr++;
			}
			else {
				EnqueueString(buffer, queue);
				buffer = calloc(BUF_SIZE, sizeof(char));
				ctr = 0;
			}
		}
	}
}
