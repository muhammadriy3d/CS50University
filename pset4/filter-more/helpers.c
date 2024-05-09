#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbGray;
    // For each height
    for (int i = 0; i < height; i++)
    {
        // For each width
        for (int j = 0; j < width; j++)
        {
            // Add gray filter
            rgbGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Update each of RBG COLORs
            image[i][j].rgbtBlue = rgbGray;
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtRed = rgbGray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[3];
    // For each height
    for (int i = 0; i < height; i++)
    {
        // For each width
        for (int j = 0; j < width / 2; j++)
        {
            // Configure the RBG COLORs
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;
            // Update the RBG
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtRed = temp[2];
        }
    }
    return;
}

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float c = 0;
    int sum = 0;

    for (int k = i - 1; k < (i + 2); k++)
    {
        for (int l = j - 1; l < (j + 2); l ++)
        {
            if (k < 0 || l < 0 || k >= height || l >= width)
            {
                continue;
            }
            if (color_position == 0)
            {
                sum += image[k][l].rgbtRed;
            }
            else if (color_position == 1)
            {
                sum += image[k][l].rgbtGreen;
            }
            else
            {
                sum += image[k][l].rgbtBlue;
            }
            c++;
        }
    }
    return round(sum / c);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // For each height
    for (int i = 0; i < height; i++)
    {
        // For each width
        for (int j = 0; j < width; j++)
        {
            // Copy the image
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // configure the image
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, 2);
        }
    }
    return;
}

int getSobelFilter(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float sumX = 0;
    float sumY = 0;

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int k = i - 1, x = 0; k < (i + 2); k++, x++)
    {
        for (int l = j - 1, y = 0; l < (j + 2); l++, y++)
        {
            if (k < 0 || l < 0 || k >= height || l >= width)
            {
                continue;
            }
            if (color_position == 0)
            {
                sumX += image[k][l].rgbtRed * gx[x][y];
                sumY += image[k][l].rgbtRed * gy[x][y];
            }
            else if (color_position == 1)
            {
                sumX += image[k][l].rgbtGreen * gx[x][y];
                sumY += image[k][l].rgbtGreen * gy[x][y];
            }
            else
            {
                sumX += image[k][l].rgbtBlue * gx[x][y];
                sumY += image[k][l].rgbtBlue * gy[x][y];
            }
        }
    }
    int result = round(sqrt((sumX * sumX) + (sumY * sumY)));
    return result < 255 ? result : 255;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = getSobelFilter(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = getSobelFilter(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = getSobelFilter(i, j, height, width, copy, 2);
        }
    }
    return;
}