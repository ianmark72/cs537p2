#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
	int enqueueCount;
	int dequeueCount;
	int enqueueBlockCount;
	int dequeueBlockCount;
}Queue;

Queue *CreateStringQueue(int size) {

}

void EnqueueString(Queue *q, char *string) {

}

char *DequeueString(Queue *q) {

}

void PrintQueueStats(Queue *q) {

}
