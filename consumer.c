#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "common.h"

void *consumer(void *shared_data) {
	
	struct shared_data_info *shared = (struct shared_data_info *)shared_data;
    int nextc = 0;

    // Consume every delicious
    // marshmallow
    int c;
    for(c = 0; c < CHARMS; c++) {

        // wait(full)
        if(sem_wait(shared->full) == -1) {
            perror("wait(full)");
            pthread_exit(NULL);
        }
        
        // wait(mutex)
        if(sem_wait(shared->mutex) == -1) {
            perror("wait(mutex)");
            pthread_exit(NULL);
        }

        /********************CRITICAL SECTION BEGIN********************/
        
        // Shared memory access
        struct charm consume_charm = (shared->charm_buf)[nextc];
        nextc = (nextc + 1) % shared->BUF_SIZE;
        printf("    Consuming: ");
        print_charm(&consume_charm);
        printf("\n");
        fflush(0);

        /*********************CRITICAL SECTION END*********************/

        // signal(mutex)
        if(sem_post(shared->mutex) == -1) {
            perror("signal(mutex)");
            pthread_exit(NULL);
        }

        // signal(empty)
        if(sem_post(shared->empty) == -1) {
            perror("signal(empty)");
            pthread_exit(NULL);
        }

    }
    
    pthread_exit(NULL);
}
