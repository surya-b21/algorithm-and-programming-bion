#include <stdio.h>

void main()
{
    int checkedNumber = 1;

    while(checkedNumber <= 100) {
        int prime = 1;
        for (int i = 2; i < checkedNumber; i++) {
            if (checkedNumber % i == 0) {
                prime = 0;
                break;
            }
        }
        
        if (prime == 1) {
            printf("%d ", checkedNumber);
        }

        checkedNumber++;
    }
}