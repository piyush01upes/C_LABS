#include<stdio.h>
int main(){
    int a;
    printf("Enter the value of a:\n");
    scanf("%d",&a);
    int *p;
    p = &a;
    float b;
    printf("Enter the value of b:\n");
    scanf("%f",&b);
    float *q;
    q = &b;
    char c;
    printf("Enter the value of c:\n");
    scanf(" %c",&c);
    char *r;
    r = &c;
    printf("The size of the integer is %zu bytes\n", sizeof(int));
    printf("The size of the float is %zu bytes\n", sizeof(float));
    printf("The size of the character is %zu bytes\n", sizeof(char));
    printf("Address = %d, Value = %d\n",p,*p);
    printf("Address = %d, Value = %f\n",q,*q);
    printf("Address = %d, Value = %c\n",r,*r);
    printf("After incrementing,\n");
    printf("Address = %d, Value = %d\n",p+1,*(p+1));
    printf("Address = %d, Value = %f\n",q+1,*(q+1));
    printf("Address = %d, Value = %c\n",r+1,*(r+1));
    return 0;
}
