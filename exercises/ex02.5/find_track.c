/* 
Ben Ziemann
HW2.5 for Software Systems
Implementation of simple regex pattern matching for
a track list

Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i+1, tracks[i]);
        }
    }
}


// Finds all tracks that match the given pattern.
//
// Prints track number and title.
// pattern: a valid regex expression
// Non zero return values indicate error
int find_track_regex(char pattern[])
{
  int count;
  count = 0;
  regex_t reg;

  //Error check
  //Identify if the given string is a valid regex pattern
  //pattern is written into reg
  if (regcomp(&reg, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
      printf("Invalid regular expression.\n");
      return 1;
  }

  //Search tracks for match
  for (int i=0; i<NUM_TRACKS; i++) {
      //Compare each track name with pattern stored in reg
      if (regexec(&reg, tracks[i], 0, NULL, 0)==0) {
          printf("Track %i: '%s'\n", i+1, tracks[i]);
          count++;
      }
  }

  //Successful matching
  if(count>=1){
    printf("%i tracks found.\n", count);
    return 0;
  }

  //Successful regex, no match
  else{
    printf("No tracks found.\n");
    return 2;
  }

  regfree(&reg); //Free up memory
}


// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}


int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
