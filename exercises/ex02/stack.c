/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/*
* 1) This appears to be intended to first create an array of
* the interger 42 of predefined length, then to print it out element
* by element. This is done in the foo function. The bar function gets
* called but only allocates and writes an array whose elements correspond
* to their index.
*
* 2) Attempting to compile returned the warning of
* "function returns address of local variable", referring
* to the "foo" function. This means that the function returns
* an address of a locally scoped variable of the function, something that
* is overwrriten in the bar function by an array of the same size
* because it was also declared in the local scope.
*
* 3) Segmentation fault occurs because what is no written at the
* address is no longer what was expected, it has been made obsolete since
* it only had a local scope, which ended with the return of the foo function
*
* 4) Same segmentation fault error occurs, it just becomes much
* harder to debug because the print statements would have clued you into the scope
* and address issue but without them you're largely left in the dark.
*
*/


/*
* Function to declare an array of predefined size and
* fill it with interger 42 at all elements
*
* Currently doesn't work as intended due to returned the address of a
* locally scoped variable
*/

int *foo() {
    int i;
    int array[SIZE];

    //printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

/*
* Function to declare an array of predefined size and to write
* each element as it's index in the array
*
*/
void bar() {
    int i;
    int array[SIZE];

    //printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}


/*
* Main function to read out foo function's array's elements
*
* Does not currently work due to attempting to read from foo's locally 
* scoped variable
*/
int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
