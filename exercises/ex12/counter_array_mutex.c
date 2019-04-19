/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

/*
* #1) Were there any errors with counter_array?
* Yes, mine had 97321 errors, namely repeat counts
*
*
* #4) Compare the times, how much does synching add?
* counter_array w/o print statements:
* real    0m0.017s
* user    0m0.023s
* sys     0m0.004s
*
* counter_array_mutex w/o print statements:
* real    0m0.076s
* user    0m0.061s
* sys     0m0.085s

* This goes from .044 seconds to .222 seconds, or about 5x as much overhead
* predictably, most of this is time is spent by the system.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "mutex.c"

#define NUM_CHILDREN 2

void perror_exit(char *s)
{
    perror(s);
    exit(-1);
}

void *check_malloc(int size)
{
    void *p = malloc(size);
    if (p == NULL) {
        perror_exit("malloc failed");
    }
    return p;
}

typedef struct {
    int counter;
    int end;
    int *array;
    Mutex *mutex;
} Shared;


Shared *make_shared(int end)
{
    int i;
    Shared *shared = check_malloc(sizeof(Shared));


    shared->mutex = make_mutex();
    shared->counter = 0;
    shared->end = end;

    shared->array = check_malloc(shared->end * sizeof(int));
    for (i=0; i<shared->end; i++) {
        shared->array[i] = 0;
    }

    return shared;
}

pthread_t make_thread(void *(*entry)(void *), Shared *shared)
{
    int ret;
    pthread_t thread;

    ret = pthread_create(&thread, NULL, entry, (void *) shared);
    if (ret != 0) {
        perror_exit("pthread_create failed");
    }
    return thread;
}

void join_thread(pthread_t thread)
{
    int ret = pthread_join(thread, NULL);
    if (ret == -1) {
        perror_exit("pthread_join failed");
    }
}

void child_code(Shared *shared)
{
    //printf("Starting child at counter %d\n", shared->counter);

    
    while (1) {
        mutex_lock(shared->mutex);
        if (shared->counter >= shared->end) {
            mutex_unlock(shared->mutex);
            return;
        }
        shared->array[shared->counter]++;
        shared->counter++;

        if (shared->counter % 10000 == 0) {
            //printf("%d\n", shared->counter);
        }
        mutex_unlock(shared->mutex);
    }
}

void *entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    child_code(shared);
    //printf("Child done.\n");
    pthread_exit(NULL);
}

void check_array(Shared *shared)
{
    int i, errors=0;

    //printf("Checking...\n");

    for (i=0; i<shared->end; i++) {
        if (shared->array[i] != 1) errors++;
    }
    //printf("%d errors.\n", errors);
}

int main()
{
    int i;
    pthread_t child[NUM_CHILDREN];

    Shared *shared = make_shared(1000000);

    for (i=0; i<NUM_CHILDREN; i++) {
        child[i] = make_thread(entry, shared);
    }

    for (i=0; i<NUM_CHILDREN; i++) {
        join_thread(child[i]);
    }

    check_array(shared);
    return 0;
}