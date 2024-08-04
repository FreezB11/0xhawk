#include <iostream>

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "../src/lib/stb_image.h"
}

int main()
{
    std::string filename = "../train_data/Animal/dogs/2013-03-28_421268360524543050.jpg";
    
    // ... x = width, y = height, n = # 8-bit components per pixel ...
    // ... replace '0' with '1'..'4' to force that many components per pixel
    // ... but 'n' will always be the number that it would have been if you said 0
    int x,y,n;
    unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 0);
    
    // ... process data if not NULL ..
    if (data != nullptr && x > 0 && y > 0)
    {
        if (n == 3)
        {
            
            std::cout << "First pixel: RGB "
                      << static_cast<int>(data[0]) << " "
                      << static_cast<int>(data[1]) << " "
                      << static_cast<int>(data[2]);
        }
        else if (n == 4)
        {
            std::cout << "First pixel: RGBA "
                      << static_cast<int>(data[0]) << " "
                      << static_cast<int>(data[1]) << " "
                      << static_cast<int>(data[2]) << " "
                      << static_cast<int>(data[3]) << '\n';
        }
    }
    else
    {
        std::cout << "Some error\n";
    }

    stbi_image_free(data);
}