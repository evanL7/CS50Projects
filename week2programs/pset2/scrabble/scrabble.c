#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2) // Checks if player 1 has the greater score
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2) // Checks if player 2 has the greater score
    {
        printf("Player 2 wins!\n");
    }
    else // Otherwise there is a tie
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int sum = 0; // Keeps track of the amount of points the word is worth
    int count; // Matches the character with the points array
    for (int i = 0; i < strlen(word); i++)
    {
        if (islower(word[i]))
        {
            count = word[i] - 97; // Subtract 97 because ascii value of lowercase 'a' is 97 and we want to match character with above array
            sum += POINTS[count];
        }
        else if (isupper(word[i]))
        {
            count = word[i] - 65; // Subtract 65 because ascii value of uppercase 'A' is 65 and we want to match character with above array
            sum += POINTS[count];
        }
    }
    // printf("%i\n", sum);
    // TODO: Compute and return score for string
    return sum;
}
