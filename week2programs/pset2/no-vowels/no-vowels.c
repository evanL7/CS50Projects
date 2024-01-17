// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string text);

int main(int argc, string argv[]) // Using command line arguments instead of get_int, get_string because of efficiency (?)
{
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    printf("%s", replace(argv[1])); // Prints out the new string
    printf("\n");

}

string replace(string text)
{
    for (int i = 0, j = strlen(text); i < j; i++) // Don't use strlen inside of second argument because it does more work
    {
        switch (text[i]) // Obtains the current loops' letter
        {
            case 'a': // If it's the case that the character is an 'a'
                text[i] = '6';
                break;
            case 'e': // If it's the case that the character is an 'e'
                text[i] = '3';
                break;
            case 'i': // ditto
                text[i] = '1';
                break;
            case 'o': // ditto
                text[i] = '0';
                break;
            default:
                break;
        }
    }
    return text; // Returns the new word
}
