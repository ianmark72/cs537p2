#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
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

