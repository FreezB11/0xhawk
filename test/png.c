#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define PNG_SIGNATURE_SIZE 8

const uint8_t png_signature[PNG_SIGNATURE_SIZE] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A
};

const uint8_t IEND[12] = {
    0x00,0x00,0x00,0x00,0x49,0x45,0x4e,0x44,0xae,0x42,0x60,0x82
};

// 00 00 00 00 49 45 4E 44 AE 42 60 82


int main () {

    FILE* fp;
    fp = fopen("out.png","ab");  

    fwrite(png_signature, 1, PNG_SIGNATURE_SIZE, fp);
    fwrite(IEND, 1, 12, fp);
    fclose(fp); 
    



    return 0;
}