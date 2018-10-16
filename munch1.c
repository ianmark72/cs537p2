#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void munch1(Queue* curQ, Queue* nextQ) {
	char space = ' ';
	char asterisk = '*';
	char* string;
	string = DequeueString(curQ);

	for(int i = 0; i < strnlen(string); i++) {
		if(string[i] == space) {
			string[i] = asterisk;
		}
	}

	EnqueueString(nextQ, string);
}
