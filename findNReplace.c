#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

void writingFile(char *string, FILE *fptr, char *filename)
{
    fptr = fopen(filename, "w");

    fputs(string, fptr);

    fclose(fptr);
}

char* findAndReplace(char *word, FILE *fptr, char *change)
{
    char *string = malloc(MAX_CHAR * sizeof(char));
    fptr = fopen("file.txt", "r");
    fgets(string, MAX_CHAR, fptr);
    fclose(fptr);

    int i = 0;
    char **arr = (char**)malloc(20 * sizeof(char*));
    char *s = strtok(string, " ");
    while(s != NULL) {
        arr[i++] = s;
        s = strtok(NULL, " ");
    }

    int index = 1;
    char *result = malloc(MAX_CHAR * sizeof(char));
    strcpy(result, arr[0]);
    while(arr[index] != NULL) {
        if (strcmp(arr[index], change) == 0) {
            arr[index] = word;
        }

        strcat(result, " ");
        strcat(result, arr[index]);
        index++;
    }

    return result;
}

void main()
{
    char string[MAX_CHAR];
    printf("Masukkan kalimat : ");
    gets(string, MAX_CHAR, stdin);

    char find[3];
    printf("Masukkan kata yang akan diganti : ");
    gets(find, 3, stdin);
    find[strcspn(find, "\n")] = 0;

    char word[10];
    printf("Masukkan kata pengganti : ");
    gets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = 0;

    FILE *fptr;

    writingFile(string, fptr, "file.txt");

    char *result = findAndReplace(word, fptr, find);
    writingFile(result, fptr, "file-output.txt");
}