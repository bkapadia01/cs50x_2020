#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // request for hieght in interger value only
    do
    {
        height = get_int("Enter Height: ");
    }
    //check for int value is between 1 and 8
    while (height < 1 || height > 8);
    
    for (int i = 1; i <= height; i++)
    {
        //space before left stairs starts
        for (int k = height - i; k > 0; k--)
        {
            printf(" ");
        }
        // left stairs
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        //gap between stairs
        printf("  ");
        
        //right stairs
        for (int m = 1; m <= i; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}
