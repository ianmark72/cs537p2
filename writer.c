#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void* writer(void* q){

	Queue* Q = (Queue*) q;
	char* string;
	while(1) {
	string = DequeueString(Q);
	printf("%s\n", string);
	free(string);
	//exit on null
	}
	return NULL;
}
