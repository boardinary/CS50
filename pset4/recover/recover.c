#include <stdio.h>
#include <stdlib.h>

#define BlockSize 512

int main(int argc, char *argv[])
{

    // Check that only one argument is written
    if (argc != 2)
    {
        printf("Usage: recover [image]\n");
        return 1;

    }

    // Check to see if image file exists
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Please enter a valid image filename\n");
        return 1;
    }

    char filename[8];

    // Memory allocation for buffer
    unsigned char *buffer = malloc(512);

    // write filename counter
    int n = -1;

    // Initialize write file pointer
    FILE *filew = NULL;

    while (fread(buffer, BlockSize, 1, file))
    {
        // Check if JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // Close previous write file
            if (n > -1)
            {
                fclose(filew);
            }

            // Iterate file number counter
            n++;

            // New file name. Format will be different depending on size of n.
            if (n <= 9)
            {
                sprintf(filename, "00%i.jpg", n);
            }

            else if (n > 9 && n < 99)
            {
                sprintf(filename, "0%i.jpg", n);
            }

            else
            {
                sprintf(filename, "%i.jpg", n);
            }

            // Open new file
            filew = fopen(filename, "w");

            // Write to filew
            fwrite(buffer, BlockSize, 1, filew);
        }

        // Write to open write file
        else if (n > -1)
        {
            fwrite(buffer, BlockSize, 1, filew);
        }
    }

    // Close write file
    fclose(filew);

    // Close read file
    fclose(file);

    // Clear memory
    free(buffer);

    return 0;
}

