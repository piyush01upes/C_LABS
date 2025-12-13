#include <stdio.h>
#include <stdlib.h>

#define MIN 1
#define MAX 5

int primaryDiagonal(int **a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i][i];
    return sum;
}

int secondaryDiagonal(int **a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i][n - 1 - i];
    return sum;
}

int rowSum(int **a, int n, int r) {
    int sum = 0;
    for (int j = 0; j < n; j++)
        sum += a[r][j];
    return sum;
}

int colSum(int **a, int n, int c) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i][c];
    return sum;
}

int main() {

    int n;

    printf("Enter matrix size (1 to 5): ");
    while (scanf("%d", &n) != 1 || n < MIN || n > MAX) {
        printf("Invalid input! Enter integer between 1 and 5: ");
        while (getchar() != '\n'); // clear buffer
    }

    int **a = malloc(n * sizeof(int *));
    int *data = malloc(n * n * sizeof(int));
    for (int i = 0; i < n; i++)
        a[i] = data + i * n;

    printf("Enter %d integers:\n", n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            printf("a[%d][%d] = ", i, j);
            while (scanf("%d", &a[i][j]) != 1) {
                printf("Invalid input! Enter an integer: ");
                while (getchar() != '\n');
            }
        }
    }

    char again = 'y';

    while (again == 'y' || again == 'Y') {

        printf("\nMenu:\n");
        printf("1. Primary Diagonal Sum\n");
        printf("2. Secondary Diagonal Sum\n");
        printf("3. Row Sum\n");
        printf("4. Column Sum\n");
        printf("5. Exit\n");

        int ch;
        printf("Enter choice: ");

        while (scanf("%d", &ch) != 1) {
            printf("Invalid choice! Enter again: ");
            while (getchar() != '\n');
        }

        switch (ch) {

            case 1:
                printf("Primary diagonal sum = %d\n", primaryDiagonal(a, n));
                break;

            case 2:
                printf("Secondary diagonal sum = %d\n", secondaryDiagonal(a, n));
                break;

            case 3: {
                int r;
                printf("Enter row index (0 to %d): ", n - 1);
                while (scanf("%d", &r) != 1 || r < 0 || r >= n) {
                    printf("Invalid row index! Enter again: ");
                    while (getchar() != '\n');
                }
                printf("Row sum = %d\n", rowSum(a, n, r));
                break;
            }

            case 4: {
                int c;
                printf("Enter column index (0 to %d): ", n - 1);
                while (scanf("%d", &c) != 1 || c < 0 || c >= n) {
                    printf("Invalid column index! Enter again: ");
                    while (getchar() != '\n');
                }
                printf("Column sum = %d\n", colSum(a, n, c));
                break;
            }

            case 5:
                printf("Exiting...\n");
                free(data);
                free(a);
                return 0;

            default:
                printf("Invalid option.\n");
        }

        printf("\nDo you want to continue? (y/n): ");
        while (getchar() != '\n'); // clear buffer
        scanf("%c", &again);
    }

    printf("Program ended.\n");
    free(data);
    free(a);

    return 0;
}
