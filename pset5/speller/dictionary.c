// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Function prototypes
int hash_index(char *hash_this);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// counter for words in the dictionary;
unsigned int word_count = 0;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *hashtable[N] = {NULL};

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int len = strlen(word);
    char copy[len];
    for (int i = 0; i < len; i++)
    {
        copy[i] = tolower(word[i]);
    }
    copy[len] = '\0';

    int h = hash(copy);

    node *cursor = hashtable[h];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, copy) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error reading file.");
        return false;
    }
    char word[LENGTH - 1];

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
        strcpy(new_node->word, word);
        
        // Calculate index for insertion;
        int i = hash(new_node->word);

        // Initializes head to point to hashtable index/bucket
        node *head = hashtable[i];

        // Insert nodes at the beggining of the linked list
        if (head == NULL)
        {
            hashtable[i] = new_node;
            new_node->next = NULL;
            word_count++;
        }
        else
        {
            new_node->next = hashtable[i];
            hashtable[i] = new_node;
            word_count++;
        }
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

