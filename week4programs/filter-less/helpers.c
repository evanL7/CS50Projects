#include "helpers.h"
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    float average; // Average stores the average of the RGB values
    int rounded_avg;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            average = (float) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            rounded_avg = (int) average;
            if (average >= (float) (rounded_avg + 0.5)) // Check if average needs to be rounded up or down
            {
                rounded_avg++;
            }
            // Set RGB values all the same to create grayscale
            image[i][j].rgbtRed = rounded_avg;
            image[i][j].rgbtGreen = rounded_avg;
            image[i][j].rgbtBlue = rounded_avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    double sepiaRed, sepiaGreen, sepiaBlue;
    int originalRed, originalGreen, originalBlue;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // First get the original pixel colours
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // Next, convert the original colours to sepia colours
            // If the sepia value exceeds 255, the maximum colour range, reset the value to 255.
            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else if (sepiaRed >= (int) sepiaRed + 0.5) // Adjusts pixel colour for rounding up
            {
                sepiaRed = (int) sepiaRed;
                sepiaRed++;
            }

            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else if (sepiaGreen >= (int) sepiaGreen + 0.5) // Adjusts pixel colour for rounding up
            {
                sepiaGreen = (int) sepiaGreen;
                sepiaGreen++;
            }

            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            else if (sepiaBlue >= (int) sepiaBlue + 0.5) // Adjusts pixel colour for rounding up
            {
                sepiaBlue = (int) sepiaBlue;
                sepiaBlue++;
            }

            // Finally, set the image to the new sepia coloured pixels
            image[i][j].rgbtRed = (int) sepiaRed;
            image[i][j].rgbtGreen = (int) sepiaGreen;
            image[i][j].rgbtBlue = (int) sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *temp; // Dynamically allocate memory to temporarily store the reflected row
    temp = (RGBTRIPLE *) malloc(sizeof(RGBTRIPLE) * width);

    int i, j, k;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++) // Stores the currently reflected row
        {
            temp[j] = image[i][(width - 1) - j];
        }

        for (k = 0; k < width; k++) // Updates the image accordingly
        {
            image[i][k] = temp[k];
        }
    }
    free(temp); // Frees the allocated memory
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, count;
    double totRed, totGreen, totBlue;
    double newRed, newGreen, newBlue;

    RGBTRIPLE image_copy[height][width];
    for (i = 0; i < height; i++) // Copies the image to a new 2-D array
    {
        for (j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Reset values for the next pixel
            totRed = 0;
            totGreen = 0;
            totBlue = 0;
            count = 0;

            // Adds the centre of the box
            totRed += image_copy[i][j].rgbtRed;
            totGreen += image_copy[i][j].rgbtGreen;
            totBlue += image_copy[i][j].rgbtBlue;
            count++;

            // Conditions to check if the top row of the box should be added
            if (i - 1 >= 0 && j - 1 >= 0) // Check top left of box
            {
                totRed += image_copy[i-1][j-1].rgbtRed;
                totGreen += image_copy[i-1][j-1].rgbtGreen;
                totBlue += image_copy[i-1][j-1].rgbtBlue;
                count++;
            }
            if (i - 1 >= 0) // Check top middle of box
            {
                totRed += image_copy[i-1][j].rgbtRed;
                totGreen += image_copy[i-1][j].rgbtGreen;
                totBlue += image_copy[i-1][j].rgbtBlue;
                count++;
            }
            if (i - 1 >= 0 && j + 1 < width) // Check top right of the box
            {
                totRed += image_copy[i-1][j+1].rgbtRed;
                totGreen += image_copy[i-1][j+1].rgbtGreen;
                totBlue += image_copy[i-1][j+1].rgbtBlue;
                count++;
            }

            // Conditions to check if the middle row of the box should be added
            if (j - 1 >= 0) // Check middle left of box
            {
                totRed += image_copy[i][j-1].rgbtRed;
                totGreen += image_copy[i][j-1].rgbtGreen;
                totBlue += image_copy[i][j-1].rgbtBlue;
                count++;
            }
            if (j + 1 < width) // Check middle right of box
            {
                totRed += image_copy[i][j+1].rgbtRed;
                totGreen += image_copy[i][j+1].rgbtGreen;
                totBlue += image_copy[i][j+1].rgbtBlue;
                count++;
            }

            // Conditions to check if the bottom row of the box should be added
            if (i + 1 < height && j - 1 >= 0) // Check bottom left of box
            {
                totRed += image_copy[i+1][j-1].rgbtRed;
                totGreen += image_copy[i+1][j-1].rgbtGreen;
                totBlue += image_copy[i+1][j-1].rgbtBlue;
                count++;
            }
            if (i + 1 >= 0 && i + 1 < height) // Check bottom middle of box
            {
                totRed += image_copy[i+1][j].rgbtRed;
                totGreen += image_copy[i+1][j].rgbtGreen;
                totBlue += image_copy[i+1][j].rgbtBlue;
                count++;
            }
            if (i + 1 < height && j + 1 < width) // Check bottom right of the box
            {
                totRed += image_copy[i+1][j+1].rgbtRed;
                totGreen += image_copy[i+1][j+1].rgbtGreen;
                totBlue += image_copy[i+1][j+1].rgbtBlue;
                count++;
            }

            // Finds the new blurred pixel colours
            newRed = totRed / count;
            newGreen = totGreen / count;
            newBlue = totBlue / count;

            if (newRed >= (int) newRed + 0.5) // Adjusts pixel colour for rounding up
            {
                newRed = (int) newRed;
                newRed++;
            }
            if (newGreen >= (int) newGreen + 0.5) // Adjusts pixel colour for rounding up
            {
                newGreen = (int) newGreen;
                newGreen++;
            }
            if (newBlue >= (int) newBlue + 0.5) // Adjusts pixel colour for rounding up
            {
                newBlue = (int) newBlue;
                newBlue++;
            }

            // Sets the new blurred pixel colours
            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtBlue = newBlue;
        }
    }
    return;
}