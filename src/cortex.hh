#pragma once
#include <iostream>

// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "calculas.hh"
#include "color.h"
#define int8 unsigned char
#define log(x) std::cout << x << std::endl;

class ark{
private:
    int width, height, channels;
    int8 *img;
public:
    ark(const char *filename): width(0), height(0), channels(0){
        img = stbi_load(filename, &width,&height,&channels,4);
        if(img == NULL){
            log("Failed to load the image.")
        }
        log("Image loaded successfully")
    };
    // ~ark(){
    //     stbi_image_free(img);
    // };
};
/*
 ->5x5
0,0,0,0,0
0,0,0,0,0
0,0,0,0,0
0,0,0,0,0
0,0,0,0,0

*/