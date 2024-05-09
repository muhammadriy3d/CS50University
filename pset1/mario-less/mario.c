#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        //Prompt user for height
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // For each row
    for (int i = 0; i < n; i++)
    {
        // Add space for it to be on right
        for (int s = 0; s < n - i - 1; s++)
        {
            printf(" ");
        }
        // For each column
        for (int j = 0; j <= i; j++)
        {
            //add brick
            printf("#");
        }
        //move to next line
        printf("\n");
    }
}