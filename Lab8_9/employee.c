#include <stdio.h>
typedef struct employee
{
    char name[100];
    float basicpay;
    float grosspay;
} employee;
void readEmployee(employee *e)
{
    printf("Enter name: ");
    scanf("%s", e->name);
    printf("Enter basic pay: ");
    scanf("%f", &e->basicpay);
    e->grosspay = e->basicpay + (e->basicpay * 0.52);
}
void displayEmployee(const employee *e)
{
    printf("%s %.1f\n", e->name, e->grosspay);
}
int main()
{
    employee emp[100];
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Employee %d:\n", i + 1);
        readEmployee(&emp[i]);
    }
    printf("The Employee Name with the Gross Salary is:\n");
    for (int i = 0; i < n; i++)
    {
        displayEmployee(&emp[i]);
    }
    return 0;
}
