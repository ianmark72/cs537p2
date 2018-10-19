/***********************************************************************
* FILENAME: queue.c
*
* DESCRIPTION:
*       This is the file that contains the structure of the queue and 
*       queue pointer. It also has all method the pertain to 
*       manipulating the queue.
*
* AUTHORS: Matthew Derzay, CS Login: derzay
*          Ian Mark, CS Login: imark
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/**
 *  This is the structure of queue. It contains mutex and condition varaibles for 
 *  syncronization and various ints for stat keeping. It also keeps an array of
 *  string as the queue idea.
 */
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
	//Error return value.
	int r;
	//New queue being created.
        Queue *Q;
	//Allocating memory for the queue.
        Q = (Queue*)malloc(sizeof(Queue));

	//Allocating memeory for the string array.
        Q->strings = malloc(sizeof(char*) * size);
	//Setting max size to parameter value.
        Q->capacity = size;

	//Initializing all values in queue to 0;
        Q->front = 0;
        Q->back = 0;
        Q->curAmount = 0;
	Q->enqueueCount = 0;
	Q->dequeueCount = 0;
	Q->enqueueBlockCount = 0;
	Q->dequeueBlockCount = 0;

	//Initialize the mutex lock.
	r = pthread_mutex_init(&Q->lock, NULL);
	if (r != 0) {
                perror("Error: Mutex Initialization.");
                exit(0);
        }

	//Initialize the two condition variables.
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

/**
 *  The structure of the queue pointer. This struct contains two
 *  pointers to queues.
 */
typedef struct QueuePointer {
        Queue* q1;
        Queue* q2;
}QueuePointer;

/**
 *  This is the constructor of a queue pointer.
 *
 *  Parameters: cuQ, nextQ - The two queuees to be added to the pointer.
 *
 *  Return: QueuePointer - The newly creatd queuePointer.
 */
QueuePointer *CreateStringQueuePointer(Queue* curQ, Queue* nextQ) {
	//New queuepointer.
        QueuePointer* QP;
	//Allocate memory for the queue pointer.
        QP = (QueuePointer*)malloc(sizeof(QueuePointer));

	//Set the elements of the queue pointer to the two queues.
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

/**
 *  This method takes a string and puts it into a queue in the next space
 *  that is open.
 *
 *  Parameters: q - The queue for the enqueue.
 *  		string - the string to be enqueued.
 */
void EnqueueString(Queue *q, char *string) {
	//Lock the resouce of queue.
	pthread_mutex_lock(&q->lock);

	//If the queue is full, block until not full.
	if(q->capacity == q->curAmount) {	
		//Block enqueue.	
		pthread_cond_wait(&q->full, &q->lock);
		q->enqueueBlockCount++; 
	}

	//Set string to the next open space.
	q->strings[q->back] = string; 
	if(q->back + 1 == q->capacity) {
		q->back = 0;
	}else{
		q->back++;
	}
	q->curAmount++;

	//If the string is the final null pointer don't count as enqueue.
	if(string != NULL) {
		q->enqueueCount++; 
	}

	//printQueue(q);
	
	//Unlock and signal dequeue.
	pthread_mutex_unlock(&q->lock);
	pthread_cond_signal(&q->empty);
}

/**
 *  This method takes a string off the queue given and returns it.
 *
 *  Parameters: q - The queue being taken from.
 *
 *  Return: char* - The string dequeued.
 */
char* DequeueString(Queue *q) {
	//Lock resource
	pthread_mutex_lock(&q->lock);

	//String being dequeued.
	char* string;

	//If the queue is empty, block until not empty.
	if(q->curAmount == 0) {
		//Block dequeue.
		pthread_cond_wait(&q->empty, &q->lock);
		q->dequeueBlockCount++;
	}

	//Remove the string from the queue.
	string = q->strings[q->front];
	q->strings[q->front] = NULL;
	if(q->front + 1 == q->capacity) {
		q->front = 0;
	}else{
		q->front++;
	}
	q->curAmount--;

	//Don't count the final null pointer as a dequeue.
	if(string != NULL) {
		q->dequeueCount++;
	}

	//printQueue(q);
	
	//Unlock mutex and signal enqueue.
	pthread_mutex_unlock(&q->lock);
	pthread_cond_signal(&q->full);
	return string;
}

/**
 *  This method prints the stats of the queue given.
 *
 *  Parameters: q - The queue of the stats being printed.
 */
void PrintQueueStats(Queue *q) {
	//Lock so the stats can't be altered.
	pthread_mutex_lock(&q->lock);
	//Print all stat elements.
	fprintf(stderr, "Queue Stats:\nEnqueue Count: %d\nDequeue Count: %d\nEnqueue Blocked Count: %d\nDequeue Blocked Count: %d\n", q->enqueueCount, q->dequeueCount, q->enqueueBlockCount, q->dequeueBlockCount);
	pthread_mutex_unlock(&q->lock);
}
