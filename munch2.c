#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "queue.h"

void* munch2(void* qp) {
	QueuePointer* QP = (QueuePointer*) qp;
        char* string;
	int i = 0;
        string = DequeueString(QP->q1);
	int terminate = 0;

	if(string == NULL) {
		terminate = 1;
	}else{
        	while(string[i] != '\0') {
			string[i] = toupper(string[i]);
			i++;
		}
	}

        EnqueueString(QP->q2, string);

	if(terminate == 1) {
		pthread_exit(0);
	}

	return NULL;
}
