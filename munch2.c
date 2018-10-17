#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"

void* munch2(void* qp) {
	QueuePointer* QP = (QueuePointer*) qp;
        char* string;
	int i = 0;
        string = DequeueString(QP->q1);

        while(string != '\0') {
		string[i] = toupper(string[i]);
		i++;
	}

        EnqueueString(QP->q2, string);
	return NULL;
}
