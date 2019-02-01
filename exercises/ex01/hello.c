#include <stdio.h>

int main() {
	int x = 5;
	int y = x+1;
    printf("%i\n", y);
    return 0;
}


/*
*Q1 - Two lines are added:
* subq	$16, %rsp
* movl	$5, -4(%rbp)
* These appear to allocate memory and then write the value
* that memory location
*
* Q2 - It appears to skip allocating and writing x's value
* probably because it is never used.
* It also seems to run more functions(?), probably to check over the
* program to determine where variables like X do not need be used.
*
* Q3 - When optimized it appears to write x's value directly into the
* print statement, rather than write the value to an address
*
* Q4 - Again when optimized it appears put y's values directly
* value into the print statement as opposed to allocating and writing
* for x's and y's values.
*
* Q5 - Optimization seems to precompute any variables whose value would
* be know based on other variables or values used in setting their value.
* If a variable is not used as part of something being shown outside the scope
* of the function it also appears to purposely neglect allocating and writing
* values for that variable.
*
*
*/