#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void* writer(Queue* q){
	char* string;
	string = DequeueString(q);
	printf("%s\n", string);
	free(string);
}
