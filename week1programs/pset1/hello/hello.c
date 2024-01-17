#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name? "); // Asks the user for their name
    printf("hello, %s\n", name); // Print line includes their name
}