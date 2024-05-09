#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Call functions to be read from c
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
//int calculator(float i0, float i1, float i2);

/*int len;
int c;
int s;*/

/* Main program func */
int main(void)
{
    // Prompt input
    string t = get_string("Text: ");

    // Get how much letters are there
    int letters = count_letters(t);
    // Output letters number in the text
    // printf("Letters: %i\n", letters);

    // Get how much words are there
    int words = count_words(t);
    // Output letters number in the text
    // printf("Words: %i\n", words);

    // Get how much words are there
    int sentences = count_sentences(t);
    // Output letters number in the text
    // printf("Sentences: %i\n", sentences);

    // Calculate and solive the problem
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    // printf("%.2f\n", L);
    // printf("%.2f\n", S);

    float index = 0.0588 * L - 0.296 * S - 15.8;
    // printf("%d\n", (int) round(index));

    // Print the grade level
    int average = (int) round(index);
    if (average <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (average >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", average);
    }
}

/* Calculate Letters func */
int count_letters(string text)
{
    // Manual len
    int len = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((islower(text[i]) || isupper(text[i])) && (isalpha(text[i])))
        {
            len++;
        }
    }
    return len;
    // Uncomment the code below to return text using strlen thanks CS50 to make it easy
    // Auto lib len
    // return strlen(text);

    // Next time my custom string counting
    /**
    for (int i = 0; text[i] != '\0'; i++)
    {
           the formila of how to calculate the letters
    @p ... is to convert that text to chars & to do a
           loop for chars and get that loop int
    }
    */
}

/* Calculate Words func */
int count_words(string text)
{
    // Manual len
    int c = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ' && text[i + 1] != ' ')
        {
            c++;
        }
    }
    return c + 1;
    // same as before but we need to make sure that
    // the spaces are not counted and any other
    // special symbols as word e.g: sister-in-low one word.
}

int count_sentences(string text)
{
    int s = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            s++;
        }
    }
    return s;
}
/*
int calculator(float i0, float i1, float i2)
{
    // Call variables
    // Average of letters = L
    float L = i0;
    float W = i1;
    float S = i2;
    return index;
}
*/