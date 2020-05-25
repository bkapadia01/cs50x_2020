#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //ensure user enters 2 values 
    if (argc != 2)
    {
        printf("format: ./recover card.raw \n");
        return 1;
    }
    //open memory card
    //repeat until end of card
    //read 512byte into buffer
    //if start of new jpg
    //if first jpg - write first file
    //else close previous file and open new file
    //else 
    //if arlready found jpg - keep writing 
    
    //open memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }
    
    unsigned char buffer[512];
    char filename[10];
    int imgcount = 0;
    int counter = 0;
    FILE *img;

    while (fread(buffer, 512, 1, file) == 1)
    {

        if (counter == 0 && buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", imgcount);
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
            counter++;
        }
        else if (counter >= 1 && buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            fclose(img);
            imgcount++;
            sprintf(filename, "%03i.jpg", imgcount);
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
            counter++; 
        }
        else if (counter >= 1)
        {
            fwrite(buffer, 512, 1, img);
            counter++;
        }
    }
        
    
}
