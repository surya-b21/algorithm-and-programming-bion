#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findVowel(char *month)
{
    int result = 0;
    char *vowel[] = {"a", "e", "i", "o", "u"};

    for (int i = 0; i < strlen(month); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (month[i] != *vowel[j]) continue;

            result++;
            break;
        }
    }
        

    return result;
}

char** findMonth(char input, int* length)
{
    char **months = malloc(12 * sizeof(char*));
    for (int i = 0; i < 12; i++) {
        months[i] = malloc(10 * sizeof(char));
    }

    char *listMonth[] = {"januari", "februari", "maret", "april", "mei", "juni", "juli", "agustus", "september", "oktober", "november", "desember"};
    int insertedIndex = 0;
    for(int i = 0; i < 12; i++) {
        if (input != listMonth[i][0]) continue;

        months[insertedIndex] = listMonth[i];
        insertedIndex++;
    }

    *length = insertedIndex;

    return months;
}

void main()
{
    char input;
    printf("Masukkan satu huruf A - Z : ");
    scanf("%c", &input);

    int monthLength;
    char **months = findMonth(input, &monthLength);

    if (monthLength < 1) {
        printf("tidak ada bulan yang berawalan dengan huruf %c", input);
        exit(0);
    }

    for (int i = 0; i < monthLength; i++)
    {
        printf("%d. %s\n", i + 1, months[i]);
    }

    int choice;
    printf("Pilih salah satu bulan diatas : ");
    scanf("%d", &choice);

    if (choice >= monthLength) {
        printf("pilihan tidak ditemukan");
        exit(0);
    }
    
    int vowels = findVowel(months[choice - 1]);
    int consonants = strlen(months[choice - 1]) - vowels;

    printf("Jumlah huruf vokal : %d\n", vowels);
    printf("Jumlah huruf konsonan : %d", consonants);
}