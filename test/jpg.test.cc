#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

struct Pixel {
    uint8_t value;
};

std::vector<std::vector<Pixel>> readJpeg(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    // Read the entire file into a buffer
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
    file.close();

    // Placeholder: you need to parse the JPEG file and extract pixel data here.
    // This is a complex process involving decoding steps mentioned earlier.

    // Example: Create a 160x160 grayscale image as a placeholder
    std::vector<std::vector<Pixel>> image(160, std::vector<Pixel>(160, {0}));

    return image;
}

int main() {
    std::string filename = "../train_data/Animal/dogs/2013-03-28_421268360524543050.jpg";
    std::vector<std::vector<Pixel>> image = readJpeg(filename);

    // Output the pixel values
    for (const auto& row : image) {
        for (const auto& pixel : row) {
            std::cout << (int)pixel.value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
