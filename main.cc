#include <iostream>
#include "src/ark.h"
#include "src/matrix.h"

void printMatrix(const Matrix& matrix, const std::string& channelName) {
    std::cout << channelName << " Matrix:\n";
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            std::cout << matrix.data[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Helper function to print the DFT result
void printDFT(const std::vector<std::vector<std::complex<float>>>& dftMatrix, const std::string& channelName) {
    std::cout << channelName << " Frequency Matrix (Magnitude):\n";
    for (int i = 0; i < dftMatrix.size(); ++i) {
        for (int j = 0; j < dftMatrix[i].size(); ++j) {
            std::cout << std::abs(dftMatrix[i][j]) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    std::string imagePath = "girl.png";  // Replace with the path to your image file

    // Initialize CNN and matrices
    CNN cnn;
    Matrix red(0, 0), green(0, 0), blue(0, 0);

    // Load the image and split into RGB matrices
    if (cnn.loadImage(imagePath, red, green, blue)) {
        // Print the matrices
        // printMatrix(red, "Red");
        // printMatrix(green, "Green");
        // printMatrix(blue, "Blue");
        // Compute and print the DFT of each color channel
        auto redDFT = red.computeDFT();
        auto greenDFT = green.computeDFT();
        auto blueDFT = blue.computeDFT();

        // printDFT(redDFT, "Red");
        // printDFT(greenDFT, "Green");
        // printDFT(blueDFT, "Blue");

    } else {
        std::cerr << "Failed to load the image: " << imagePath << "\n";
    }

    return 0;
}
