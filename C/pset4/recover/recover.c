#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

typedef struct
{
    BYTE SOI[2]; // Start of image marker
    BYTE APP[1]; // Applicatio Use marker
} JPEGHEAD;

typedef struct
{
    JPEGHEAD h;
    BYTE buffer[509];
} JPEGBUFFER;

// Prototypes
_Bool buffer_has_header(JPEGBUFFER);

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Usage: %s [forensics image path]\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    FILE *out = NULL;

    if (file == NULL)
    {
        printf("Error reading file.");
        return 1;
    }

    int file_count = 0;

    // Create 512B buffer (memory block)
    JPEGBUFFER buffer;
    
    // Open the raw file in read mode (reading 512 bytes at a time)
    while (fread(&buffer, sizeof buffer, 1, file))
    {
        // Create file name
        char fileName[8];

        // Check the headers to see if its a new JPEG file
        if (buffer_has_header(buffer))
        {
            if (out != NULL)
            {
                // Close opened file if any
                fclose(out);

                // Increase file counter
                file_count++;
            }

            // Set file name properly
            sprintf(fileName, "%.3d.jpg", file_count);

            // Open new file
            out = fopen(fileName, "w");

            if (out == NULL)
            {
                printf("Error creating output file.\n");
                return 1;
            }
        }

        // Write buffer content to the output file
        if (out != NULL) fwrite(&buffer, sizeof(JPEGBUFFER), 1, out);
    }

    printf("%d\n", file_count);
    if (out != NULL) fclose(out);
    fclose(file);
}

_Bool buffer_has_header(JPEGBUFFER buffer)
{
    if (buffer.h.SOI[0] == 0xff && buffer.h.SOI[1] == 0xd8 && buffer.h.APP[0] == 0xff)
        return true;

    return false;
}