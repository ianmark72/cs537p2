#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
	int enqueueCount;
	int dequeueCount;
	int enqueueBlockCount;
	int dequeueBlockCount;
	
	int curAmount;
	int capacity;
	char** strings;
}Queue;

Queue *CreateStringQueue(int size) {
	Queue *Q;
	Q = (Queue*)malloc(sizeof(Queue));

	Q->strings = (char**)malloc(sizeof(char*) * size);
	capacity = size;
	curAmount = 0;

	return Q;
}

void EnqueueString(Queue *q, char *string) {

}

char *DequeueString(Queue *q) {

}

void PrintQueueStats(Queue *q) {

}
