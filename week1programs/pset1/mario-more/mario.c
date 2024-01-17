#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get the height of the blocks from the user
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (size < 1 || size > 8);

    // Print out the blocks
    int initial_spaces = size - 1;
    for (int i = 0; i < size; i++) // This loop keeps track of the current row
    {
        for (int j = 0; j < initial_spaces; j++) // Keeps track of the number of spaces intially
        {
            printf(" ");
        }

        for (int k = 0; k < i + 1; k++) // Prints out the number of hashes on the left side
        {
            printf("#");
        }

        printf("  "); // Prints the two spaces between the blocks

        for (int l = 0; l < i + 1; l++) // Prints out the number of hashes on the right side
        {
            printf("#");
        }

        printf("\n"); // Creates new line to continue to the next row
        initial_spaces--; // Keeps track of the number of spaces to be printed out
    }

}