#include <cs50.h>
#include <string.h>
#include <stdio.h>


int main(void)
{
    string word = get_string("Word: ");
    int answer = 0;

    for (int i = 0, length = strlen(word); i < length; i++)
    {
        // printf("Answer: %i\n", answer);
        if (word[i] > word[i+1] && word[i+1] != '\0')
        {
            // printf("%i %i\n", word[i], word[i+1]);
            answer = 1;
        }
    // printf("Answer: %i\n", answer);
    }
    if (answer == 0)
    {
        printf("Yes.\n");
    }
    else
    {
        printf("No.\n");
    }
}