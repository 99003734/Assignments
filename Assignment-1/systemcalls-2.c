#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE * sample_File;
    char path[100];

    char ch;
    int i=0;
    int characters=0, words=0, lines=0;

    printf("Enter the file path: ");
    scanf("%s", path);

    sample_File = fopen(path, "r");

    if (sample_File == NULL)
    {
        printf("Please enter the valid text file.\n");

        exit(0);
    }


    
    while ((ch = fgetc(sample_File)) != EOF)
    {
        characters++;
        i++;

        
        if (ch == '\n' || ch == '\0')
            lines++;

       
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
            words++;
    }

    if (i > 0)
    {
        words++;
        lines++;
    }

    printf("\n");
    printf("Number of characters = %d\n", characters);
    printf("Number of words      = %d\n", words);
    printf("Number of lines      = %d\n", lines);

    fclose(sample_File);

    return 0;
}
