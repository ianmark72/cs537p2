#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "queue.h"

void* munch1(void* qp) {
	// while true on null, exit
	QueuePointer* QP = (QueuePointer*) qp;
	const int BUF_SIZE = 1024;
	char space = ' ';
	char asterisk = '*';
	char* string;
	int terminate = 0;

	while(1) {
		string = DequeueString(QP->q1);
	
		if(string == NULL) {
			terminate = 1;
		}else{
			for(unsigned int i = 0; i < strnlen(string, BUF_SIZE); i++) {
				if(string[i] == space) {
					string[i] = asterisk;
				}
			}
		}

		EnqueueString(QP->q2, string);

		if(terminate == 1) {
			pthread_exit(0);
		}
	}

	return NULL; 
}
