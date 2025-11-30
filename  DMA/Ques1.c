/*Write a C program that: 1. Dynamically allocates an array of size n using malloc(). 2. Takes n
integer inputs from the user. 3. Inserts a new element at a given position pos (1-based index). 4.
Shifts the existing elements to the right. 5. Displays the updated array.
Input Example: Enter number of elements: 5 Enter elements: 10 20 30 40 50 Enter element to
insert: 25 Enter position to insert: 3
Output Example: Array after insertion: 10 20 25 30 40 50
*/
#include <stdio.h>
#include <stdlib.h>

void inputArray(int *arr, int n);
void printArray(int *arr, int n);
int* insertAtPosition(int *arr, int *n, int element, int pos);

void inputArray(int *arr, int n) {
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

void printArray(int *arr, int n) {
    printf("Array after insertion: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* insertAtPosition(int *arr, int *n, int element, int pos) {
    arr = (int *)realloc(arr, (*n + 1) * sizeof(int));
    for (int i = *n; i >= pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos - 1] = element;
    (*n)++;
    return arr;
}

int main() {
    int n, element, pos;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    inputArray(arr, n);

    printf("Enter element to insert: ");
    scanf("%d", &element);

    printf("Enter position (1-based index): ");
    scanf("%d", &pos);

    arr = insertAtPosition(arr, &n, element, pos);

    printArray(arr, n);

    free(arr);
    return 0;
}
