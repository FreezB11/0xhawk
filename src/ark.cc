#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ark.h"

bool CNN::loadImage(const std::string& imagePath, Matrix& red, Matrix& green, Matrix& blue) {
    int width, height, channels;
    unsigned char* imgData = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
    
    if (!imgData) {
        return false;
    }

    // Initialize the matrices with the image dimensions
    red = Matrix(height, width);
    green = Matrix(height, width);
    blue = Matrix(height, width);

    // Fill the matrices with pixel data
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            red.at(y, x) = imgData[index] / 255.0f;        // Red channel
            green.at(y, x) = imgData[index + 1] / 255.0f;  // Green channel
            blue.at(y, x) = imgData[index + 2] / 255.0f;   // Blue channel
        }
    }

    stbi_image_free(imgData);
    return true;
}
