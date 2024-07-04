#include <stdio.h>
#include <stdbool.h>

void mergedList(int* array1, int* array2, int length1, int length2, int* mergedArray)
{
   int stopper = length1 + length2;
   int sign1 = 0;
   int sign2 = 0;
   while ((sign1 + sign2) < stopper) {
       if (sign1 < length1 && sign2 == 0) {
           mergedArray[sign1] = array1[sign1];
           sign1++;
       }
       
       if (sign1 == length1 && sign2 < length2) {
           mergedArray[sign1 + sign2] = array2[sign2];
           sign2++;
       }
   }
   
   sortList(mergedArray, stopper);
}

void sortList(int* mergedArray, int length)
{
    bool swapped;
    for (int i = 0; i < length - 1; i++) {
        swapped = false;
        for (int j = 0; j < length - 1; j++) {
            if (mergedArray[j] > mergedArray[j + 1]) {
                int temp = mergedArray[j];
                mergedArray[j] = mergedArray[j + 1];
                mergedArray[j + 1] = temp;
                swapped = true;
            }
        }
        
        if (swapped == false) break;
    }
}

void main()
{
    int length1;
    printf("Masukkan panjang array 1 : ");
    scanf("%d", &length1);

    int array1[length1];
    for (int i = 0; i < length1; i++) {
        int temp;
        printf("Masukkan elemen ke %d untuk array 1 : ", i);
        scanf("%d", &temp);

        array1[i] = temp;
    }

    int length2;
    printf("Masukkan panjang array 2 : ");
    scanf("%d", &length2);

    int array2[length2];
    for (int i = 0; i < length2; i++) {
        int temp;
        printf("Masukkan elemen ke %d untuk array 2 : ", i);
        scanf("%d", &temp);

        array2[i] = temp;
    }
    
    int mergedArray[length1 + length2];
    mergedList(&array1, &array2, length1, length2, &mergedArray);
    
    for(int i = 0; i < length1 + length2; i++) {
        printf("%d ", mergedArray[i]);
    }
}