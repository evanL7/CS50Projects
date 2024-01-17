#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string words[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    string word = get_string("Word: ");
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(words[i], word) == 0)
        {
            printf("Found!\n");
            return 0;
        }
    }
    printf("Not found.\n");
    return 1;
}