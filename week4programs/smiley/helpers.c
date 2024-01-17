#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++) // Loops through the height, i.e., rows
    {
        for (int j = 0; j < width; j++) // Loops through width, i.e. columns
        {
            if (image[i][j].rgbtBlue != 0 || image[i][j].rgbtGreen != 0 || image[i][j].rgbtRed != 0) // Probably better to check if == 0x00
            {
                image[i][j].rgbtBlue = 128;
            }
        }
    }
}
