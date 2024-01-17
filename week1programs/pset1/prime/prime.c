#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: "); // Asks user for a minimum value
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: "); // Asks user for a maximum value
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i)) // If this loop is true, then the number is prime
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    bool is_prime;

    for (int j = 2; j < number; j++)
    {
        if (number % j == 0) // This condition checks if the number is composite
        {
            return false; // If we know the number is composite, then it must not be prime
        }
    }
    return true; // If the number exits the loop, we know that the number is prime
}
