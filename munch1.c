#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void* munch1(void* qp) {
	QueuePointer* QP = (QueuePointer*) qp;
	const int BUF_SIZE = 1024;
	char space = ' ';
	char asterisk = '*';
	char* string;
	string = DequeueString(QP->q1);

	for(unsigned int i = 0; i < strnlen(string, BUF_SIZE); i++) {
		if(string[i] == space) {
			string[i] = asterisk;
		}
	}

	EnqueueString(QP->q2, string);
	return NULL; 
}
