#include <stdio.h>
#include<string.h>
typedef union address
{
    char home_address[100];
    char hostel_address[100];
}address;
typedef struct stud
{
    char name[50];
    char city_name[50];
    char state_name[50];
    char zip[15];
    address addr;
    int current_place;
}student;
int main()
{
    student a;
    printf("Enter your name: ");
    scanf(" %[^\n]",a.name);
    printf("Enter your city: ");
    scanf(" %[^\n]",a.city_name);
    printf("Enter your state: ");
    scanf(" %[^\n]",a.state_name);
    printf("Enter your ZIP code: ");
    scanf(" %[^\n]",a.zip);
    printf("Enter 1 if you live in hostel or 2 if you live at home: ");
    scanf("%d",&a.current_place);
    // tried to use the structure and union nesting in the if-else block while taking inputs from user
    if (a.current_place == 1)
    {
        printf("Enter your hostel address: ");
        scanf(" %[^\n]",a.addr.hostel_address);
        printf("The address of the student is: %s\n",a.addr.hostel_address);
    } 
    else
    {
        printf("Enter your home address: ");
        scanf(" %[^\n]",a.addr.home_address);
        printf("The address of the student is: %s\n",a.addr.home_address);

    }
    printf("Name of the student is %s\n",a.name);
    printf("City: %s\n",a.city_name);
    printf("State: %s\n",a.state_name);
    printf("ZIP: %s\n",a.zip);
    return 0;
}
