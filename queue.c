#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

sem_t mutex;
sem_init(&mutex, 0, 1);

typedef struct Queue {
	int enqueueCount;
	int dequeueCount;
	int enqueueBlockCount;
	int dequeueBlockCount;
	
	int front;
	int back;	
	int curAmount;
	int capacity;
	char** strings;
}Queue;

Queue *CreateStringQueue(int size) {
	sem_wait(&mutex);
	Queue *Q;
	Q = (Queue*)malloc(sizeof(Queue));

	Q->strings = malloc(sizeof(char*) * size);
	Q->capacity = size;
	Q->front = 0;
	Q->back = 0;
	Q->curAmount = 0;

	sem_post(&mutex);
	return Q;
}

void EnqueueString(Queue *q, char *string) {
	sem_wait(&mutex);
	if(q->capacity == q->curAmount) {
		printf("Queue is full.");
		//Block enqueue.
		q->enqueueBlockCount++; 
	}else{
		q->strings[back] = &string; 
		if(back + 1 == capacity) {
			q->back = 0;
		}else{
			q->position++;
		}
		q->curAmount++;
		q->enqueueCount++;
	}
	sem_post(&mutex);
}

char* DequeueString(Queue *q) {
	sem_wait(&mutex);
	char* string;
	if(q->curAmount == 0) {
		printf("Nothing to dequeue.");
		//Block dequeue.
		q->dequeueBlockCount++;
	}else{
		string = &q->strings[front];
		q->strings[front] = NULL;
		if(q->front + 1 == q->capacity) {
			q->front = 0;
		}else{
			q->front++;
		}
		q->curAmount--;
		q->dequeueCount++;
	}
	sem_post(&mutex);
	return string;
}

void PrintQueueStats(Queue *q) {
	sem_wait(&mutex);
	printf("Enqueue Count: %d\n", q->enqueueCount);
	printf("Dequeue Count: %d\n", q->dequeueCount);
	printf("Enqueue Blocked Count: %d\n", q->enqueueBlockCount);
	printf("Dequeue Blocked Count: %d\n", q->dequeueBlockCount);
	sem_post(&mutex);
}
