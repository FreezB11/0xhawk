#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

bmp bmp_write(char *filename,char data[],int width,int height){
    //identify the file as a BMP
    char tag[] = {'B','M'};

     int header[] = {
        0x3a,                   // File size... update at the end.
        0, 0x36, 0x28,
        width, height,       // Image dimensions in pixels

        0x180001, 0, 0, 0x002e23, 0x002e23, 0, 0,
    };
    int file_size = 54 + 4 * width * height;

    header[0] = sizeof(tag) + sizeof(header) + file_size;

    FILE *file = fopen(filename,"w+");

    fwrite(&tag,sizeof(tag),1,file);
    fwrite(&header, sizeof(header), 1, file);
    
    // fwrite(&bitmap, sizeof(bitmap), 1, file);
    printf("%s\n",data);
    printf("%ld\n",sizeof(file_size));
    fwrite(*(&data),file_size,1,file);
    fclose(file);
}