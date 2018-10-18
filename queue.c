#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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

	pthread_mutex_t lock;
        pthread_cond_t empty;
        pthread_cond_t full;
}Queue;

Queue *CreateStringQueue(int size) {
	int r;
        Queue *Q;
        Q = (Queue*)malloc(sizeof(Queue));

        Q->strings = malloc(sizeof(char*) * size);
        Q->capacity = size;
        Q->front = 0;
        Q->back = 0;
        Q->curAmount = 0;
	Q->enqueueCount = 0;
	Q->dequeueCount = 0;
	Q->enqueueBlockCount = 0;
	Q->dequeueBlockCount = 0;

	r = pthread_mutex_init(&Q->lock, NULL);
	if (r != 0) {
                perror("Error: Mutex Initialization.");
                exit(0);
        }

	r = pthread_cond_init(&Q->empty, NULL);
	if (r != 0) {
                perror("Error: Condition Variable Initialization.");
                exit(0);
        }

	r = pthread_cond_init(&Q->full, NULL);
	if (r != 0) {
                perror("Error: Condition Variable Initialization.");
                exit(0);
        }

        return Q;
}

typedef struct QueuePointer {
        Queue* q1;
        Queue* q2;
}QueuePointer;

QueuePointer *CreateStringQueuePointer(Queue* curQ, Queue* nextQ) {
        QueuePointer* QP;
        QP = (QueuePointer*)malloc(sizeof(QueuePointer));

        QP->q1 = curQ;
        QP->q2 = nextQ;

        return QP;
}

void EnqueueString(Queue *q, char *string) {
	pthread_mutex_lock(&q->lock);
	if(q->capacity == q->curAmount) {
		printf("Queue is full.");
		//Block enqueue.
		pthread_cond_wait(&q->full, &q->lock);
		q->enqueueBlockCount++; 
	}

	q->strings[q->back] = string; 
	if(q->back + 1 == q->capacity) {
		q->back = 0;
	}else{
		q->back++;
	}
	if(q->curAmount == 0) {
		pthread_cond_signal(&q->empty);
	}
	q->curAmount++;
	q->enqueueCount++;
	
	pthread_mutex_unlock(&q->lock);
}

char* DequeueString(Queue *q) {
	pthread_mutex_lock(&q->lock);
	char* string;
	if(q->curAmount == 0) {
		printf("Nothing to dequeue.");
		//Block dequeue.
		pthread_cond_wait(&q->empty, &q->lock);
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
		pthread_cond_signal(&q->full);	
	}
	q->curAmount--;
	q->dequeueCount++;

	return string;
	pthread_mutex_unlock(&q->lock);
}

void PrintQueueStats(Queue *q) {
	pthread_mutex_lock(&q->lock);
	printf("Enqueue Count: %d\n", q->enqueueCount);
	printf("Dequeue Count: %d\n", q->dequeueCount);
	printf("Enqueue Blocked Count: %d\n", q->enqueueBlockCount);
	printf("Dequeue Blocked Count: %d\n", q->dequeueBlockCount);
	pthread_mutex_unlock(&q->lock);
}
