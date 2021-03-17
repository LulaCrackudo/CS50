// Implements a dictionary's functionality
#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#define N 10000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// counter for words in the dictionary;
unsigned int word_count = 0;

// Hash table
node *hashtable[N];

// Returns true if word is in dictionary else false
bool check(char word[LENGTH + 1])
{
    char lower[LENGTH + 1];

    to_lower(lower, word);

    int h = hash(lower);
    node *cursor = hashtable[h];

    while (cursor != NULL && strcasecmp(cursor->word, lower) != 0)
        cursor = cursor->next;

    return cursor != NULL;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
        hash = (hash << 2) ^ word[i];

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL) return false;

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate space for a new node;
        node *new_node = malloc(sizeof(node));

        // Check if allocation succeeded;
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // Copy word into new node
        strncpy(new_node->word, word, LENGTH + 1);

        // Calculate index for insertion;
        int i = hash(new_node->word);

        // Initializes head to point to hashtable index
        node *head = hashtable[i];

        new_node->next = hashtable[i];
        hashtable[i] = new_node;
        word_count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = hashtable[i];
        node *cursor = head;

        // freeing linked lists
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}

void to_lower(char t[LENGTH + 1], char s[LENGTH + 1])
{
    strcpy(t, s);
    for(int i = 0; t[i]; i++)
        t[i] = tolower(t[i]);

}