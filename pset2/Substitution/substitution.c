#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void encode(char *key);

int main(int argc, char *argv[])
{
    char *key = argv[1];

    if (key == NULL || argv[2] != NULL) // if no cl arguments have been passed
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    for (int i = 0; key[i] != '\0'; i++) // iterates over every char from the first argument passed in the command line
    {
        if (isalpha(key[i]) == 0) // checks if there are any not-alphabetical char
        {
            printf("Usage: ./substitution key\n");
            return 1; 
        }

        for (int j = 0; key[j] != '\0'; j++) // iterates over every char again??
        {
            if (key[i] == key[j] && i != j) // check for duplicates
            {  
                printf("%c, %c\n", key[i], key[j]);
                printf("Your key has duplicated chars\n");
                return 1; 
            }
        }  
    }
    if (strlen(key) != 26) // check the length of the key
    {
        printf("key must contain 26 characters\n");
        return 1;
    }
    encode(key);
}

void encode(char *key)
{
    char *plaintext = get_string("plaintext: ");
    for (int i = 0, s = strlen(plaintext); i < s; i++)
    {
        if (isalpha(plaintext[i]) != 0)
        {
            if (plaintext[i] < 97) // if the char is uppercase (less then ascii for lowercase A)
            {
                plaintext[i] = toupper(key[plaintext[i] - 65]);  
            }
            else
            {
                plaintext[i] = tolower(key[plaintext[i] - 97]);   
            }
            
        }
    }
    printf("ciphertext: %s\n", plaintext);
}