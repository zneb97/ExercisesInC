/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


/*
* Test to ensure global variables are shared as per the HW
* Given that threads share text and code segments, it makes sense
* They should also share global
*/
int global_test = 42;
int i;

typedef struct {
    int heap_test;
} Shared;


// errno is an external global variable that contains
// error information
extern int errno;


// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i, Shared *hare)
{
    sleep(i);
    printf("Hello from child %d.\n", i);
    /*
    * Test to ensure global variables are shared as per the HW
    * Given that threads share text and code segments, it makes sense
    * they should also share global. This is proven in the printing of the below
    */
    printf("This is a test of global %i for child %d.\n", global_test, i);
    /*
    * Having two different functions in eahc thread (two printfs) and having them
    * executre in different orders in different executions of the programs is proof
    * of threads having different stacks. If they shared stacks, they would process the 
    * functions in order before moving on to the next due to the FILO principle. With multiple
    * stacks this does not apply.
    */

    /*
    * Test for if a structure, which exists on the heap, can be accessed by each thread
    * Yes, it can because they all share the heap
    *
    */

     printf("This is a test of heap %i for child %d.\n", hare->heap_test, i);

     /*
     * Turning the how many children to make into a global then having the first
     * child set the number lower proves that they share code and text. This may or may
     * not work due to timing
     */ 
     i = 5;

}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int num_children;
    Shared test_struct;
    test_struct.heap_test = 33;


    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i, &test_struct);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time

    /*
    * Confirm gloabal has changed
    * confirm heap has changed
    */
    printf("Global is now %i\n", global_test);
    printf("Struct on heap is now %i\n", test_struct.heap_test);
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
