#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void* munch1(QueuePointer* QP) {
	char space = ' ';
	char asterisk = '*';
	char* string;
	string = DequeueString(QP->q1);

	for(int i = 0; i < strnlen(string); i++) {
		if(string[i] == space) {
			string[i] = asterisk;
		}
	}

	EnqueueString(QP->q2, string);
}
