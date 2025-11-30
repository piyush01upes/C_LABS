#include<stdio.h>
#include<string.h>
typedef struct book
{
    int book_id;
    char title[35];
    char author_name[40];
    float price;
}books;
books fun(books a)
{
    printf("Enter the book id:\n");
    scanf("%d",&a.book_id);
    printf("Enter the title of the book:\n");
    scanf(" %[^\n]",a.title);
    printf("Enter the name of the author:\n");
    scanf(" %[^\n]",a.author_name);
    printf("Enter the price of the book:\n");
    scanf("%f",&a.price);
    return a;
}
int main()
{
    books book1;
    book1 = fun(book1);
    printf("The ID of the book is: %d\n",book1.book_id);
    printf("Title of the book is: %s\n",book1.title);
    printf("Author of the book is: %s\n",book1.author_name);
    printf("Price of the book is: %.2f\n",book1.price);
    return 0;
}
