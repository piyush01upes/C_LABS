 #include <stdio.h>

int main() {
    int num;

    // Validate number input
    printf("Enter a number: ") ;
    while (scanf("%d", &num) != 1) {
        printf(" Invalid input! Please enter an integer: ");
        scanf("%*s");  // discard wrong input
    }

    printf("\n--- Multiplication Table of %d ---\n", num);

    for (int i = 1; i <= 10; i++) {
        printf("%d * %d = %d\n", num, i, num * i);
    }

    return 0;
}
