#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void munch2(Queue* curQ, Queue* nextQ) {
        char* string;
        string = DequeueString(curQ);

        for(int i = 0; i < strnlen(string); i++) {
                if(string[i] < 123 || string[i] > 96) {
                        string[i] = string[i] - 32;
                }
        }

        EnqueueString(nextQ, string);
}
