#include <stdio.h>

void main()
{
    char string[20];
    int play = 1;

    do {
        printf("Masukkan kata anda : ");
        scanf("%s", &string);

        int charLength = strlen(string);
        int firstIndex = 0;
        int secondIndex = 19;
        int palindrome = 1;
        if (charLength % 2 == 1) {
            firstIndex = ((charLength - 1) / 2) - 1;
            secondIndex = firstIndex + 2;
        } else {
            firstIndex = charLength / 2;
            secondIndex = firstIndex + 1;
        }

        while(firstIndex >= 0) {
            if (string[firstIndex] != string[secondIndex]) {
                palindrome = 0;
                break;
            }

            firstIndex--;
            secondIndex++;
        }

        if (palindrome == 1) {
            printf("This is a palindrome word\n");
        } else {
            printf("This is not a palindrome word\n");
        }

        printf("Do you want try again ? (1=yes, 0=no)");
        scanf("%d", &play);
    } while (play == 1);
}