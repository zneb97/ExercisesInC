/*
* Ben Ziemann
* 4/9
*
* Basic histogram implementation to practice
* with Glib
*
* For Olin Softsys 2019
*/

#include <stdio.h>
#include <stdlib.h>

#include <glib.h>
#include <string.h>


GHashTable* table;

/*
* Prints out a hash table of words and their ocurrence
*/
void print_table(gpointer key, gpointer value, gpointer user_data){
	char* word = (char*)key;
	int count = GPOINTER_TO_INT(value);
	printf("%s appears %d times.\n", word, count);

}


int main(int argc, char** argv){

	gchar *filename;
	gchar *contents;
	gsize *size;
	gchar** text;
	guint length;
	gchar *curr_word;
	gpointer val_ptr;
	guint *val;
	int i;

	//Use a hashtable for fast, unique lookups later
	table = g_hash_table_new(g_str_hash, g_str_equal);

	//File setup

	filename = "input.txt";
    if(!g_file_get_contents (filename, &contents, &size, NULL)){
    	printf("Not a valid file!\n");
    	return 1;
    }

  	//Build table
    text = g_strsplit(contents," ",-1);
    length = g_strv_length(text);
	for(i = 0; i<length; i++){
    	curr_word = text[i];

    	//Word is in the table already
    	if(g_hash_table_contains(table, curr_word)){

    		//Deal with gtk types
	      	val_ptr = g_hash_table_lookup(table, curr_word);
	      	val = GPOINTER_TO_INT(val)+1;
	      	val_ptr = GUINT_TO_POINTER(val);
	     	g_hash_table_replace(table, curr_word, val_ptr);
    	}

    	//Not in the table yet
    	else{
		    val = 1;
		    val_ptr = GUINT_TO_POINTER(val);
		    g_hash_table_insert(table, curr_word, val_ptr);
	    }
	}

	//Print the table
	g_hash_table_foreach(table, print_table, NULL);

  	//Cleanup
 	g_hash_table_destroy(table);
 	return 0;
 
}