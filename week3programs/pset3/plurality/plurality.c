#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) // The command line arguments are the candidates
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int num_iter = candidate_count; // Calculates the number of iterations
    for (int j = 0; j < num_iter; j++)
    {
        if (strcmp(name, candidates[j].name) == 0) // Compares names
        {
            candidates[j].votes++;
            return true;
        }
    }
    return false; // If loop exited, then invalid ballot
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int greatest_votes = 0;
    int num_iter = candidate_count;

    for (int k = 0; k < num_iter; k++) // Loop to find the candidate(s) with the most votes
    {
        if (candidates[k].votes > greatest_votes)
        {
            greatest_votes = candidates[k].votes;
        }
    }

    for (int l = 0; l < num_iter; l++) // Loop to print the candidate(s) with the most votes
    {
        if (candidates[l].votes == greatest_votes)
        {
            printf("%s\n", candidates[l].name);
        }
    }
    return;
}