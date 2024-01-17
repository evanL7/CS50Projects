#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512; // Amount of memory read after each iteration
const int NAME_SIZE = 8;    // Maximum length of filename minus 1 for the NULL character

/*
    Understanding: my first attempt at recover assumed that every block held a header and could
    be differentiated by the fourth item in the buffer, but that is incorrect. The correct way is to understand
    that only the first block of the jpg holds the header and until a new header is reached, that new header
    is a new jpg file.

    I also faced the bug after realizing that to pace the tests, JPEG files have the file format .jpg not .jpeg.
*/

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Need two command line arguments.\n");
        return 1;
    }

    char *raw_filename = argv[1];
    FILE *raw_file = fopen(raw_filename, "r");

    if (!raw_file) // Check that file is read properly
    {
        printf("Could not read file.\n");
        return 1;
    }

    int counter = 0;
    FILE *new_file = NULL;
    char buffer_filename[NAME_SIZE];
    BYTE *buffer;
    buffer = (BYTE *) malloc(sizeof(BYTE) * BLOCK_SIZE);

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // Start of a new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // First jpeg block
        {
            if (new_file != NULL) // Close the current jpeg currently being worked on
            {
                fclose(new_file);
            }
            sprintf(buffer_filename, "%03d.jpg", counter);
            new_file = fopen(buffer_filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, new_file);
            counter++;
        }
        else if (new_file != NULL) // Continue writing to the current jpeg file
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, new_file);
        }
    }
    free(buffer);
    fclose(new_file);
    fclose(raw_file);
    return 0;
}