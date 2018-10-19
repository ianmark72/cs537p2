#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct Queue {
	//Number of strings enqueued.
	int enqueueCount;
	//Number of strings dequeued.
	int dequeueCount;
	//Number of times the thread was blocked from enqueuing.
	int enqueueBlockCount;
	//Number of times the thread was blocked from dequeuing.
	int dequeueBlockCount;
	
	//Front of the queue.
	int front;
	//Back of the queue.
	int back;	
	//Total strings in the queue.
	int curAmount;
	//Max amount of string in the queue.
	int capacity;
	//Array of strings.
	char** strings;

	//Monitor lock for syncronization.
	pthread_mutex_t lock;
	//Condition variables for blocking.
        pthread_cond_t empty;
        pthread_cond_t full;
}Queue;

/**
 *  This is the constructor of a queue.
 *
 *  Parameters: size - The size of the queue.
 *
 *  Return: Queue - The newly created queue.
 */
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

// function to print out a queue
void printQueue(Queue* q) {
        for (int i =0; i < 10; i ++) {
                if(q->strings[i] == NULL) { printf("%i:  No string\n", i);}
                else {
                        printf("%i: %s\n", i , q->strings[i]);
                }
		printf("\n");
        }
}

void EnqueueString(Queue *q, char *string) {
	pthread_mutex_lock(&q->lock);
	if(q->capacity == q->curAmount) {	
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
	q->curAmount++;
	if(string != NULL) {
		q->enqueueCount++; 
	}
	printQueue(q);
	pthread_mutex_unlock(&q->lock);
	pthread_cond_signal(&q->empty);
}

char* DequeueString(Queue *q) {
	pthread_mutex_lock(&q->lock);
	char* string;
	if(q->curAmount == 0) {
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
	
	q->curAmount--;
	if(string != NULL) {
		q->dequeueCount++;
	}
	//printQueue(q);
	pthread_mutex_unlock(&q->lock);
	pthread_cond_signal(&q->full);
	return string;
}

void PrintQueueStats(Queue *q) {
	pthread_mutex_lock(&q->lock);
	fprintf(stderr, "Queue Stats:\nEnqueue Count: %d\nDequeue Count: %d\nEnqueue Blocked Count: %d\nDequeue Blocked Count: %d\n", q->enqueueCount, q->dequeueCount, q->enqueueBlockCount, q->dequeueBlockCount);
	pthread_mutex_unlock(&q->lock);
}
