#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int main() {	
	char *s1;
	char string1[20] = "Hello";
	s1 = string1;

	printf("before q\n");
	Queue* q = CreateStringQueue(10);
	printf("after q\n");
	EnqueueString(q, s1);
	printf("after enqueue\n");
	printf("%s\n", DequeueString(q));
	printf("after dequeue\n");
	PrintQueueStats(q);	
}

