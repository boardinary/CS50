// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include <strings.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Dictionary word count
unsigned int wordcount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Initialize index and call hash() to retrieve
    unsigned int index = hash(word);

    // Initialize n
    node *n;

    // Set n equal to first node
    n = table[index];

    while (n != NULL)
    {
        // Check for match
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }

        // Advance to next node
        n = n->next;

    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index;

    // Very simple hash function first letter of word is 0 - 26

    index = word[0] - 65;

    if (index > 31)
    {
        index = index - 32;
    }
    //printf("%i\n", index);
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // initialize dictionary pointer
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    // Initialize new word variable
    char word[LENGTH + 1];

    // Initialize new node
    node *n = NULL;

    // Initialize index for array of linked lists
    int index;

    while (fscanf(dict, "%s", word) != EOF)
    {
        // Retrieve hash index
        index = hash(word);

        // Allocate memory for new node
        n = malloc(sizeof(node));

        if (n == NULL) // Return false if malloc fails
        {
            return false;
        }

        // Copy word into new node
        strcpy(n->word, word);

        // Assign head node address to new node address
        n->next = table[index];

        // Make new node the new head of the linked list
        table[index] = n;

        // Keep track of dictionary size while loading
        wordcount++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
    //return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Initialize cursor and tmp nodes
    node *cursor;
    node *tmp;

    // if (cursor == NULL || tmp == NULL)
    // {
    //     return false;
    // }

    // Iterate through array to free each linked list
    for (int i = 0; i < N; i++)
    {
        // Set cursor and tmp nodes equal to first node in array element
        cursor = table[i];
        tmp = table[i];

        // Traverse through linked list to free each node
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    free(cursor);

    return true;
}
