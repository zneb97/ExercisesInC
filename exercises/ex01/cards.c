/*
* Benjamin Ziemann
* Software Systems
* Last Updated: 1/29
*
* Basic card counting based on
* Head First C's program and refactored
* to practice the basics of C
*/

#include <stdio.h>
#include <stdlib.h>


/*Prompts the user for a card input and truncates answer
* to first two characters
*
* card_name: buffer where result is stored. Valid inputs
* 				are 1 through 10, 'A', 'J', 'Q', and 'K'
*/
void get_card(char *card_name){
	puts("Enter the card name: ");
    scanf("%2s", card_name);
}


/* Returns the numeric value of a card for a game
* of blackjack. 'X' is used to quit the program.
*
* card_name: two characters of user inputted card
*/
int get_value(char card_name[3]){
	int val = 0;
	switch(card_name[0]){
		case'K':
		case'Q':
		case'J':
		    val = 10;
		    break;
		case 'A':
		    val = 11;
		    break;
		default:
		     val = atoi(card_name);
		     if((val<1)||(val>10)){
		     	puts("I don't understand that value!");
		     	break;
		     }
	}
	return val;
}


/* Updates the card counting based on the current
* card's value
*
* val: value of the current card
* count: buffer to keep track of cards counted
*
*/
void update_counter(int val, int *count){
	if ((val>2)&&(val<7)){
    	(*count)++;
	}
	else if (val==10){
		(*count)--;
	}
	printf("Current count: %i\n", *count);
}


/* Prompt users for cards to card count
* until the escape character is input.
*/
int main(){
    char card_name[3];
    int count = 0;
    int val;

    while(1){
    	get_card(card_name);
    	if(card_name[0] =='X'){
    		break;
    	}

    	val = get_value(card_name);
    	update_counter(val, &count);    
    }
    return 0;
}