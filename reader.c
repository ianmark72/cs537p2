#include "reader.h"
#include <stdio.h>
#include <stdlib.h>


int read() {
	char* buffer = NULL;
	buffer = calloc(100, sizeof(char));
	//replace with BUF_SIZE
	for( int i = 0; i < 100; i++ ){
		
		getc(buffer);
		if (buffer[i] == '\n') { //add line to queue }
	}
	printf("%s", buffer);
}
