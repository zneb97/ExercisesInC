/*
* Ben Ziemann's Adder Program
*
* Part of Software Systems Spring 2019
* Exercises in C #2
* 2/9/18
*
* Takes user inputted numbers, stores, and sums them
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NUMS 5 //maximum number of ints to add
#define BUFFER 128 //Input character limiting


/*
* Function to sum a given array
*
* nums_to_add: Allocated array of numbers to be summed
* count: Length of the array actually used
*/
int sum_array(int nums_to_add[], int count){
	int i;
	int sum = 0;

	for(i=0; i<count; i++){
		sum += nums_to_add[i];
	}
	return sum;
}


/*
* Converts a string to an int and check validity
*
* user_num_str: string to be converted to int
*/
int check_num(char* user_num_str){
	int val;
	val = atoi(user_num_str);
	//NaN
	if(val == 0){
		printf("Not a number.\n");
		return 1;
	}
	//No error
	else{
		return 0;
	}
}


/*
* Prompts user for input of numbers to sums and sums them
*
* Can be stopped with CTRL+D. Non integer inputs will stop the program
*/
int main(){
    int count;
    count = 0;
    int fail_flag;
    fail_flag = 0;

    int user_num;
    int sum;
    char user_num_str[BUFFER];
    int nums_to_add[MAX_NUMS];
   

    printf("You can sum up to %i numbers.\n", MAX_NUMS);
    printf("You can use CTRL+D to quit.\n");
    printf("Please do not enter 0.\n");
	while(count < MAX_NUMS){

		//Prompt for input
		printf("Enter the next number to be sum: \n");
		//Had problems with CTRL+D not being end of field so put it here
	    if(fgets(user_num_str, BUFFER, stdin)==NULL){
	    	printf("Ending summation.\n");
	    	fail_flag = 2;
	    }
	    else{
	    	fail_flag = check_num(user_num_str);
	    }
	    //Invalid input
	    if(fail_flag >= 1){
	    	break;
	    }

	    //Valid input	
	    user_num = atoi(user_num_str);
	    nums_to_add[count] = user_num;
	    count++;
	}

	//If ended by array limit
	if(count>=MAX_NUMS){
		printf("Max number of integers reached.\n");
		printf("Please see Ben Z to raise your limit.\n");
		printf("Calculating sum now...\n");
	}

	//If ended by error
	else if(fail_flag == 1){
		printf("There was an error in your input.\n");
		printf("Calculating sum of valid numbers...\n");
	}

	sum = sum_array(nums_to_add, count);
	printf("Your sum is: %i\n", sum);

    return 0;
}