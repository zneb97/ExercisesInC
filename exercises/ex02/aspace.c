/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

int stack_grows_down(){
	int test_var = 2;
	printf ("Address of the new local variable is %p\n", &test_var);
	int *add1 = malloc(16);
  	int *add2 = malloc(16);
  	printf ("Address of add1 is %p\n", add1);
  	printf ("Address of add2 is %p\n", add2);
  	if (add1<add2){
  		return 1;
  	}
  	else{
  		return 0;
  	}

}

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    void *p2 = malloc(128);
    char *s = "Hello, World";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("p2 points to %p\n", p2);
    printf ("s points to %p\n", s);

    printf("Does the stack grown down? %i\n", stack_grows_down());

   	void *test0 = malloc(7);
   	void *test1 = malloc(7);
    printf("Test 0 address: %p\n", test0);
    printf("Test 1 address: %p\n", test1);
    return 0;
}
