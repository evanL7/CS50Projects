#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1);

    int array[n];

    array[0] = 1;
    printf("%i\n", array[0]);
    for (int i = 1; i < n; i++)
    {
        array[i] = 2 * array[i-1];
        printf("%i\n", array[i]);
    }

}