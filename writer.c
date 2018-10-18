#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "queue.h"

void* writer(void* q){

	Queue* Q = (Queue*) q;
	char* string;
	while(1) {
	string = DequeueString(Q);
	int terminate = 0;

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
	return NULL;
}
