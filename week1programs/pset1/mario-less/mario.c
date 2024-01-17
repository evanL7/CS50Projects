#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Gets the height from the user
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (size < 1 || size > 8);

    // Prints out the right aligned set of hashes
    int initial_num_dots = size - 1;
    for (int i = 0; i < size; i++)
    {
        for (int k = 0; k < initial_num_dots; k++) // This loop determines the number of spaces in the row
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++) // This loop determines the number of hashes in the row
        {
            printf("#");
        }
        printf("\n"); // Creates new line for the next row
        initial_num_dots--; // Decrements variable to make clear the number of spaces needed for the next row
    }
}