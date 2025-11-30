// Q3. Write a C program that: 1. Dynamically allocates memory for n integers using malloc(). 2.
// Accepts elements from the user. 3. Separates all even and odd elements into two new dynamically
// allocated arrays. 4. Prints the even and odd arrays separately.
// Input Example: Enter number of elements: 6 Enter elements: 1 2 3 4 5 6
// Output Example: Even elements: 2 4 6 Odd elements: 1 3 5
#include <stdio.h>
#include <stdlib.h>

void inputArray(int *arr, int n);
void printArray(int *arr, int n);
void separateEvenOdd(int *arr, int n, int **evenArr, int *eCount, int **oddArr, int *oCount);

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter elements: ");
    inputArray(arr, n);

    int *evenArr, *oddArr;
    int eCount = 0, oCount = 0;

    separateEvenOdd(arr, n, &evenArr, &eCount, &oddArr, &oCount);

    printf("Even elements: ");
    printArray(evenArr, eCount);

    printf("Odd elements: ");
    printArray(oddArr, oCount);

    free(arr);
    free(evenArr);
    free(oddArr);

    return 0;
}

void inputArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void separateEvenOdd(int *arr, int n, int **evenArr, int *eCount, int **oddArr, int *oCount) {
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            (*eCount)++;
        else
            (*oCount)++;
    }

    *evenArr = (int *)malloc((*eCount) * sizeof(int));
    *oddArr = (int *)malloc((*oCount) * sizeof(int));

    int ei = 0, oi = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            (*evenArr)[ei++] = arr[i];
        else
            (*oddArr)[oi++] = arr[i];
    }
}
