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
            // Add rgb's filter for grayscale e.g: image[height pixles][width pixels] ..
            // round(); func is in math.h lib to fix some rounding issues
            rgbGray = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = rgbGray;
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtBlue = rgbGray;
        }
    }
    return;
}

// set RBG default pixels == 255
int max_rgb(int RGB)
{
    // If RBG is grater or less than the default decmial number
    if (RGB > 255)
    {
        // Set to 255
        RGB = 255;
    }
    return RGB;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Same as before but we need to configure each of the RGB
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;
    // For each height
    for (int i = 0; i < height; i++)
    {
        // For each width
        for (int j = 0; j < width; j++)
        {
            // configure the RGB colors to sepia
            sepiaBlue = max_rgb(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));
            sepiaGreen = max_rgb(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));
            sepiaRed = max_rgb(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));
            // add each color to rgbtCOLOR
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // make a temp
    int temp[3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[2] = image[i][j].rgbtRed;
            temp[1] = image[i][j].rgbtGreen;
            temp[0] = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = temp[2];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtBlue = temp[0];
        }
    }
    return;
}

int convBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float c = 0;
    int sum = 0;

    for (int x = i - 1; x < (i + 2); x++)
    {
        for (int y = j - 1; y < (j + 2); y ++)
        {
            if (x < 0 || y < 0 || x >= height || y >= width)
            {
                continue;
            }
            if (color_position == 0)
            {
                sum += image[x][y].rgbtRed;
            }
            else if (color_position == 1)
            {
                sum += image[x][y].rgbtGreen;
            }
            else
            {
                sum += image[x][y].rgbtBlue;
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
            image[i][j].rgbtRed = convBlur(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = convBlur(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = convBlur(i, j, height, width, copy, 2);
        }
    }
    return;
}
