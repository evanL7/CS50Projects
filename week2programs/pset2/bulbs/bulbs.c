#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8; // Global variable

void print_bulb(int bit);

int main(void)
{
    int size[] = {128, 64, 32, 16, 8, 4, 2, 1}; // Potential values from 8 bits

    string text = get_string("Message: "); // Obtain user input
    int j = strlen(text); // Find length of string

    for (int i = 0; i < j; i++) // This loop gets the bit string for each character
    {
        int num = text[i]; // This variable obtains the ASCII number of the character
        int bit_string[BITS_IN_BYTE]; // This variable stores the bit string which represents the binary number

        // Loop determines whether a position should be assigned a one or zero starting from greatest to smallest
        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            if (size[k] <= num)
            {
                bit_string[k] = 1; // Assigns a one
                num -= size[k]; // Subtracts from the num variable until the one is reached in the size array
            }
            else
            {
                bit_string[k] = 0; // Assigns a zero
            }
            print_bulb(bit_string[k]); // Calls the function to show the coloured dots
            // printf("%i", bit_string[k]); // Use if want to see binary representation of the current character
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
