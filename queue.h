#ifndef QUEUE_H
#define QUEUE_H

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

typedef struct QueuePointer {
	Queue* q1;
        Queue* q2;
}QueuePointer;

QueuePointer *CreateStringQueuePointer(Queue* q1, Queue* q2);
Queue* CreateStringQueue(int size);
void EnqueueString(Queue *q, char* string);
char* DequeueString(Queue *q);
void PrintQueueStats(Queue *q);

#endif /* QUEUE_H */

