#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
//char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Check blank inputs
    if (argc != 2)
    {
        // Set help
        printf("Usage: ./caeser key\n");
        return 1;
    }
    // Configuration for our program
    if (only_digits(argv[1]) == false)
    {
        // Configuration for invalid inputs → Errors
        printf("Usage: ./caeser key\n");
        return 1;
    }
    else if (only_digits(argv[1]) == true)
    {
        // Get our KEY and convert that key into an int'eger
        int k = atoi(argv[1]);

        // Prompt input for the usr → plaintext and store it to s string
        string s = get_string("plaintext: ");
        printf("ciphertext: ");

        // Configuration for valids inputs and the system
        for (int j = 0; j < strlen(s); j++)
        {
            // CHECK FOR UPPERCASES
            if (isupper(s[j]))
            {
                // KEEP ALL WORDS CABITAL LETTER
                printf("%c", (s[j] - 'A' + k) % 26 + 65);
            }
            else if (islower(s[j])) //CHECK FOR LOWERCASES
            {
                // FORCE IT TO UPPERCASE USING ACSII
                printf("%c", (s[j] - 'a' + k) % 26 + 97);
            }
            else // CHECK FOR RANDOM CHARACTER
            {
                // PRINT IT AS IT
                printf("%c", s[j]);
            }
        }
        // Set new line → exit - 0 → success
        printf("\n");
        return 0;
    }
}

// KEYS TYPE IS DIGIT
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return isdigit(*s);
}

/* char rotate(char c, int n)
{
    for (int j = 0; j < strlen(g); j++)
    {
        // CHECK FOR UPPERCASES
        if (isupper(g[j]))
        {
            // KEEP ALL WORDS CABITAL LETTER
            printf("%c", (g[j] - 'A' + k) % n + 65);
        }
        //CHECK FOR LOWERCASES
        else if (islower(g[j]))
        {
            // FORCE IT TO UPPERCASE USING ACSII
            printf("%c", (g[j] - 'a' + k) % n + 97);
        }
        // CHECK FOR RANDOM CHARACTER
        else
        {
            // PRINT IT AS IT
            printf("%c", g[j]);
        }
    }
    // Set new line → exit - 0 → success
    printf("\n");
    return *g;
} */