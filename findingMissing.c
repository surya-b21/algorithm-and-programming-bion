#include <stdio.h>
#include <stdbool.h>

int findMissingNumber(int array[], int length)
{
    int check;
    for (int i = 0; i < length; i++)
    {
        if ((array[i] + 1) == array[i + 1]) continue;
        check = array[i] + 1;
        break;
    }
    
    return check;
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}

void main()
{
    int n;
    printf("Insert n number : ");
    scanf("%d", &n);

    int array[n-1];
    puts("Insert number in array");
    for (int i = 0; i < n - 1; i++)
    {
        int temp;
        scanf("%d", &temp);
        array[i] = temp;
    }

    // sort array
    bubbleSort(array, n-1);

    int missing = findMissingNumber(array, n-1);
    
    printf("Missing number: %d", missing);
}