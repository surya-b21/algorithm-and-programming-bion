#include <stdio.h>

void main()
{
    int length;
    printf("Please insert length of array : ");
    scanf("%d", &length);

    int array[length];
    printf("Please insert array element :\n");
    for (int i = 0; i < length; i++) {
        int temp;
        scanf("%d", &temp);

        array[i] = temp;
    }

    int target;
    printf("Please insert total : ");
    scanf("%d", &target);

    int first, second;

    findIndex(array, length, target, &first, &second);

    printf("%d %d", first, second);
}

void findIndex(int array[], int length, int target, int * first, int * second)
{
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            if (array[i] + array[j] == target) {
                *first = i;
                *second = j;
                return;
            }
        }
    }
}