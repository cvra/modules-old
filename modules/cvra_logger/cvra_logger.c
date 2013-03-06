/*
 * cvra_logger.c
 *
 *  Created on: 21 mars 2012
 *      Author: Antoine Albertelli
 */

#include <aversive.h>

#include <cvra_logger.h>
#include <stdlib.h>
#include <string.h>

/* On alloue un buffer de 10M */
#define LOGSIZE (10*1000000*sizeof(char))

static char *write_pointer=NULL;
static char *read_pointer;
int buffer_size;

void cvra_logger_reset() {
	if(write_pointer != NULL) {
		free(write_pointer);
	}

	write_pointer = malloc(LOGSIZE);

    if(write_pointer == NULL) 
        panic();

	read_pointer = write_pointer;
	memset(write_pointer, 0, LOGSIZE);
	buffer_size = LOGSIZE-1;
}


const char *cvra_logger_get_log() {
	const char *tmp = read_pointer;
	read_pointer = write_pointer;
	return tmp;
}


void cvra_logger_log(const char *message) {
	int len = strlen(message);
	if(buffer_size - len < 0) return;
	strncpy(write_pointer, message, buffer_size);
	buffer_size -= len;
	write_pointer += len;
}
