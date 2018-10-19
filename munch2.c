/***********************************************************************
* FILENAME: munch2.c 
*
* DESCRIPTION:
*       This is the file that takes strings off a queue and changes all
*       the letters to uppercase, then it puts the string onto the 
*       next queue.
* 
* AUTHORS: Matthew Derzay, CS Login: derzay
*          Ian Mark, CS Login: imark
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "queue.h"

void* munch2(void* qp) {
	//Cast queue pointer from void*.
	QueuePointer* QP = (QueuePointer*) qp;
	//String to be manipulated.
        char* string;
	//Counter for looping through the string.
	int i = 0;
	//Flag for termination of the thread.
	int terminate = 0;

	//Continue until thread termination.
	while(1) {
		//Get string from the queue.
		string = DequeueString(QP->q1);
		i = 0;

		//Check if the thread needs to be terminated
		if(string == NULL) {
			terminate = 1;
		}else{
			//Convert all letters to upper case.
        		while(string[i] != '\0') {
				string[i] = toupper(string[i]);
				i++;
			}
		}

		//Put the string onto the  next queue.
        	EnqueueString(QP->q2, string);

		//Terminate the thread.
		if(terminate == 1) {
			pthread_exit(0);
		}
	}

	return NULL;
}
