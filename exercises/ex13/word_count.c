/* Example code for Exercises in C

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

Started with ex-ghashtable-3.c from
http://www.ibm.com/developerworks/linux/tutorials/l-glib/section5.html

Note: this version leaks memory.

*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>

/* Represents a word-frequency pair. */
typedef struct {
    gint freq;
    gchar *word;
} Pair;

/* Compares two key-value pairs by frequency. */
gint compare_pair(gpointer v1, gpointer v2, gpointer user_data)
{
    Pair *p1 = (Pair *) v1;
    Pair *p2 = (Pair *) v2;
    return p1->freq - p2->freq;
}

/* Iterator that prints pairs. */
void pair_printor(gpointer value, gpointer user_data)
{
    Pair *pair = (Pair *) value;
    printf("%d\t %s\n", pair->freq, pair->word);
}


/* Iterator that prints keys and values. */
void kv_printor (gpointer key, gpointer value, gpointer user_data)
{
    printf(user_data, key, *(gint *) value);
}


/* Iterator that adds key-value pairs to a sequence. */
void accumulator(gpointer key, gpointer value, gpointer user_data)
{
    GSequence *seq = (GSequence *) user_data;
    Pair *pair = g_new(Pair, 1); //Allocates, to free later

    //These are referenced directly later so we need to make copies of them here
    pair->word = g_strdup((gchar *) key); //Strings are allocated earlier, dup here
    pair->freq = *(gint *) value;

    g_sequence_insert_sorted(seq,
        (gpointer) pair,
        (GCompareDataFunc) compare_pair,
        NULL);

    // g_free(key); //Remove the origianl string
}

/* Increments the frequency associated with key. */
void incr(GHashTable* hash, gchar *key)
{
    gint *val = (gint *) g_hash_table_lookup(hash, key);

    if (val == NULL) {
        gchar *k = g_strdup(key);
        gint *val1 = g_new(gint, 1); //Allocated 
        *val1 = 1;
        g_hash_table_insert(hash, k, val1);
    } else {
        *val += 1;
    }
    // g_free(key);

}

void free_hash(gpointer key, gpointer value, gpointer user_data)
{
    free(key);
    free(value);
    return;

}

//Was running into seg fault, found a glib function for freeing array
// void free_array(gchar **array, int len){
//     for(int i = 0;i < len; i++){
//         g_free(array[i]);
//     }

//     g_free(array);
//     return;
// }

/*
* Free the pair in the hash. This takes care of the the hash copy of the string
* and the allocated pair itself
*/
void free_pair(gpointer pair){
    Pair *p = (Pair *) pair;
    g_free(p->word);
    g_free(p);
}

int main(int argc, char** argv)
{
    gchar *filename;

    // open the file
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "emma.txt";
    }

    FILE *fp = g_fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        exit(-10);
    }

    /* string array is a(two-L) NULL terminated array of pointers to
    (one-L) NUL terminated strings */
    gchar **array;
    gchar line[128];

    //Different glib function, new_full, that allows for free functions
    GHashTable* hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free); //Allocated

    // read lines from the file and build the hash table
    while (1) {
        gchar *res = fgets(line, sizeof(line), fp);
        if (res == NULL) break;

        array = g_strsplit(line, " ", 0);
        for (int i=0; array[i] != NULL; i++) {
            incr(hash, array[i]);
        }

       g_strfreev(array);
        // free_array(array, sizeof(array)/sizeof(gchar));

    }
    fclose(fp);

    // print the hash table
    g_hash_table_foreach(hash, (GHFunc) kv_printor, "Word %s freq %d\n");

    // iterate the hash table and build the sequence
    //Give it a free function so when destroyed below it is called on each
    //Takes care of string copy
    GSequence *seq = g_sequence_new((GDestroyNotify) free_pair);
    g_hash_table_foreach(hash, (GHFunc) accumulator, (gpointer) seq);

    // iterate the sequence and print the pairs
    g_sequence_foreach(seq, (GFunc) pair_printor, NULL);



    // g_hash_table_foreach(hash, (GHFunc) free_hash, NULL);

    //new_full and its destory functions take care of everything in the hash
    g_hash_table_destroy(hash);
    g_sequence_free(seq);

    return 0;
}
