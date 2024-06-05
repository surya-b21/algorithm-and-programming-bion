#include <stdio.h>

void main()
{
    int play = 1;

    do {
        int myNumber = rand() % 1000 + 1;
        int guess;
        printf("I have a number between 1 and 1000\nCan you guess my number?\n");
        printf("Please type your first guess :");
        scanf("%d", &guess);

        while(guess != myNumber) {
            if (guess < myNumber) {
                printf("To low. ");
            } else {
                printf("To high. ");
            }

            printf("Try again.");
            scanf("%d", &guess);
        }

        printf("Wow! you nailed it!\n");

        printf("Do you want try again ? (1=yes, 0=no)");
        scanf("%d", &play);
    } while (play == 1);
}