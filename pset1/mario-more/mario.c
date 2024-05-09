#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        // Prompt user for height
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    //For each rows
    for (int i = 0; i < n; i++)
    {
        //For each space in left of hashe
        for (int s = 0; s < n - i - 1; s++)
        {
            //Space
            printf(" ");
        }

        //For each column
        for (int j = 0; j <= i; j++)
        {
            //Blocks
            printf("#");
        }

        //Space between two pyramid
        printf("  ");

        //Second pyramid
        for (int j2 = 0; j2 <= i; j2++)
        {
            //Block
            printf("#");
        }

        //Move to next line
        printf("\n");
    }
}