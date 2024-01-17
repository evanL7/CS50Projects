#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string user_input = get_string("Text: "); // Gets user input
    int number_of_letters = count_letters(user_input); // Counts the number of letters from user input
    int number_of_words = count_words(user_input); // Counts the number of words
    int number_of_sentences = count_sentences(user_input); // Counts the number of sentences

    float L = ((float) number_of_letters / number_of_words) * 100.0; // Calculates the average number of letters per 100 words
    float S = ((float) number_of_sentences / number_of_words) * 100.0; // Calculates the average number of sentences per 100 words
    float index = 0.0588 * L - 0.296 * S - 15.8;

    int floor_index = index; // Since we are rounding the grade, I found it easier to floor the index number

    if (index >= 16) // First deal with if the grade level is 16+
    {
        printf("Grade 16+\n");
    }
    else if (index < 1) // Next deal with if the grade is less than Grade 1
    {
        printf("Before Grade 1\n");
    }
    else if (index < floor_index + 0.5) // Deals with rounding the grade
    {
        printf("Grade %i\n", floor_index); // Rounds down the grade level
    }
    else
    {
        printf("Grade %i\n", floor_index + 1); // Rounds up the grade level
    }
}

// This function counts the number of letters in the string argument
int count_letters(string text)
{
    int count = 0; // Keeps track of the number of letters
    for (int i = 0, j = strlen(text); i < j; i++)
    {
        if (isalpha(text[i])) // Checks if the letter is alphabetical
        {
            count ++;
        }
    }
    return count; // Returns the total amount
}

// This function counts the number of words in the string argument
int count_words(string text)
{
    int count = 1; // Start at one because by counting the number of spaces, we dont include the last word
    for (int i = 0, j = strlen(text); i < j; i++)
    {
        if (isspace(text[i])) // Checks if the character is a space
        {
            count++;
        }
    }
    return count;
}

// This function counts the number of sentences in the string argument
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, j = strlen(text); i < j; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') // Checks if the character is specifically a '.', '!', or '?'
        {
            count++;
        }
    }
    return count;
}