/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void free_anything(int *p) {
    free(p);
}

int read_element(int *array, int index) {
    int x = array[index];
    return x;
}

int main()
{
    int never_allocated;
    int *free_twice = malloc(sizeof (int));
    int *use_after_free = malloc(sizeof (int));
    int *never_free = malloc(sizeof (int));
    int array1[100];
    int *array2 = malloc(100 * sizeof (int));

    // valgrind does not bounds-check static arrays
    //Original:
    // read_element(array1, -1);
    // read_element(array1, 100);
    //My Fix (change the index you're reading from to be in bounds:
    read_element(array1, 0);
    read_element(array1, 99);

    // but it does bounds-check dynamic arrays
    //Original:
    // read_element(array2, -1);
    // read_element(array2, 100);
    //My fix (change the indexs you're reading from to be in bounds)
    read_element(array1, 0);
    read_element(array1, 99);

    // and it catches use after free
    free(use_after_free);
    //Just don't use it a gain OR malloc it again  after
    //Don't do this *use_after_free = 17; before doing this again *use_after_free = malloc(sizeof (int));

    // never_free is definitely lost
    *never_free = 17;

    // the following line would generate a warning
    // free(&never_allocated);

    // but this one doesn't
    //Don't try to free things that weren't allocated in the first place - that's a paddlin'
    //free_anything(&never_allocated);


    //Fix: only free things once
    free(free_twice);
    //free(free_twice);

    return 0;
}
