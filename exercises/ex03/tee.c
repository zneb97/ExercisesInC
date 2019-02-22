/**
* Ben Ziemann
* Implementation of the "tee" command
* for Software Systems Spring 2019 HW3
* 
* Reflection: 
* Once I stopped being overwhelmed and made the mental call to stop diving down the rabbit hole of terms and just try something
* things went a lot of smoother. Now with more confidence on my side I made a quick list of the componenets I needed and tried to
* avoid Googling everything that I didn't immediately know to avoid sidetracking/bogging myself down in uncessary mountains of information,
* that while interesting, proved unncessary for the task or would paralyze me thinking there is more to this than
* there actually was. I think the best thing I did for myself was spend 10 or so minutes just trying out the 'tee' command
* in my terminal to understand what everything did.
*
* I think the biggest thing that slowed me down was immediately getting overwhelmed 
* by trying to dive too deep into what every word meant on the command page and trying to think about everything
* all at once rather than just try one thing at a time.
*
* Next time I will: -Start the assignment earlier so the initial feeling of overwhelmingness is so paralyzing
*				    -Start the assignment earlier so I can try the optional part
*				    -Try going at it earlier on, it's unlikely I will be fully prepared no matter how much reading I do, 
						especially in an assignment where we are supposed to be learning new things anyways
*
* My code differs from the professional code in that they use a lot more libraries and header files, probably
* to speed operations up and allow for more and complex outputs. 
* Additionally they also use ALOT more error checking (see my non-implementation of -p), taking
* advantage of enumeration to make this clean. It's also just generally cleaner. 
* Finally they have a full implementation :P
*
*/

#include <stdio.h>
#include <stdlib.h>
//For getopt and arugment parsing
#include <unistd.h>

#define MAX_FILES 5
#define MAX_BUFFER 100

/**
* Implementation of 'tee' command
*
* int argc - number of arguments
* char *argv[] - the arguments, includes ./ and any flags
*/

int main (int argc, char *argv[]){	
	int argument;
	int i;
	short argOffset;
	//0-overwite files, 1-append to files
	short appending = 0;
	char *input[MAX_BUFFER];
	FILE *myFiles[MAX_FILES];

	//Error check
	if(argc > MAX_FILES+1){
		printf("Too many files and flags! Please use one flag at most and  %i files or less!\n", MAX_FILES);
		return 1;
	}

	//Go through arguments
	//Wondered about --arguments (help, version), didn't really look into them b/c time constraints
	//Instead just made them characters
  	while((argument = getopt(argc, argv, "aiphv")) != -1){
     	switch(argument){
          	case 'a':
            	appending = 1;
            	break;
            case 'i':
	            //Optional
	            printf("Optional - not implemented.\n");
            	return 1;
            	break;
            case 'p':
	            printf("Not implemented\n");
            	return 1;
            	break;
            case 'h':
            	printf("Use CTRL+D to end the program.\n");
           		printf("Use -a [FILE] to append to given files.\nUse no flags [FILE] to overwrite given files.\n");
           		printf("Use -v to see the creator info and version.\nUse -h to see this screen again.\n");
           		printf("Flag -p is not implemented. \nFlag -i is not implemented.\n");
            	return 1;
            	break;
          	case 'v':
           		printf("This tee command implementation was made by Ben Ziemann for Software Systems Spring 2019.\nLast updated 2/22/19.\n");
            	return 1;
            	break;
          	default:
            	printf("Not a valid argument. Please see -h for help.");
            	return 1;
      	}
    }

    //Open file(s) with correct intent
    //Program assumes user only use 1 flag max (-a), otherwise none
    //Real tee command only uses last flag
    //./tee and whether appending affects # of arguments
	if(appending){
		argOffset=2;
		for(i=0; i < argc-argOffset; i++){
  			myFiles[i] = fopen(argv[i+argOffset], "a+");
  		}
	}
	else{
		argOffset=1;
		for(i=0; i < argc-argOffset; i++){
  			myFiles[i] = fopen(argv[i+argOffset], "w+");
  		}
  	}

  	printf("Pleae end the program with CTRL+D, NOT CTRL+C to properly save input.\n");

    //Read user input, write to file(s)
    //Kill with CTRL-D
    while(fgets(input, MAX_BUFFER, stdin) != NULL){
    	fputs(input, stdout);
	    for(i = 0; i < argc-argOffset; i++){
	      fputs(input, myFiles[i]);
	    }
    }

    //Cleanup
    for(i=0; i<argc-argOffset; i++){
    	fclose(myFiles[i]);
    }
    printf("Files written!\n");
  	return 0;
}