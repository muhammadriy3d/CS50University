#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void cipher();
void alphaAdjust(char c, string key);

string s;

int main(int argc, string argv[])
{
    string errors[] = {"Usage: ./substitution key\n", "Key must contain 26 characters.\n", "Key must not contain any repeated characters\n"};
    // Not blank, check if the command-line argument is valid
    if (argc != 2)
    {
        // Print help for user
        printf("%s", errors[0]);
        return 1;
    }

    // Configuration to get a valid KEY from user
    if (strlen(argv[1]) != 26)
    {
        // Print checkValidKey
        printf("%s", errors[1]);
        return 1;
    }
    else
    {
        // For each char
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            // Check whether alpha is there
            if (!isalpha(argv[1][i]))
            {
                // No get error → help
                printf("%s", errors[1]);
                return 1;
            }
            // for each letter that repeated
            for (int j = i + 1; j < strlen(argv[1]); j++)
            {
                // Is rpeated
                if (toupper(argv[1][j]) == toupper(argv[1][i]))
                {
                    // Print help
                    printf("%s", errors[2]);
                    return 1;
                }
            }
        }
        cipher(argv[1]);
        return 0;
    }
}




// Configuration for cipher proccess
void cipher(string key)
{
    // Prompt input
    s = get_string("plaintext: ");
    printf("ciphertext: ");

    // For each char in input
    for (int i = 0; i < strlen(s); i++)
    {
        // Check alpha char
        if (!isalpha(s[i]))
        {
            // Print it as it
            printf("%c", s[i]);
        }
        else
        {
            char x = s[i];
            if (s[i] >= 'a' && s[i] <= 'z')
            {
                alphaAdjust(tolower(x), key);
            }
            else if (s[i] >= 'A' && s[i] <= 'Z')
            {
                alphaAdjust(toupper(x), key);
            }
        }
    }
    printf("\n");
}

// alpha fix: to get the alphabet array value of each plaintext
void alphaAdjust(char c, string key)
{
    // Alpha array string
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // For each alpha
    for (int i = 0; i < strlen(alpha); i++)
    {
        // Check lowercase
        if (c >= 'a' && c <= 'z')
        {
            // Is lowercase & force it
            if (c == tolower(alpha[i]))
            {
                // Print lowercase
                printf("%c", tolower(key[i]));
            }
        }
        // Check uppercase
        else if (c >= 'A' && c <= 'Z')
        {
            // Is uppercase & force it
            if (c == toupper(alpha[i]))
            {
                // Print uppercase
                printf("%c", toupper(key[i]));
            }
        }
    }
}