#include <stdio.h>
typedef struct complex
{
    float real;
    float imag;
} complex;
void readcomplex(complex *c)
{
    printf("Enter the real part of number: ");
    if (scanf("%f", &c->real) != 1)
    {
        c->real = 0.0f;
    }
    printf("Enter the imaginary part of number: ");
    if (scanf("%f", &c->imag) != 1)
    {
        c->imag = 0.0f;
    }
}
void writecomplex(const complex *c)
{
    if (c->imag >= 0)
    {
        printf("%.2f + %.2fi\n", c->real, c->imag);
    }
    else
    {
        printf("%.2f - %.2fi\n", c->real, -c->imag);
    }
}
complex add(const complex *a, const complex *b)
{
    complex res;
    res.real = a->real + b->real;
    res.imag = a->imag + b->imag;
    return res;
}
complex subtract(const complex *a, const complex *b)
{
    complex res;
    res.real = a->real - b->real;
    res.imag = a->imag - b->imag;
    return res;
}
int main()
{
    complex c1 = {0.0f, 0.0f}, c2 = {0.0f, 0.0f}, c3,csub;
    readcomplex(&c1);
    readcomplex(&c2);
    c3 = add(&c1, &c2);
    printf("Sum of complex numbers: ");
    writecomplex(&c3);
    csub = subtract(&c1, &c2);
    printf("Difference of complex numbers: ");
    writecomplex(&csub);
    return 0;
}
