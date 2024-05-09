#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

bool isjpg(BYTE *block);

int main(int argc, char *argv[])
{
    // If user type wrong to launch the program
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover **.raw\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "r");
    // Check if it's NULL
    if (input == NULL)
    {
        fprintf(stderr, "Could not open the %s file.\n", argv[1]);
        return 2;
    }

    // Declare output file buffer
    FILE *JPG;

    // Declare temporary storage for block.
    BYTE block[512];

    // bool to see if we've found any jpgs yet
    bool found = false;
    int r;
    int num = 0;

    while (fread(block, sizeof(block), 1, input) == 1)
    {
        // If we found a header
        if (isjpg(block))
        {
            // Filename will be three digits + .jpg and a null character
            char filename[8];

            // filename is defined by jpgnum which only iterates when new jpgheader is found.
            sprintf(filename, "%03.3i.jpg", num);

            // For debugging
            printf("processing file: %s\n", filename);

            if (found == true)
            {
                // Already jpg in buffer. Close/finish it.
                fclose(JPG);
            }
            else
            {
                // First jpg! Set foundjpg to true.
                found = true;
            }
            // Open new and write first block in it
            JPG = fopen(filename, "w");

            fwrite(block, sizeof(block), 1, JPG);

            num++;
        }
        // If we didn't find a header
        else
        {
            // Are we already working on a jpg?
            if (found == true)
            {
                // This is not a header and there is already a jpg, so write this block to current jpg.
                fwrite(block, sizeof(block), 1, JPG);
            }
        }

    }
    // Close files
    fclose(input);
    fclose(JPG);
}

bool isjpg(BYTE *block)
{
    if (block[0] == 0xff &&
        block[1] == 0xd8 &&
        block[2] == 0xff &&
        (block[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    else
    {
        return false;
    }
}