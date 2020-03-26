#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round(((float) image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize image copy
    RGBTRIPLE copy[height][width];

    // Make a reflected image row by row into copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][width - 1 - j] = image[i][j];
        }
    }

    // Copy "copy" into image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize image copy
    RGBTRIPLE copy[height][width];

    // Make a blurred image row by row into copy for center bulk of image
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            int totRed = 0;
            int totGreen = 0;
            int totBlue = 0;

            //iterate to add up all of the color intensities in the block
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    totBlue = totBlue + image[k][l].rgbtBlue;
                    totGreen = totGreen + image[k][l].rgbtGreen;
                    totRed = totRed + image[k][l].rgbtRed;
                }
            }

            // Average the totals
            int avgBlue = round((float) totBlue / 9);
            int avgGreen = round((float) totGreen / 9);
            int avgRed = round((float) totRed / 9);

            // Copy values to copy
            copy[i][j].rgbtBlue = avgBlue;
            copy[i][j].rgbtGreen = avgGreen;
            copy[i][j].rgbtRed = avgRed;
        }
    }

    // Make blurred top row
    for (int i = 1; i < width - 1; i++)
    {

        int totRed = 0;
        int totGreen = 0;
        int totBlue = 0;

        //iterate to add up all of the color intensities in the block
        for (int j = i - 1; j < i + 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                totBlue = totBlue + image[k][j].rgbtBlue;
                totGreen = totGreen + image[k][j].rgbtGreen;
                totRed = totRed + image[k][j].rgbtRed;
            }
        }

        // Calculate avg color intensities
        int avgBlue = round((float) totBlue / 6);
        int avgGreen = round((float) totGreen / 6);
        int avgRed = round((float) totRed / 6);

        // Copy values to copy
        copy[0][i].rgbtBlue = avgBlue;
        copy[0][i].rgbtGreen = avgGreen;
        copy[0][i].rgbtRed = avgRed;
    }

    // Make blurred bottom row
    for (int i = 1; i < width - 1; i++)
    {

        int totRed = 0;
        int totGreen = 0;
        int totBlue = 0;

        //iterate to add up all of the color intensities in the block
        for (int j = i - 1; j < i + 2; j++)
        {
            for (int k = height - 2; k < height; k++)
            {
                totBlue = totBlue + image[k][j].rgbtBlue;
                totGreen = totGreen + image[k][j].rgbtGreen;
                totRed = totRed + image[k][j].rgbtRed;
            }
        }

        // Calculate avg color intensities
        int avgBlue = round((float) totBlue / 6);
        int avgGreen = round((float) totGreen / 6);
        int avgRed = round((float) totRed / 6);

        // Copy values to copy
        copy[height - 1][i].rgbtBlue = avgBlue;
        copy[height - 1][i].rgbtGreen = avgGreen;
        copy[height - 1][i].rgbtRed = avgRed;
    }

    // Make blurred left column
    for (int i = 1; i < height - 1; i++)
    {

        int totRed = 0;
        int totGreen = 0;
        int totBlue = 0;

        //iterate to add up all of the color intensities in the block
        for (int j = i - 1; j < i + 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                totBlue = totBlue + image[j][k].rgbtBlue;
                totGreen = totGreen + image[j][k].rgbtGreen;
                totRed = totRed + image[j][k].rgbtRed;
            }
        }

        // Calculate avg color intensities
        int avgBlue = round((float) totBlue / 6);
        int avgGreen = round((float) totGreen / 6);
        int avgRed = round((float) totRed / 6);

        // Copy values to copy
        copy[i][0].rgbtBlue = avgBlue;
        copy[i][0].rgbtGreen = avgGreen;
        copy[i][0].rgbtRed = avgRed;
    }

    // Make blurred right column
    for (int i = 1; i < height - 1; i++)
    {

        int totRed = 0;
        int totGreen = 0;
        int totBlue = 0;

        //iterate to add up all of the color intensities in the block
        for (int j = i - 1; j < i + 2; j++)
        {
            for (int k = width - 2; k < width; k++)
            {
                totBlue = totBlue + image[j][k].rgbtBlue;
                totGreen = totGreen + image[j][k].rgbtGreen;
                totRed = totRed + image[j][k].rgbtRed;
            }
        }

        // Calculate avg color intensities
        int avgBlue = round((float) totBlue / 6);
        int avgGreen = round((float) totGreen / 6);
        int avgRed = round((float) totRed / 6);

        // Copy values to copy
        copy[i][width - 1].rgbtBlue = avgBlue;
        copy[i][width - 1].rgbtGreen = avgGreen;
        copy[i][width - 1].rgbtRed = avgRed;
    }


    // Make blurred top left pixel
    int totRed = 0;
    int totGreen = 0;
    int totBlue = 0;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            totBlue = totBlue + image[i][j].rgbtBlue;
            totGreen = totGreen + image[i][j].rgbtGreen;
            totRed = totRed + image[i][j].rgbtRed;
        }
    }

    // Calculate avg color intensities
    int avgBlue = round((float) totBlue / 4);
    int avgGreen = round((float) totGreen / 4);
    int avgRed = round((float) totRed / 4);

    // Copy values to copy
    copy[0][0].rgbtBlue = avgBlue;
    copy[0][0].rgbtGreen = avgGreen;
    copy[0][0].rgbtRed = avgRed;


    // Make blurred top right pixel
    totRed = 0;
    totGreen = 0;
    totBlue = 0;

    for (int i = 0; i < 2; i++)
    {
        for (int j = width - 2; j < width; j++)
        {
            totBlue = totBlue + image[i][j].rgbtBlue;
            totGreen = totGreen + image[i][j].rgbtGreen;
            totRed = totRed + image[i][j].rgbtRed;
        }
    }

    // Calculate avg color intensities
    avgBlue = round((float) totBlue / 4);
    avgGreen = round((float) totGreen / 4);
    avgRed = round((float) totRed / 4);

    // Copy values to copy
    copy[0][width - 1].rgbtBlue = avgBlue;
    copy[0][width - 1].rgbtGreen = avgGreen;
    copy[0][width - 1].rgbtRed = avgRed;

    // Make blurred bottom left pixel
    totRed = 0;
    totGreen = 0;
    totBlue = 0;

    for (int i = height - 2; i < height; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            totBlue = totBlue + image[i][j].rgbtBlue;
            totGreen = totGreen + image[i][j].rgbtGreen;
            totRed = totRed + image[i][j].rgbtRed;
        }
    }

    // Calculate avg color intensities
    avgBlue = round((float) totBlue / 4);
    avgGreen = round((float) totGreen / 4);
    avgRed = round((float) totRed / 4);

    // Copy values to copy
    copy[height - 1][0].rgbtBlue = avgBlue;
    copy[height - 1][0].rgbtGreen = avgGreen;
    copy[height - 1][0].rgbtRed = avgRed;


    // Make blurred bottom right pixel
    totRed = 0;
    totGreen = 0;
    totBlue = 0;

    for (int i = height - 2; i < height; i++)
    {
        for (int j = width - 2; j < width; j++)
        {
            totBlue = totBlue + image[i][j].rgbtBlue;
            totGreen = totGreen + image[i][j].rgbtGreen;
            totRed = totRed + image[i][j].rgbtRed;
        }
    }

    // Calculate avg color intensities
    avgBlue = round((float) totBlue / 4);
    avgGreen = round((float) totGreen / 4);
    avgRed = round((float) totRed / 4);

    // Copy values to copy
    copy[height - 1][width - 1].rgbtBlue = avgBlue;
    copy[height - 1][width - 1].rgbtGreen = avgGreen;
    copy[height - 1][width - 1].rgbtRed = avgRed;

    // Copy "copy" into image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of image with a 1 pixel black border surrounding it
    RGBTRIPLE copy1[height + 2][width + 2];
    // Top row black
    for (int i = 0; i < width + 2; i++)
    {
        copy1[0][i].rgbtBlue = 0;
        copy1[0][i].rgbtGreen = 0;
        copy1[0][i].rgbtRed = 0;
    }
    // Bottom row black
    for (int i = 0; i < width + 2; i++)
    {
        copy1[height + 1][i].rgbtBlue = 0;
        copy1[height + 1][i].rgbtGreen = 0;
        copy1[height + 1][i].rgbtRed = 0;
    }
    // Left side black
    for (int i = 1; i < height + 1; i++)
    {
        copy1[i][0].rgbtBlue = 0;
        copy1[i][0].rgbtGreen = 0;
        copy1[i][0].rgbtRed = 0;
    }
    // Right side black
    for (int i = 1; i < height + 1; i++)
    {
        copy1[i][width + 1].rgbtBlue = 0;
        copy1[i][width + 1].rgbtGreen = 0;
        copy1[i][width + 1].rgbtRed = 0;
    }

    // Copy image contents to copy1
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            copy1[i][j] = image[i][j];
        }
    }

    // //test
    //     for (int i = 1; i < height + 1; i++)
    // {
    //     for (int j = 1; j < width + 1; j++)
    //     {
    //         copy1[i][j] = image[i][j];
    //     }
    // }


    // Inititalize two arrays to hold Gx and Gy values
    RGBTRIPLE CopyGx[height][width];
    RGBTRIPLE CopyGy[height][width];

    // Write values to 0 in CopyGx/CopyGy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            CopyGx[i][j].rgbtRed = 0;
            CopyGx[i][j].rgbtGreen = 0;
            CopyGx[i][j].rgbtBlue = 0;

            CopyGy[i][j].rgbtRed = 0;
            CopyGy[i][j].rgbtGreen = 0;
            CopyGy[i][j].rgbtBlue = 0;
        }
    }

    // Initialize Gx and Gy arrays
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Calculate Gx and Gy values
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            for (int k = i - 1, m = 0; k < i + 2; k++, m++)
            {
                for (int l = j - 1, n = 0; l < j + 2; l++, n++)
                {
                    // Calculate Gx for each channel and write to CopyGx
                    CopyGx[i - 1][j - 1].rgbtRed = CopyGx[i - 1][j - 1].rgbtRed + copy1[k][l].rgbtRed * Gx[m][n];
                    CopyGx[i - 1][j - 1].rgbtGreen = CopyGx[i - 1][j - 1].rgbtGreen + copy1[k][l].rgbtGreen * Gx[m][n];
                    CopyGx[i - 1][j - 1].rgbtBlue = CopyGx[i - 1][j - 1].rgbtBlue + copy1[k][l].rgbtBlue * Gx[m][n];

                    // Calculate Gy for each channel and write to CopyGy
                    CopyGy[i - 1][j - 1].rgbtRed = CopyGy[i - 1][j - 1].rgbtRed + copy1[k][l].rgbtRed * Gy[m][n];
                    CopyGy[i - 1][j - 1].rgbtGreen = CopyGy[i - 1][j - 1].rgbtGreen + copy1[k][l].rgbtGreen * Gy[m][n];
                    CopyGy[i - 1][j - 1].rgbtBlue = CopyGy[i - 1][j - 1].rgbtBlue + copy1[k][l].rgbtBlue * Gy[m][n];
                }
            }
        }
    }

    // Calculate Sobel value and write to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int Red = round(sqrt(pow((double) CopyGx[i][j].rgbtRed, 2) + pow((double) CopyGy[i][j].rgbtRed, 2)));
            int Blue = round(sqrt(pow((double) CopyGx[i][j].rgbtGreen, 2) + pow((double) CopyGy[i][j].rgbtGreen, 2)));
            int Green = round(sqrt(pow((double) CopyGx[i][j].rgbtBlue, 2) + pow((double) CopyGy[i][j].rgbtBlue, 2)));

            if (Red > 255)
            {
                image[i][j].rgbtRed = 255;
            }

            else
            {
                image[i][j].rgbtRed = Red;
            }

            if (Green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

            else
            {
                image[i][j].rgbtGreen = Green;
            }

            if (Blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }

            else
            {
                image[i][j].rgbtBlue = Blue;
            }
        }
    }

    return;
}
