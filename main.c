#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "reader.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"
#include "queue.h"

int main() {
	int r;
	int queueSize = 10;

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	Queue* q1 = CreateStringQueue(queueSize);
	Queue* q2 = CreateStringQueue(queueSize);
	Queue* q3 = CreateStringQueue(queueSize);

	QueuePointer* QP1 = CreateStringQueuePointer(q1, q2);
	QueuePointer* QP2 = CreateStringQueuePointer(q2, q3)

	//Thread one, Reader Method
	r = pthread_create(&thread1, NULL, read, q1);
        if (r != 0) {
		perror("Error: Thread Creation.");
		exit(0);
	}
	r = pthread_join(&thread1, NULL);
        if (r != 0) {
                perror("Error: Thread Join.");
                exit(0);
        }

	//Thread two, Munch1 Method
	r = pthread_create(&thread2, NULL, munch1, QP1);
        if (r != 0) {
                perror("Error: Thread Creation.");
                exit(0);
        }
        r = pthread_join(&thread2, NULL);
        if (r != 0) {
                perror("Error: Thread Join.");
                exit(0);
        }

	//Thread three, Munch2 Method
	r = pthread_create(&thread3, NULL, munch2, QP2);
        if (r != 0) {
                perror("Error: Thread Creation.");
                exit(0);
        }
        r = pthread_join(&thread3, NULL);
        if (r != 0) {
                perror("Error: Thread Join.");
                exit(0);
        }

	//Thread four, Writer Method
	r = pthread_create(&thread4, NULL, writer, q3);
        if (r != 0) {
                perror("Error: Thread Creation.");
                exit(0);
        }
        r = pthread_join(&thread4, NULL);
        if (r != 0) {
                perror("Error: Thread Join.");
                exit(0);
        }
}
