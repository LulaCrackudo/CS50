#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define LENGTH 45


// function prototypes
void inspect(int arrSize, char *arr[]);

char *table[10];
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 1;
    }
    FILE *file;

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error reading file. (%s)", argv[1]);
        return 1; 
    }

    // initialize counters
    int index = 0, words = 0;

    // read file bytes
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        char word[LENGTH - 1];
        if (isalpha(c))
        { 
            // append current char to the word
            word[index] = c;

            // move to the next char
            index++;

            if (index > LENGTH)
            {
                while ((c = fgetc(file)) != EOF && isalpha(c));
                index = 0;
            }
        }
        else
        {
           // Terminate current word
            word[index] = '\0';
            table[words] = word;

            // Update counter
            // inspect(4, table);
            printf("word adress: %p", &word);
            printf("\ntable = {\n");
            for (int i = 0; i < 4; i++)
            {
                printf("\t[%d] = %s (%p),\n", i, table[i], &table[i]);
            }
            printf("}\n");
            words++; 

            // Prepare for next word
            index = 0; 
        }
    }
    printf("\nWord Count: %d \n", words);
    // inspect(4, table);
    fclose(file);
    return 0;
}

void inspect(int arrSize, char *arr[])
{
    printf("\ntable = {\n");
    for (int i = 0; i < 4; i++)
    {
        printf("\t[%d] = %s (%p),\n", i, table[i], &table[i]);
    }
    printf("}\n");
    return;
}
