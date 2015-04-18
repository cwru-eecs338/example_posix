#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "common.h"

void *producer(void *shared_data) {
	
	struct shared_data_info *shared = (struct shared_data_info *)shared_data;
    int nextp = 0;

    // Produce the charms
    int c;
    for(c = 0; c < CHARMS; c++) {

        // wait(empty)
        if(sem_wait(shared->empty) == -1) {
            perror("wait(empty)");
            pthread_exit(NULL);
        }
        
        // wait(mutex)
        if(sem_wait(shared->mutex) == -1) {
            perror("wait(mutex)");
            pthread_exit(NULL);
        }

        /********************CRITICAL SECTION BEGIN********************/
        
        struct charm *produce_charm = &LUCKY_CHARMS[c];
        printf("Producing: ");
        print_charm(produce_charm);
        printf("\n");
		fflush(0);
        shared->charm_buf[nextp] = *produce_charm; // Shared memory access
        nextp = (nextp + 1) % shared->BUF_SIZE;

        /*********************CRITICAL SECTION END*********************/

        // signal(mutex)
        if(sem_post(shared->mutex) == -1) {
            perror("signal(mutex)");
            pthread_exit(NULL);
        }

        // signal(full)
        if(sem_post(shared->full) == -1) {
            perror("signal(full)");
            pthread_exit(NULL);
        }

    }

    pthread_exit(NULL);
}
