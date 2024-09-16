#ifndef ARK_H
#define ARK_H

#include "matrix.h"
#include <string>

class CNN {
public:
    // Load image and split into RGB matrices
    bool loadImage(const std::string& imagePath, Matrix& red, Matrix& green, Matrix& blue);
};

#endif // ARK_H
