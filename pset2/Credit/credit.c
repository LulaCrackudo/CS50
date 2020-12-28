#include <stdio.h>
#include <cs50.h>
#include <string.h>

void validate(char *cardNumber);
void checkFlag(int fNumber, int sNumber);

int main(void)
{
    char *n = get_string("Number: ");
    if ((n[0] - '0') > 3 || (n[0] - '0') < 5)
    {
        validate(n);
        return 0;
    }
    printf("INVALID\n");
    return 1;
}

void validate(char *cardNumber)
{
    int length = strlen(cardNumber) - 1;
    if (length < 12 || length > 16)
    {
        printf("INVALID\n");
        return;
    }
    int result = 0;
    for (int i = length - 1; i >= 0; i -= 2) // calculate the first digits second-to-last
    {
        int n = (cardNumber[i] - 48) * 2;
        while (n)
        {
            // sum the products' digits
            result += n % 10;
            n /= 10;
        }
    }
    printf("result1: %i\n", result);
    for (int i = length; i >= 0; i -= 2) // calculate the remaining "half"
    {
        int n = cardNumber[i] - 48;
        result += n; // add them to the overall result
    }
    printf("result2: %i\n", result);
    if (result % 10 != 0)
    {
        printf("INVALID\n");
        return;
    }
    int fstNumber = cardNumber[0] - 48;
    int scnNumber = cardNumber[1] - 48;
    checkFlag(fstNumber, scnNumber);
    return;
}

void checkFlag(int fstNumber, int scnNumber)
{
    if (fstNumber == 3 && (scnNumber == 4 || scnNumber == 7))
    {
        printf("AMEX\n");
        return;
    }
    if (fstNumber == 4)
    {
        printf("VISA\n");
        return;

    }
    if (fstNumber == 5 && (scnNumber <= 5 && scnNumber >= 1))
    {
        printf("MASTERCARD\n");
        return;
    }
    printf("INVALID\n");
    return;
}