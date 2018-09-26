#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
 
// Declare a struct with names and scores
typedef struct
{
    char *name;
    int score;
} Entry;

int main()
{
    // Declare identificators for Loops and temporary stores
    int i, j, temp;
    char empo[4];
    
    // Deaclare variables for counting rows in data the file
    int ch = 0;
    int entryCount = 0;

    // Open input file for reading data
    // First column in the file consists size of name
    // Second column in the file consists name
    // Third column in the file consists score
    FILE *input = fopen("C:/C/sorting.txt", "r");
    
    // For counting number of rows in the file
    if (input == NULL) return 0; // Program return 0 if file is empty
    entryCount++;
    while ((ch = fgetc(input)) != EOF) // Program write number of rows to the entryCount
    {
        if (ch == '\n')
        entryCount++;
    }

    // Size of array Entry now equal entryCount
    Entry *entries = malloc(sizeof(Entry) * entryCount);
    
    // Rewind input file for geting data
    rewind(input);

    // Geting names and scores
    for (i = 0; i < entryCount; i++)
    {
        int nameLen;
        fscanf(input, "%i", &nameLen);
        entries[i].name = malloc(sizeof(char) * (nameLen + 1));
        fscanf(input, "%s %i", entries[i].name, &entries[i].score);
    }
    
    // Sorting rows frome input file by scores
    for (i = 0; i < entryCount; i++)
    {
        for (j = 0; j < entryCount; j++)
        {
            if (i == j) continue;
            if (entries[i].score < entries[j].score)
            {
                temp = entries[i].score;
                entries[i].score = entries[j].score;
                entries[j].score = temp;
                strcpy(empo, entries[i].name);
                strcpy(entries[i].name, entries[j].name);
                strcpy(entries[j].name, empo);                
            }
        }
    }

    // Open output file for writing result data
    FILE *output = fopen("C:/C/sorting-result.txt", "w");

    // Writing output file row by row
    for (i = 0; i < entryCount; i++)
    {
        fprintf(output, "%i. %s: %i\n", i + 1, entries[i].name, entries[i].score);     
    }

    // Erase array with names and scores
    for (i = 0; i < entryCount; i++)
        {
            free(entries[i].name);
            free(&entries[i].score);
        }
    free(entries);

    // Closing files
    fclose(input);
    fclose(output);
}