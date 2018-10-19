/***********************************************************************
* FILENAME: main.c 
*
* DESCRIPTION:
*       This is the main file of the program. It creates all of the
*       threads, queues, and queuePointers. It also prints the stats
*       of the queues at the end.
* 
* AUTHORS: Matthew Derzay, CS Login: derzay
*          Ian Mark, CS Login: imark
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "reader.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"
#include "queue.h"

int main() {
	//Error return.
	int r;
	//Max capacity of the queue.
	int queueSize = 10;

	//Threads for each function.
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	//Queues to pass strings between the four functions.
	Queue* queue1 = CreateStringQueue(queueSize);
	Queue* queue2 = CreateStringQueue(queueSize);
	Queue* queue3 = CreateStringQueue(queueSize);

	//Queue Pointers to hold two queue to be passed as one argument into pthread_create.
	QueuePointer* QP1 = CreateStringQueuePointer(queue1, queue2);
	QueuePointer* QP2 = CreateStringQueuePointer(queue2, queue3);

	//Thread one, Reader Method
	r = pthread_create(&thread1, NULL, read, queue1);
        if (r != 0) {
		perror("Error: Thread Creation.");
		exit(0);
	}

	//Thread two, Munch1 Method
	r = pthread_create(&thread2, NULL, munch1, QP1);
        if (r != 0) {
                perror("Error: Thread Creation.");
                exit(0);
        }

	//Thread three, Munch2 Method
	r = pthread_create(&thread3, NULL, munch2, QP2);
        if (r != 0) {
                perror("Error: Thread Creation.");
                exit(0);
        }

	//Thread four, Writer Method
	r = pthread_create(&thread4, NULL, writer, queue3);
        if (r != 0) {
                perror("Error: Thread Creation.");
                exit(0);
        }
	
	//Join threads
	r = pthread_join(thread1, NULL);
        if (r != 0) {
                perror("Error: Thread Join.");
                exit(0);
        }
	r = pthread_join(thread2, NULL);
        if (r != 0) {
                perror("Error: Thread Join.");
                exit(0);
        }
	r = pthread_join(thread3, NULL);
        if (r != 0) {
                perror("Error: Thread Join.");
                exit(0);
        }
	r = pthread_join(thread4, NULL);
        if (r != 0) {
                perror("Error: Thread Join.");
                exit(0);
        }

	//Print out queue stats.
	PrintQueueStats(queue1);
	PrintQueueStats(queue2);
	PrintQueueStats(queue3);	
}
