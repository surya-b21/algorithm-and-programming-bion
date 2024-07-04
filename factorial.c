#include <stdio.h>

void main()
{
    int loop = loopFactorial(15);
    printf("Factorial dari 15 adalah : %d\n", loop);
    
    int recursive = recursiveFactorial(15);
    printf("Factorial dari 5 adalah : %d\n", recursive);
}

int loopFactorial(int input)
{
    for (int i = input; i >= 2; i--) {
        input *= (i - 1);
    }

    return input;
}

int recursiveFactorial(int input)
{
    if (input == 1) return 1;
    
    return input * recursiveFactorial(input - 1);
}