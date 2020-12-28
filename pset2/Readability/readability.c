#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float calc_readability(char *text);
int count_chars(char *text);
int count_words(char *text);
int count_sentences(char *text);

float sentencesPerHundredWords(int words, int sentences );
float lettersPerHundredWords(int words, int letters );

int main(void)
{
    char *text = get_string("Text: ");
    int grade = calc_readability(text);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (grade > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    printf("Grade %i\n", grade);
    return 0;
}

float calc_readability(char *text)
{
    int charCount = count_chars(text);
    int wordCount = count_words(text);
    int sentCount = count_sentences(text);
    printf("Chars: %i\nWords:%i\nSentences:%i\n", charCount, wordCount, sentCount);

    float L = lettersPerHundredWords(wordCount, charCount);
    float S = sentencesPerHundredWords(wordCount, sentCount);

    float grade = 0.0588 * L - 0.296 * S - 15.8;
    return round(grade);
}

int count_chars(char *text)
{
    int chars = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalnum(text[i]) != 0)
        {
            chars++;
        }
    }
    return chars;
}

int count_words(char *text)
{
    int words = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isspace(text[i]) && !isspace(text[i+1]) && !isspace(text[i-1]))
        {
            words++;
        }
    }
    return words + 1;
}

int count_sentences(char *text)
{
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (ispunct(text[i+1]) == 0 && (text[i] == '?' || text[i] == '.' || text[i] == '!'))
        {
            printf("%i\n", text[i]);  
            sentences++;
        }
    }
    return sentences;
}

float sentencesPerHundredWords(int words, int sentences )
{
    return (100.0 * sentences) / words;
}

float lettersPerHundredWords(int words, int letters )   
{
    return (100.0 * letters) / words;
}