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

int main(int argc, string argv[])
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
    // search for the candidate and update their votes
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // is candidate get vote
        if (strcmp(candidates[i].name, name) == 0)
        {
            // increase the votes for the candidate
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}
// Print the winner (or winners) of the election
void print_winner(void)
{
    // search in every candidate and demetermine who is get the most votes
    int isHigh = 0;
    // start the proccess to search every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // compare who get the most
        if (candidates[i].votes > isHigh)
        {
            // update the higher vote and put it on the int'eger isHigh
            isHigh = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // For who get most votes equal to higher one
        if (candidates[i].votes == isHigh)
        {
            // Print winner
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}