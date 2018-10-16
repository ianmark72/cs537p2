#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
        //int enqueueCount;
        //int dequeueCount;
        //int enqueueBlockCount;
        //int dequeueBlockCount;

        //int front;
        //int back;
        //int curAmount;
        //int capacity;
        //char** strings;

	//sem_t mutex;
}Queue;

Queue* CreateStringQueue(int size);
void EnqueueString(Queue *q, char* string);
char* DequeueString(Queue *q);
void PrintQueueStats(Queue *q);

#endif /* QUEUE_H */

