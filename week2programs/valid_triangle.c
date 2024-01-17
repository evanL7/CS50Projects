#include <cs50.h>
#include <stdio.h>

int valid_triangle(float a, float b, float c);

int main(void)
{
    float reals[3];
    int answer;

    for (int i = 0; i < 3; i++)
    {
        reals[i] = get_float("Number: ");
    }
    answer = valid_triangle(reals[0], reals[1], reals[2]);
    if (answer)
    {
        printf("True, valid triangle.\n");
    }
    else
    {
        printf("False, invalid triangle.\n");
    }
}

int valid_triangle(float a, float b, float c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return 0;
    }
    else if (a + b <= c || a + c <= b || b + c <= a)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}