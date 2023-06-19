#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

// Grayscale image
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

int main(int argc, char *argv[])
{
    // Define allowable filters
    char *filters = "begr";

    // Get filter flag and check validity
    char filter = getopt(argc, argv, filters);
    if (filter == '?')
    {
        printf("Invalid filter.\n");
        return 1;
    }

    // Ensure only one filter
    if (getopt(argc, argv, filters) != -1)
    {
        printf("Only one filter allowed.\n");
        return 2;
    }

    // Ensure proper usage
    if (argc != optind + 2)
    {
        printf("Usage: ./filter [flag] infile outfile\n");
        return 3;
    }

    // Remember filenames
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Open input file
    // Minor edit, we set the read "r" to binary mode "rb".
    // References:
    // https://www.reddit.com/r/cs50/comments/eqxuw6/pset_4_filter_is_there_a_bug_in_original_cs50/
	// https://codereview.stackexchange.com/questions/249455/cs50-filtermore-comfortable-image-filters-in-c/249467#249467	
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // Open output file
    // Minor edit, we set the write "w" to binary mode "wb". Same as above.
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 6;
    }

    // Get image's dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // Allocate memory for image
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines
    for (int i = 0; i < height; i++)
    {
        // Read row into pixel array
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // Skip over padding
        fseek(inptr, padding, SEEK_CUR);
    }

    // Filter image
    switch (filter)
    {
        // Blur
        case 'b':
            blur(height, width, image);
            break;

        // Edges
        case 'e':
            edges(height, width, image);
            break;

        // Grayscale
        case 'g':
            grayscale(height, width, image);
            break;

        // Reflect
        case 'r':
            reflect(height, width, image);
            break;
    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixels to outfile
    for (int i = 0; i < height; i++)
    {
        // Write row to outfile
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Write padding at end of row
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free memory for image
    free(image);

    // Close files
    fclose(inptr);
    fclose(outptr);
    return 0;
}



// TODO BY STUDENT
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	// We'll go from top to bottom, left to right
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			//printf("AAAA");
			
			// Get the average of the three colors in the pixel, in Bytes, according to RGBTRIPLE struct in bmp.h
			// We round it in order to remove floating point numbers.
			float average_float = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtGreen) / 3;
			int average = round(average_float);
			
			// We'll set each of the RGB values to the average.
			image[i][j].rgbtRed = average;
			image[i][j].rgbtGreen = average;
			image[i][j].rgbtBlue = average;
		}
	}
	
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	for(int i = 0; i < height; i++)
	{
		// We'll only need to go up to half of the row. We don't need to touch the other half.
		for(int j = 0; j < width/2; j++)
		{
			
			// First, we put the left side pixel into a temporary variable, or a "cache" backup.
			int backup_red = image[i][j].rgbtRed;
			int backup_green = image[i][j].rgbtGreen;
			int backup_blue = image[i][j].rgbtBlue;
			
			// We'll then set each left side pixel to the color of the corresponding right side pixel.
			image[i][j].rgbtRed = image[i][width-j].rgbtRed;
			image[i][j].rgbtGreen = image[i][width-j].rgbtGreen;
			image[i][j].rgbtBlue = image[i][width-j].rgbtBlue;
			 
			// We then set the right side pixel to the original left side pixel, in order to successfully "Reflect" the image.
			image[i][width-j].rgbtRed = backup_red;
			image[i][width-j].rgbtGreen = backup_green;
			image[i][width-j].rgbtBlue = backup_blue;
			
			
		}
	}
	
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE surrounding_pixels[height][width];
	
	// We make a backup/cached referenced of the original values of each pixel.
	// This is so that we can take the average of the surrounding pixels and change the actual image safely.
	for(int i = 0; i < height; i++)
	{
		
		for(int j = 0; j < width; j++)
		{
			
			surrounding_pixels[i][j].rgbtRed = image[i][j].rgbtRed;
			surrounding_pixels[i][j].rgbtGreen = image[i][j].rgbtGreen;
			surrounding_pixels[i][j].rgbtBlue = image[i][j].rgbtBlue;
			
		}
	}
	
	
	for(int i = 0; i < height; i++)
	{
		
		for(int j = 0; j < width; j++)
		{
			int totalRed = 0;
			int totalGreen = 0;
			int totalBlue = 0;
			int count = -1;
			
			
			// Row 1
			// If the current height, i, is at the top, then this will be skipped
			// Example: i at 0 is 0-1 = -1 which is a height above the top row, of which does not exist.
			if(i-1 >= 0)
			{
				// This while loop is for the row of pixels at the index i height.
				// count is to have a dynamic variable and to serve as a counter for the loop.
				do
				{
					// If j + the current counter does is not at -1 AND does not exceed 399, then we count the RGB values of that pixel.
					if(j+count >= 0 && j+count < width)
					{
						totalRed += surrounding_pixels[i-1][j+count].rgbtRed;
						totalGreen += surrounding_pixels[i-1][j+count].rgbtGreen;
						totalBlue += surrounding_pixels[i-1][j+count].rgbtBlue;	
					}
					count++;
					
				}while(count!=2);		
			}
			count = -1;
			
			
			// Row 2
			// This row should always exist.
			do
			{	
				if(j+count >= 0 && j+count < width)
				{
					totalRed += surrounding_pixels[i][j+count].rgbtRed;
					totalGreen += surrounding_pixels[i][j+count].rgbtGreen;
					totalBlue += surrounding_pixels[i][j+count].rgbtBlue;	
				}
				count++;
					
			}while(count!=2);		
			count = -1;
			
			
			// Row 3
			// This is for the bottom of the row.
			// Our max index is at 399 so if the current height, i, is at the bottom, then this should be skipped.
			// Example: At i = 399, i+1 = 400, but row 400 does not exist in the array so this needs to be skipped.
			if(i+1 < height)
			{
				do
				{
					if(j+count >= 0 && j+count < width)
					{
						totalRed += surrounding_pixels[i+1][j+count].rgbtRed;
						totalGreen += surrounding_pixels[i+1][j+count].rgbtGreen;
						totalBlue += surrounding_pixels[i+1][j+count].rgbtBlue;	
					}
					count++;
					
				}while(count!=2);		
			}
			count = -1;
			
			
			int averageRed = round(totalRed/9);
			int averageGreen = round(totalGreen/9);
			int averageBlue = round(totalBlue/9);
			
			image[i][j].rgbtRed = averageRed;
			image[i][j].rgbtGreen = averageGreen;
			image[i][j].rgbtBlue = averageBlue;
		}
	}
	
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE surrounding_pixels[height][width];
	
	// We make a backup/cached referenced of the original values of each pixel.
	// This is so that we can take the average of the surrounding pixels and change the actual image safely.
	for(int i = 0; i < height; i++)
	{
		
		for(int j = 0; j < width; j++)
		{
			
			surrounding_pixels[i][j].rgbtRed = image[i][j].rgbtRed;
			surrounding_pixels[i][j].rgbtGreen = image[i][j].rgbtGreen;
			surrounding_pixels[i][j].rgbtBlue = image[i][j].rgbtBlue;
			
		}
	}
	
	
	for(int i = 0; i < height; i++)
	{
		
		for(int j = 0; j < width; j++)
		{
			// Gx values
			int totalRedGx = 0;
			int totalGreenGx = 0;
			int totalBlueGx = 0;
			// Gy values
			int totalRedGy = 0;
			int totalGreenGy = 0;
			int totalBlueGy = 0;
			
			int count = -1;
			
			
			// Row 1
			// If the current height, i, is at the top, then this will be skipped
			// Example: i at 0 is 0-1 = -1 which is a height above the top row, of which does not exist.
			if(i-1 >= 0)
			{
				// This while loop is for the row of pixels at the index i height.
				// count is to have a dynamic variable and to serve as a counter for the loop.
				do
				{
					// If j + the current counter does is not at -1 AND does not exceed 399, then we count the RGB values of that pixel.
					if(j+count >= 0 && j+count < width)
					{
						totalRedGx += surrounding_pixels[i-1][j+count].rgbtRed * count;
						totalGreenGx += surrounding_pixels[i-1][j+count].rgbtGreen * count;
						totalBlueGx += surrounding_pixels[i-1][j+count].rgbtBlue * count;
						
						if(count != 0)
						{			
							totalRedGy += surrounding_pixels[i-1][j+count].rgbtRed * -1;
							totalGreenGy += surrounding_pixels[i-1][j+count].rgbtGreen * -1;
							totalBlueGy += surrounding_pixels[i-1][j+count].rgbtBlue * -1;	
						}
						else
						{
							totalRedGy += surrounding_pixels[i-1][j+count].rgbtRed * -2;
							totalGreenGy += surrounding_pixels[i-1][j+count].rgbtGreen * -2;
							totalBlueGy += surrounding_pixels[i-1][j+count].rgbtBlue * -2;	
						}
					}
					count++;
					
				}while(count!=2);		
			}
			count = -1;
			
			
			// Row 2
			// This row should always exist.
			do
			{	
				if(j+count >= 0 && j+count < width)
				{

						totalRedGx += surrounding_pixels[i-1][j+count].rgbtRed * (count*2);
						totalGreenGx += surrounding_pixels[i-1][j+count].rgbtGreen * (count*2);
						totalBlueGx += surrounding_pixels[i-1][j+count].rgbtBlue * (count*2);
						
						totalRedGy += surrounding_pixels[i-1][j+count].rgbtRed * 0;
						totalGreenGy += surrounding_pixels[i-1][j+count].rgbtGreen * 0;
						totalBlueGy += surrounding_pixels[i-1][j+count].rgbtBlue * 0;	
						
				}
				count++;
					
			}while(count!=2);		
			count = -1;
			
			
			// Row 3
			// This is for the bottom of the row.
			// Our max index is at 399 so if the current height, i, is at the bottom, then this should be skipped.
			// Example: At i = 399, i+1 = 400, but row 400 does not exist in the array so this needs to be skipped.
			if(i+1 < height)
			{
				do
				{
					if(j+count >= 0 && j+count < width)
					{
						totalRedGx += surrounding_pixels[i-1][j+count].rgbtRed * count;
						totalGreenGx += surrounding_pixels[i-1][j+count].rgbtGreen * count;
						totalBlueGx += surrounding_pixels[i-1][j+count].rgbtBlue * count;
						
						if(count != 0)
						{			
							totalRedGy += surrounding_pixels[i-1][j+count].rgbtRed * 1;
							totalGreenGy += surrounding_pixels[i-1][j+count].rgbtGreen * 1;
							totalBlueGy += surrounding_pixels[i-1][j+count].rgbtBlue * 1;	
						}
						else
						{
							totalRedGy += surrounding_pixels[i-1][j+count].rgbtRed * 2;
							totalGreenGy += surrounding_pixels[i-1][j+count].rgbtGreen * 2;
							totalBlueGy += surrounding_pixels[i-1][j+count].rgbtBlue * 2;	
						}
					}
					count++;
					
				}while(count!=2);		
			}
			count = -1;
			
			
			int newRed = round(sqrt( (totalRedGx * totalRedGx) + (totalRedGy * totalRedGy) ));
				if(newRed > 255)
				{
					newRed = 255;
				}
			int newGreen = round(sqrt( (totalGreenGx * totalGreenGx) + (totalGreenGy * totalGreenGy) ));
				if(newGreen > 255)
				{
					newGreen = 255;
				}
			int newBlue = round(sqrt( (totalBlueGx * totalBlueGx) + (totalBlueGy * totalBlueGy) ));
				if(newBlue > 255)
				{
					newBlue = 255;
				}
				
			//int newRedGy;
			//int newGreenGy;
			//int newBlueGy;
	
			image[i][j].rgbtRed = newRed;
			image[i][j].rgbtGreen = newGreen;
			image[i][j].rgbtBlue = newBlue;
		}
	}
	
    return;
}
