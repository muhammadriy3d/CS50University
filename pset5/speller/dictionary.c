// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "dictionary.h"

// Default count words
unsigned int count_words = 0;

// Prototypes
unsigned int size(void);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// N = 26 this is A to Z
const unsigned int N = 20000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int word_index = hash(word);

    // initialize cursor to first node in the linked list
    node *cursor = table[word_index];

    // while loop to iterate until NULL
    // NULL is the one with no pointer
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true; // word is found
        }
        // set the cursor to the next node in the linked list
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int roll_sum = 0;
    unsigned int squared = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        squared = pow(toupper(word[i]), 2);
        if (i == round(strlen(word) / 2))
        {
            roll_sum = roll_sum + round(sqrt(roll_sum)) + 17;
        }
        roll_sum = squared + roll_sum + 47;
    }
    return roll_sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dict_open = fopen(dictionary, "r");
    //printf("pointer to memory address of the memory card %p \n", input_memory_card);
    if (dict_open == NULL)
    {
        printf("Could not open the dictionary file.\n");
        return false;
    }
    else if (dict_open != NULL)
    {
        char buffer[LENGTH + 1];
        int hash_index = 0;
        while (fscanf(dict_open, "%s", buffer) != EOF)
        {
            node *n = malloc(sizeof(node));
            // check that the memory initialized ok
            if (n == NULL)
            {
                return false;
                break;
            }
            else if (n != NULL)
            {
                // copy the word into the word portion of the node
                strcpy(n->word, buffer);
                // set address to NULL
                n->next = NULL;

                // get the hash number
                hash_index = hash(buffer);
                // if nothing is there equal the first entry to the new node
                if (table[hash_index] == NULL)
                {
                    table[hash_index] = n;
                }
                else if (table[hash_index] != NULL)
                {
                    // set the new node address to the first element index position
                    n->next = table[hash_index];
                    // set the head of the linked list to the previously inserted node
                    table[hash_index] = n;
                }

                // count words
                count_words++;
            }
        } // end while loop
        fclose(dict_open);
        return true;
    }
    else
    {
        return false;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // summed count words whilst loading
    return count_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // loop along the index positions
    for (int i = 0; i < N; i++)
    {
        // set temp and cursor to first index position
        node *temp = table[i];
        node *cursor = table[i];

        while (temp != NULL)
        {
            // set cursor to next
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}