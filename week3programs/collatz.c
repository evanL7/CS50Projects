#include <cs50.h>
#include <stdio.h>

int collatz(int num);

int main(void)
{
    int number = get_int("Number: ");
    printf("Steps: %i\n", collatz(number));
}


int collatz(int num)
{
    if (num == 1)
    {
        return 0;
    }

    else if ((num % 2) == 0)
    {
        return 1 + collatz(num / 2);
    }

    else
    {
        return 1 + collatz(3 * num + 1);
    }
}