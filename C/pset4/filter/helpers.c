#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

#define BLUR_INTENSITY 1

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each line of the image
    for (int i = 0; i <= height; i++)
    {
        // Iterate over each pixel (RGBTRIPLE) in the line
        for (int j = 0; j <= width; j++)
        {
            // Get one pixel
            RGBTRIPLE *pixel = &image[i][j];

            // Get the red, green and blue
            int r = pixel->rgbtRed;
            int g = pixel->rgbtGreen;
            int b = pixel->rgbtBlue;

            // Calculate the average
            float avg = (r + g + b) / 3.00;

            // Assing the average color to the pixel's RGB
            pixel->rgbtRed = pixel->rgbtGreen = pixel->rgbtBlue = (int) round(avg);
        }
    }
    return;
}

// Reflect image
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            temp[i][j] = image[i][j];

    // Iterate over each line of the image
    for (int row = 0; row <= height; row++)

        // Iterate over the pixels from last to first
        for (int col = width; col > 0; col--)

            image[row][width - col] = temp[row][col - 1];

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            temp[i][j] = image[i][j];

    // Initialize average variables
    double avg_blue, avg_green, avg_red, stat;

    // Iterate over each line of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel
        for (int j = 0; j < width; j++)
        {
            // Reset average values
            avg_blue = avg_green = avg_red = stat = 0.0;

            // Blur Box (3 x 3)
            for (int rows = i - 1; rows <= i + 1; rows++)
            {
                for (int cols = j - 1; cols <= j + 1; cols++)
                {
                    // Is the pixel in any edge?
                    if ((rows >= 0 && rows < height) && (cols >= 0 && cols < width))
                    {
                        avg_red   += temp[rows][cols].rgbtRed;
                        avg_blue  += temp[rows][cols].rgbtBlue;
                        avg_green += temp[rows][cols].rgbtGreen;
                        stat++;
                    }
                }
            }

            if (stat == 0.0) return;

            image[i][j].rgbtBlue  = round(avg_blue / stat);
            image[i][j].rgbtGreen = round(avg_green / stat);
            image[i][j].rgbtRed   = round(avg_red / stat);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            temp[i][j] = image[i][j];

    // Sobel arrays
    const int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    const int Gy[] = {-1, -2, -1, 0 , 0, 0, 1, 2, 1};

    // Initialize sum variables
    int gx_R, gx_G, gx_B;
    int gy_R, gy_G, gy_B;
    double sum_R, sum_G, sum_B;

    // Iterate over each line of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            // Sobel operator counter
            int v  = 0;

            // Reset sum values
            gx_R = gx_G = gx_B = 0;
            gy_R = gy_G = gy_B = 0;
            sum_R  = sum_G = sum_B = 0;

            // For each rgb value of the pixel, compute Gx and Gy.
            // Sobel operator
            for (int rows = i - 1; rows <= i + 1; rows++)
            {
                for (int cols = j - 1; cols <= j +  1; cols++)
                {
                    // Is the pixel in any edge?
                    if ((rows >= 0 && rows < height) && (cols >= 0 && cols < width))
                    {
                        gx_R += temp[rows][cols].rgbtRed * Gx[v];
                        gy_R += temp[rows][cols].rgbtRed * Gy[v];

                        gx_G += temp[rows][cols].rgbtGreen * Gx[v];
                        gy_G += temp[rows][cols].rgbtGreen * Gy[v];

                        gx_B += temp[rows][cols].rgbtBlue * Gx[v];
                        gy_B += temp[rows][cols].rgbtBlue * Gy[v];
                    }
                    v++;
                }
            }

            sum_R = sqrt(gx_R * gx_R + gy_R * gy_R);
            sum_B = sqrt(gx_B * gx_B + gy_B * gy_B);
            sum_G = sqrt(gx_G * gx_G + gy_G * gy_G);

            pixel->rgbtRed   = sum_R > 255 ? 255 : round(sum_R);
            pixel->rgbtGreen = sum_G > 255 ? 255 : round(sum_G);
            pixel->rgbtBlue  = sum_B > 255 ? 255 : round(sum_B);
        }
    }
    return;
}

// Sepia filter
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *p = &image[i][j];
            int sepR, sepG, sepB;

            sepR = .393 * p -> rgbtRed + .769 * p -> rgbtGreen + .189 * p -> rgbtBlue;
            sepG = .349 * p -> rgbtRed + .686 * p -> rgbtGreen + .168 * p -> rgbtBlue;
            sepB = .272 * p -> rgbtRed + .534 * p -> rgbtGreen + .131 * p -> rgbtBlue;

            p->rgbtRed = sepR > 255 ? 255 : sepR;
            p->rgbtGreen = sepG > 255 ? 255 : sepG;
            p->rgbtBlue = sepB > 255 ? 255 : sepB;
        }
    }

}