#include "helpers.h"
#include "math.h"
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            float redP = image[i][j].rgbtRed;
            float greenP = image[i][j].rgbtGreen;
            float blueP = image[i][j].rgbtBlue;
            int avg =  roundf((redP + greenP + blueP)/3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i < height; i++){
            for(int j= 0, k=(width-j-1); j<(width/2); j++, k--){

                RGBTRIPLE temp = image[i][k];
                image[i][k] = image[i][j];
                image[i][j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if(i == 0 && j == 0) {
                float redPix = (image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue);
                int avgRed = roundf(redPix/4);
                int avgGreen = roundf(greenPix/4);
                int avgBlue = roundf(bluePix/4);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
                //printf("corner\n");
            }
            else if (i==(height-1) && j == 0)
            {
                float redPix = (image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue);
                 int avgRed = roundf(redPix/4);
                int avgGreen = roundf(greenPix/4);
                int avgBlue = roundf(bluePix/4);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
                //printf("corner\n");
            } 
            else if  (i==0 && j==(width-1))
            {
                float redPix = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue);
              int avgRed = roundf(redPix/4);
                int avgGreen = roundf(greenPix/4);
                int avgBlue = roundf(bluePix/4);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
               // printf("corner\n");

            } 
            else if (i==(height-1) && j==(width-1))
            {
                float redPix = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue);
              int avgRed = roundf(redPix/4);
                int avgGreen = roundf(greenPix/4);
                int avgBlue = roundf(bluePix/4);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
                //printf("corner\n");
            }
        }
    }
        
        for (int j = 1; j < (width-1); j++){
            int i = 0; 
                float redPix = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j+1].rgbtRed + image[i+1][j].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j].rgbtBlue);
               int avgRed = roundf(redPix/6);
                int avgGreen = roundf(greenPix/6);
                int avgBlue = roundf(bluePix/6);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
 
        }
        
        for (int j = 1; j < (width-1); j++){
            int i = (height-1); 
                float redPix = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j+1].rgbtRed + image[i-1][j].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i-1][j].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i-1][j].rgbtBlue);
              int avgRed = roundf(redPix/6);
                int avgGreen = roundf(greenPix/6);
                int avgBlue = roundf(bluePix/6);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
        }
            
        for (int i = 1; i < (height-1); i++){
            int j = 0;
                float redPix = (image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue);
                int avgRed = roundf(redPix/6);
                int avgGreen = roundf(greenPix/6);
                int avgBlue = roundf(bluePix/6);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;

        }
        
            for (int i = 1; i < (height-1); i++){
            int j = (width-1);
                float redPix = (image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue);
              int avgRed = roundf(redPix/6);
                int avgGreen = roundf(greenPix/6);
                int avgBlue = roundf(bluePix/6);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;

        }
            
    
    //everything but the edges+corners
    for (int i = 1; i < (height-1); i++){
        for (int j = 1; j < (width-1); j++){
               float redPix = (image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed);
               float greenPix = (image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen);
               float bluePix = (image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue);
              int avgRed = roundf(redPix/9);
                int avgGreen = roundf(greenPix/9);
                int avgBlue = roundf(bluePix/9);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
        }
    }
 
       for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
                image[i][j] = image2[i][j];

        }
           
       } 
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if(i == 0 && j == 0) {
                int redPix = {{image[i][j].rgbtRed, image[i+1][j].rgbtRed, image[i][j+1].rgbtRed}, {image[i+1][j+1].rgbtRed, 0, 0}, {0, 0, 0}};
                int image2.rgbtRed = redPix * Gx;

                float greenPix = (image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen  + 0 + 0 + 0 + 0 + 0);
                float bluePix = (image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + 0 + 0 + 0 + 0 + 0);
                //printf("corner\n");
            }
            else if (i==(height-1) && j == 0)
            {
                float redPix = (image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue);
                 int avgRed = roundf(redPix/4);
                int avgGreen = roundf(greenPix/4);
                int avgBlue = roundf(bluePix/4);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
                //printf("corner\n");
            } 
            else if  (i==0 && j==(width-1))
            {
                float redPix = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue);
              int avgRed = roundf(redPix/4);
                int avgGreen = roundf(greenPix/4);
                int avgBlue = roundf(bluePix/4);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
               // printf("corner\n");

            } 
            else if (i==(height-1) && j==(width-1))
            {
                float redPix = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue);
              int avgRed = roundf(redPix/4);
                int avgGreen = roundf(greenPix/4);
                int avgBlue = roundf(bluePix/4);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
                //printf("corner\n");
            }
        }
    }
        
        for (int j = 1; j < (width-1); j++){
            int i = 0; 
                float redPix = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j+1].rgbtRed + image[i+1][j].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j].rgbtBlue);
               int avgRed = roundf(redPix/6);
                int avgGreen = roundf(greenPix/6);
                int avgBlue = roundf(bluePix/6);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
 
        }
        
        for (int j = 1; j < (width-1); j++){
            int i = (height-1); 
                float redPix = (image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j+1].rgbtRed + image[i-1][j].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i-1][j].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i-1][j].rgbtBlue);
              int avgRed = roundf(redPix/6);
                int avgGreen = roundf(greenPix/6);
                int avgBlue = roundf(bluePix/6);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
        }
            
        for (int i = 1; i < (height-1); i++){
            int j = 0;
                float redPix = (image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue);
                int avgRed = roundf(redPix/6);
                int avgGreen = roundf(greenPix/6);
                int avgBlue = roundf(bluePix/6);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;

        }
        
            for (int i = 1; i < (height-1); i++){
            int j = (width-1);
                float redPix = (image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed);
                float greenPix = (image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen);
                float bluePix = (image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue);
              int avgRed = roundf(redPix/6);
                int avgGreen = roundf(greenPix/6);
                int avgBlue = roundf(bluePix/6);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;

        }
            
    
    //everything but the edges+corners
    for (int i = 1; i < (height-1); i++){
        for (int j = 1; j < (width-1); j++){
               float redPix = (image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed);
               float greenPix = (image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen);
               float bluePix = (image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue);
              int avgRed = roundf(redPix/9);
                int avgGreen = roundf(greenPix/9);
                int avgBlue = roundf(bluePix/9);
                image2[i][j].rgbtRed=avgRed;
                image2[i][j].rgbtGreen = avgGreen;
                image2[i][j].rgbtBlue = avgBlue;
        }
    }
 
       for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
                image[i][j] = image2[i][j];

        }
           
       } 
    return;
}
