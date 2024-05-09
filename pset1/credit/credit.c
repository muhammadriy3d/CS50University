#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    // Prompt for input
    long n = get_long("CC Number: ");

    // Calculate the length
    int len = 0;
    long cc = n;
    while (cc > 0)
    {
        cc = cc / 10;
        len++;
    }
    // Check whether length is valid
    if (len != 13 && len != 15 && len != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    // Calculate sum
    int sum1 = 0;
    int sum2 = 0;
    long x = n;
    int total = 0;
    int digit1;
    int digit2;
    int mod1;
    int mod2;
    do
    {
        // Remove last digit
        mod1 = x % 10;
        x = x / 10;
        sum1 = sum1 + mod1;
        // Remove second last digit
        mod2 = x % 10;
        x = x / 10;
        // 2 times second last digit and add digits to sum2
        mod2 = mod2 * 2;
        digit1 = mod2 % 10;
        digit2 = mod2 / 10;
        sum2 = sum2 + digit1 + digit2;
    }
    while (x > 0);
    total = sum1 + sum2;
    // Checking Luhn Algorithm
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    // Starting digits
    long ccn = n;
    do
    {
        ccn = ccn / 10;
    }
    while (ccn > 100);
    // Checking starting digits for the card type
    if ((ccn / 10 == 5) && (0 < ccn % 10 && ccn % 10 < 6))
    {
        printf("MASTERCARD\n");
    }
    else if ((ccn / 10 == 3) && (ccn % 10 == 4 || ccn % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (ccn / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}