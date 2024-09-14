#pragma once
#include <iostream>

// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "matrix.hh"
#include "calculas.hh"
#include "color.h"
#define int8 unsigned char
#define log(x) std::cout << x << std::endl;

class ark{
private:
    int width, height, channels;
    int8 *img;
public:
    ark(const char *filename);
    ~ark();
};
