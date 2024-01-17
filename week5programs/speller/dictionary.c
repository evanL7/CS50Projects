// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// first two letters or 676 (26^2) buckets * 26 letters of the alphabet
// plus occurrences of one letter or 26 buckets, totalling 17,602 buckets plus one since we start from zero
const unsigned int N = (26 * 26) * 26 + 26 + 1;

// Hash table
node *table[N];
static int total_words = 0; // Stores total words in the dictionary, used in size function

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *current;
    current = table[hash(word)]; // Points to the location to start looking

    while (current != NULL)
    {
        if (strcasecmp(current->word, word) == 0) // strcasecmp returns zero if the two arguments are the same, case insensitive
        {
            return true; // Word is in supplied dictionary
        }
        current = current->next; // Move to the next node
    }
    return false; // Exiting the loop implies word is not in supplied dictionary
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int alpha_value1, alpha_value2;
    alpha_value1 = toupper(word[0]) - 'A'; // Stores the first character
    alpha_value2 = toupper(word[1]) - 'A'; // Stores the second character
    if (strlen(word) == 1 || alpha_value2 < 0 || alpha_value2 > 25) // If the second character is an apostrophe, alpha_value2 will be negative
    {
        return (alpha_value1) * ((26 * 26) + (alpha_value1 + 1));
    }
    else
    {
        if (alpha_value1 == 0) // Special case where there are two or more letters and the first letter begins with an 'a'
        {
            return (alpha_value1) * (26 * 26) + (alpha_value2 + 1);
        }
        else
        {
            return (alpha_value1 + 1) * (26 * 26) + (alpha_value2 + 1);
        }
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file;
    file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Failed to open file.\n");
        return false;
    }

    char current_word[LENGTH];
    node *new_node;
    node *temp; // Temporary pointer to hash location
    unsigned int hash_value;

    while (fscanf(file, "%s", current_word) != EOF)
    {
        new_node = (node *) malloc(sizeof(node));
        if (new_node == NULL) // Failed to allocate memory for node
        {
            printf("Failed to create node.\n");
            fclose(file);
            return false;
        }
        strcpy(new_node->word, current_word);
        new_node->next = NULL;

        hash_value = hash(current_word);

        // Rework the nodes to push the node to the corresponding hash value
        temp = table[hash_value];
        new_node->next = temp;
        table[hash_value] = new_node;

        total_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *current;
    node *temp;

    for (int i = 0; i < N; i++) // Iterate through the entire table
    {
        current = table[i];
        while (current != NULL) // Free the linked list at each table index
        {
            temp = current;
            current = current->next;
            free(temp);
        }
        table[i] = NULL; // Prevent dangling pointers
    }
    return true;
}
