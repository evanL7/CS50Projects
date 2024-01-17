#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string number);
char rotate(char letter, unsigned long long key);

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2) // Condition checks if 1 or, 3 or more arguements passed in.
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Condition checks if the argument passed in is only digits
    else if (only_digits(argv[1]) == false) // Another condition used to avoid segmentation fault error.
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    unsigned long long key = atol(argv[1]); // Converts string to long integer in case user enters a very long integer
    string user_input = get_string("plaintext:  "); // Accepts the user's string
    printf("ciphertext: ");

    for (int i = 0, j = strlen(user_input); i < j; i++) // Loops through the user's string to encrypt their text
    {
        printf("%c", rotate(user_input[i], key)); // Prints characters one by one
    }
    printf("\n");
}
// This function checks if the user's command line argument is a valid number
bool only_digits(string number)
{
    for (int i = 0, j = strlen(number); i < j; i++) // Loops through entire string to see if entire input are digits
    {
        if (isdigit(number[i]) == 0)
        {
            return false;
        }
    }
    return true; // If loop exited, we know the user entered only digits
}
// This function shifts the letter by the key
char rotate(char letter, unsigned long long key)
{
    char new_letter;

    if (isalpha(letter) != 0) // Checks if the character is an alphabetical letter
    {
        if (isupper(letter)) // Deals with uppercase letter
        {
            letter -= 65;
            new_letter = (letter + key) % 26;
            new_letter += 65;
        }
        else // Deals with lowercase letter
        {
            letter -= 97;
            new_letter = (letter + key) % 26;
            new_letter += 97;
        }
        return new_letter;
    }
    return letter; // Doesn't change character if the character is not alphabetical
}