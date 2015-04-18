#ifndef SEMAPHORE_COMMON
#define SEMAPHORE_COMMON

#include <semaphore.h>


// Holds information about shared data
// needed by producer and consumer
struct shared_data_info {
    int BUF_SIZE; // Size of shared buffer (in charms)
    sem_t *mutex;    // 'mutex' semaphore
    sem_t *empty;    // 'empty' semaphore
    sem_t *full;     // 'full' semaphore
	struct charm *charm_buf; // shared buffer
};

// The data we'll be passing
// between processes
// (and part of a
//  balanced breakfast)
struct charm {
    enum COLOR
    {
        PINK = 0,
        YELLOW,
        ORANGE,
        GREEN,
        BLUE,
        PURPLE,
        RED
    } color;
    char shape[32];
};

#define CHARMS 7
extern struct charm LUCKY_CHARMS[];

void print_charm(struct charm *);
#endif
