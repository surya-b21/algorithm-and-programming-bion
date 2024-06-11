#include <stdio.h>

void main()
{
    int passes = 0;
    int failures = 0;
    int student = 1;

    while (student <= 10)
    {
        int result;
        printf("Enter Result (1=pass, 2=fail): ");
        scanf("%d", &result);

        if (result == 1) {
            // passes += 1;
            // ++passes;
            passes++;
        } else {
            // failures += 1;
            // ++failures;
            failures++;
        }

        student++;
    }

    printf("Passed : %d\n", passes);
    printf("Failures: %d\n", failures);
    if (passes > 8) {
        printf("Bonus to instructor!");
    }
    
}