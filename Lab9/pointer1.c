#include <stdio.h>
int main()
{
    int a;
    printf("enter the value of a: \n");
    scanf("%d", &a);
    int *p;
    p = &a;
    float b;
    printf("enter the value of b:\n");
    scanf("%f", &b);
    float *q;
    q = &b;
    char c;
    printf("Enter the value of c:\n");
    scanf(" %c", &c);
    char *r;
    r = &c;
    printf("The address for (int) datatype is %d\n", p); // prints the address
    printf("The value at the address is %d\n", *p);      // prints the value at which p address
    printf("The address for (float) datatype is %d\n", q);
    printf("The value stored at the address is %.1f\n", *q);
    printf("The address for (char) datatype is %d\n", r);
    printf("The value stored at the address is %c", *r);
    return 0;
}
