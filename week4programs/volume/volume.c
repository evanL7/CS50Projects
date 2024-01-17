// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];

    fread(&header, 1, HEADER_SIZE, input);
    fwrite(&header, sizeof(header), 1, output); // Writes the header to the new output file

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer; // Temporary variable that stores and adjusts the sample of audio by the given factor

    while (fread(&buffer, sizeof(buffer), 1, input)) // Continues until fread returns 0 which means there's nothing left to copy
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(buffer), 1, output); // Writes to the output file the adjusted sample of audio
    }

    // Close files
    fclose(input);
    fclose(output);
}
