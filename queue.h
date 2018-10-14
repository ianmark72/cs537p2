#ifndef QUEUE_H
#define QUEUE_H

Queue* CreateStringQueue(int size);
void EnqueueString(Queue *q, char* string);
char* DequeueString(Queue *q);
void PrintQueueStats(Queue *q);

#endif /* QUEUE_H */

