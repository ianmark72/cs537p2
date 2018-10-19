/***********************************************************************
* FILENAME: munch1.c 
*
* DESCRIPTION:
*       This is the file that takes string off a queue and changes all
*       of the spaces into asterisks, then it places the strings back
*       onto the next queue.
* 
* AUTHORS: Matthew Derzay, CS Login: derzay
*          Ian Mark, CS Login: imark
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "queue.h"

void* munch1(void* qp) {
	//Cast to queue pointer from void*.
	QueuePointer* QP = (QueuePointer*) qp;
	//Max buffer size.
	const int BUF_SIZE = 1024;
	//Character for space.
	char space = ' ';
	//Character for asterisk.
	char asterisk = '*';
	//String pointer that is being passed from the queue.
	char* string;
	//Flag for termination of the thread.
	int terminate = 0;

	//Continue until thread termination.
	while(1) {
		//Get string from queue.
		string = DequeueString(QP->q1);
	
		//If the string pointer is null, terminate thread.
		if(string == NULL) {
			terminate = 1;
		}else{
			//Loop through the string and change all spaces to asterisks.
			for(unsigned int i = 0; i < strnlen(string, BUF_SIZE); i++) {
				if(string[i] == space) {
					string[i] = asterisk;
				}
			}
		}

		//Put the string onto the next queue.
		EnqueueString(QP->q2, string);

		//Terminate thread.
		if(terminate == 1) {
			pthread_exit(0);
		}
	}

	return NULL; 
}
