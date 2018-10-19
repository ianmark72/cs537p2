/***********************************************************************
* FILENAME: writer.c 
*
* DESCRIPTION:
*       This is the the file that takes strings off the queue and prints
*       them out. It then frees the memory of the string.
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

/**
 *  This function takes string off of the queue and prints them out.
 *  It also frees the memory allocated to the string.
 *
 *  Parameters: q - The queue the strings are being taken from.
 *
 *  Return: void* - NULL, nothing of value.
 */
void* writer(void* q){

	Queue* Q = (Queue*) q;
	char* string;
	int terminate = 0;
	// Loop that waits for queue to recieve signal
	while(1) {
		//take string off queue
		string = DequeueString(Q);
		// terminate proccess if we have read the last string
		if(string == NULL){
			terminate = 1;
		}else{
			printf("%s\n", string);
		}
		free(string);
		//exit on null

		if(terminate == 1) {
			pthread_exit(0);
		}
	}
	return NULL;
}
