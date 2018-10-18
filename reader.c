#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void* read(void* q) {
	Queue* queue = (Queue*) q;
	const int BUF_SIZE = 1024;
	char* string;
	
	char input = getchar();
	if ( input != '\0' && input != EOF ) {
		char* buffer = (char*)calloc(BUF_SIZE, sizeof(char));
		int ctr = 0;
		while ( input != EOF && input != '\0') {
			if ( ctr > BUF_SIZE - 1) { 
				//send error to std
			}
			if ( input != '\n') {
				buffer[ctr] = input;
				input = getchar();
				ctr++;
			} else {
				string = (char*)calloc(strlen(buffer), sizeof(char));
				strncpy(string, buffer, BUF_SIZE);
				EnqueueString(queue, string);
				memset(buffer, 0, strnlen(buffer, BUF_SIZE));
				ctr = 0;
			}
		}
	}
	return NULL;
}
