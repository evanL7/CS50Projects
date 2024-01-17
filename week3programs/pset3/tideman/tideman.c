#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int is_circle(int start, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1; // Subtracting the program call ./filename
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }

        }
        record_preferences(ranks);

        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false; // Exiting the loop implies an invalid vote
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[i][j] = 0; // Set zero for individuals against themselves
            }
            else
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j <candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int counter = 0;
    pair temp_pair = pairs[0];
    pair current_strongest;

    for (int i = 0; i < pair_count; i++)
    {
        current_strongest = pairs[i]; // Arbitrarily selecting the first element for baseline
        temp_pair = pairs[i];

        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[current_strongest.winner][current_strongest.loser])
            {
                current_strongest = pairs[j]; // May need some debugging
                counter = j;
            }
        }
        if (i + 1 == pair_count)
        {
          break;
        }
        pairs[counter] = temp_pair;
        pairs[i] = current_strongest; // Sort the strongest to the leftmost position
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!is_circle(pairs[i].winner, pairs[i].loser))
        {
            // Lock the pair unless it makes a circle
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int flag = 1;

    for (int i = 0; i < candidate_count; i++)
    {
        flag = 1;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == 1)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

int is_circle(int start, int loser)
{
    if (loser == start)
    {
        return 1;
    }
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[loser][i])
            {
                if (is_circle(start, i))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}