#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool only_alpha(string text);
char rotate(char letter, char new_alphabet[26]);

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2) // Checks the number of arguments the user has entered
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Checks if the user entered 26 letters or there are no special characters
    else if (strlen(argv[1]) != 26 || only_alpha(argv[1]) == false)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    char new_alphabet[26]; // Stores an array of the user's alphabet
    int j = strlen(argv[1]);

    // This loop changes the string to an array which holds the new alphabet from the user's input
    for (int i = 0; i < j; i++)
    {
        new_alphabet[i] = tolower(argv[1][i]); // To avoid case sensitivity, we change the entire string to lowercase
    }

    // This loop checks if all the characters in the user's alphabet are unique
    for (int x = 0; x < 26; x++)
    {
        for (int y = 0; y < 26; y++)
        {
            if (new_alphabet[x] == new_alphabet[y] && x != y) // Checks if two letters are the same not including themselves
            {
                printf("Letters are not unique.\n");
                return 1;
            }
        }
    }

    string user_input = get_string("plaintext:  "); // Get user input

    printf("ciphertext: ");
    for (int k = 0, l = strlen(user_input); k < l; k++) // Loops through user's input to create the ciphertext
    {
        printf("%c", rotate(user_input[k], new_alphabet));
    }
    printf("\n");
}

// This function checks if the user's input are all characters of the alphabet
bool only_alpha(string text)
{
    for (int i = 0, j = strlen(text); i < j; i++)
    {
        if (isalpha(text[i]) == 0) // Checks if character is of the alphabet
        {
            return false;
        }
    }
    return true;
}

// This function changes the user's input with their associated alphabet correspondence
char rotate(char letter, char new_alphabet[26])
{
    char new_letter;
    int num_of_alpha;
    if (isalpha(letter))
    {
        if (isupper(letter)) // Deals with uppercase letters
        {
            num_of_alpha = letter - 65; // Works from zero to align position in alphabet
            new_letter = new_alphabet[num_of_alpha] - 32; // subtract 32 to get the uppercase letter
        }
        else // Deals with lowercase letters
        {
            num_of_alpha = letter - 97; // Works from zero to align position in alphabet
            new_letter = new_alphabet[num_of_alpha];
        }
        return new_letter;
    }
    return letter; // If character is not of the alphabet, just return the character unchanged
}