#include <time.h>
#include <stdio.h>

int main(void) {
    time_t start, end;

    // Save user and CPU start time
    time(&start);
    time(&end);
    // Perform operations
    while ((end - start) <= 10)
    {
        printf("%d secs\n", (int)(end - start));
        sleep(1);
        time(&end);
    }
    

    // Save end time
    // time(&end);

    // printf("user : %d secs\n", (int)(end - start));
}
