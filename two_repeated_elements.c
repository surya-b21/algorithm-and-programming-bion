#include <stdio.h>
#include <stdlib.h>

void findInSet(int *set, int value)
{
    int index = 0;
    int show = 0;
    while (set[index] != NULL)
    {
        if (set[index] == value) {
            show++;
        } else {
            set[index + 1] = value;
        }

        index++;
    }

    if (show == 2) {
        printf("%d, ", value);
    }
}

int main()
{
    int length;
    printf("Insert length of array : ");
    scanf("%d", &length);

    int array[length + 2];

    // generate array
    printf("Arr[] = {");
    for (int i = 0; i < (length + 2); i++)
    {
        int random = (rand() % length) + 1;
        array[i] = random;
        printf("%d, ", random);
    }
    printf("}, ");
    
    int *set = (int*) malloc(length * sizeof(int));
    set[0] = array[0];

    for  (int i = 0; i < (length + 2); i++)
    {
        findInSet(set, array[i]);
    }

    return 0;
}