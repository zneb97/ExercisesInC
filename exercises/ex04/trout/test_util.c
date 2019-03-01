/* Ben Ziemann

Use of Minunit asserts to test util.c as part
of HW4 for Software Systems 2019

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "minunit.h"
#include "util.c"


int tests_run = 0;

static char *test1() {
    int cs =0;
    int res = icmpcode_v4(cs);
    char *correct ="network unreachable";
    char *message = ("test%i failed: icmpcode with code %i should return %s", cs+1, cs, correct);
    mu_assert(message, res == correct);
    return NULL;
}

static char *test2() {
    int cs =1;
    int res = icmpcode_v4(cs);
    char *correct ="host unreachable";
    char *message = ("test%i failed: icmpcode with code %i should return %s", cs+1, cs, correct);
    mu_assert(message, res == correct);
    return NULL;
}

static char *test3() {
    int cs =2;
    int res = icmpcode_v4(cs);
    char *correct ="protocol unreachable";
    char *message = ("test%i failed: icmpcode with code %i should return %s", cs+1, cs, correct);
    mu_assert(message, res == correct);
    return NULL;
}

static char *test4() {
    int cs =3;
    int res = icmpcode_v4(cs);
    char *correct ="port unreachable";
    char *message = ("test%i failed: icmpcode with code %i should return %s", cs+1, cs, correct);
    mu_assert(message, res == correct);
    return NULL;
}

static char *test5() {
    int cs =4;
    int res = icmpcode_v4(cs);
    char *correct ="fragmentation required but DF bit set";
    char *message = ("test%i failed: icmpcode with code %i should return %s", cs+1, cs, correct);
    mu_assert(message, res == correct);
    return NULL;
}


/*
* Use minunit to conduct a series of tests to ensure
* util.c's icmpcode_v4 function still has functioning switch
* cases while keeping track of how many tests were run.
*/
static char * all_tests() {
    mu_run_test(test1);
    mu_run_test(test2);
    mu_run_test(test3);
    mu_run_test(test4);
    mu_run_test(test5);
    return NULL;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
