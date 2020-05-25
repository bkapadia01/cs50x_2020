// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"
int count = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 30;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //printf("%s\n", word);
    int lookUp = hash(word);
    node *nodeTmp = table[lookUp];
    while (nodeTmp != NULL)
    {
        if (strcasecmp(nodeTmp->word, word) == 0)
        {
            return true;
        }
        break;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    int sum = 0;
    int word_length = strlen(word);

    for (int i = 0; i < word_length; i++)
    {   
        char words = tolower(word[i]);
        sum += words;
    }

    int index = sum % N;
    return index;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    else
    {
        char diction[LENGTH + 1];
        while (fscanf(file, "%s", diction) != EOF)
        {
            //printf("%s\n", diction);
            node *nodeNew = malloc(sizeof(node));
            if (nodeNew == NULL)
            {
                return false;
            }
            
            strcpy(nodeNew->word, diction);
            int hashIndex = hash(nodeNew->word);
            if (table[hashIndex] == NULL)
            {
                table[hashIndex] = nodeNew;
                nodeNew->next = NULL;
            }
            else
            {
                nodeNew->next = table[hashIndex];
                table[hashIndex] = nodeNew;
            }
            count++;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //printf("%i\n", count);
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *temp = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
