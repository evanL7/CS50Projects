#include <cs50.h>
#include <stdio.h>
int main(void)
{
    int x = get_int("x: "); // Get x value from user
    int y = get_int("y: "); // Get y value from user
    printf("%i\n", x + y); // Perform addition
}