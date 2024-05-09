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

    // Print the winner
    // Who get high score win
    if (score1 > score2)
    {
        // P1 WIN!
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        // P2 WIN!
        printf("Player 2 wins!\n");
    }
    else
    {
        // TIE!
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Set default score to 0
    int score = 0;

    // Compute and return score for string

    // Track the words length and letters
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // Check if the word handle upper or lower letters and give it the same value A = a =1
        if (isupper(word[i]))
        {
            // Get points from uppercase
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            // Get points from lowercase
            score += POINTS[word[i] - 'a'];
        }
    }
    return score;
}