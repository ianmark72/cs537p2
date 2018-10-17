#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t queueThread;

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

typedef struct QueuePointer {
        Queue* q1;
        Queue* q2;
}QueuePointer;

QueuePointer *CreateStringQueuePointer(Queue* q1, Queue* q2) {
	QueuePointer* QP;
	QP = (QueuePointer*)malloc(sizeof(QueuePointer));

	QP->q1 = q1;
	QP->q2 = q2;

	return QP;
}

Queue *CreateStringQueue(int size) {
	Queue *Q;
	Q = (Queue*)malloc(sizeof(Queue));

	Q->strings = malloc(sizeof(char*) * size);
	Q->capacity = size;
	Q->front = 0;
	Q->back = 0;
	Q->curAmount = 0;

	return Q;
}

void EnqueueString(Queue *q, char *string) {
	pthread_mutex_lock(&lock);
	if(q->capacity == q->curAmount) {
		printf("Queue is full.");
		//Block enqueue.
		pthread_cond_wait(&queueThread, &lock);
		q->enqueueBlockCount++; 
	}

	q->strings[q->back] = string; 
	if(q->back + 1 == q->capacity) {
		q->back = 0;
	}else{
		q->back++;
	}
	if(q->curAmount == 0) {
		pthread_cond_signal(&queueThread);
	}
	q->curAmount++;
	q->enqueueCount++;
	
	pthread_mutex_unlock(&lock);
}

char* DequeueString(Queue *q) {
	pthread_mutex_lock(&lock);
	char* string;
	if(q->curAmount == 0) {
		printf("Nothing to dequeue.");
		//Block dequeue.
		pthread_cond_wait(&queueThread, &lock);
		q->dequeueBlockCount++;
	}

	string = q->strings[q->front];
	q->strings[q->front] = NULL;
	if(q->front + 1 == q->capacity) {
		q->front = 0;
	}else{
		q->front++;
	}
	if(q->curAmount == q->capacity){
		pthread_cond_signal(&queueThread);	
	}
	q->curAmount--;
	q->dequeueCount++;

	return string;
	pthread_mutex_unlock(&lock);
}

void PrintQueueStats(Queue *q) {
	pthread_mutex_lock(&lock);
	printf("Enqueue Count: %d\n", q->enqueueCount);
	printf("Dequeue Count: %d\n", q->dequeueCount);
	printf("Enqueue Blocked Count: %d\n", q->enqueueBlockCount);
	printf("Dequeue Blocked Count: %d\n", q->dequeueBlockCount);
	pthread_mutex_unlock(&lock);
}
