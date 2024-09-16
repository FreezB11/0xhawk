#include <iostream>
#include <vector>
#include <algorithm>
#include "../lpng1643/png.h"
#include <png.h>

using namespace std;

// Function to apply a 2D convolution
vector<vector<double>> conv2d(const vector<vector<double>> &input, const vector<vector<double>> &filter) {
    int filter_size = filter.size();
    int result_size = input.size() - filter_size + 1;
    vector<vector<double>> result(result_size, vector<double>(result_size, 0.0));

    for (int i = 0; i < result_size; ++i) {
        for (int j = 0; j < result_size; ++j) {
            double sum = 0.0;
            for (int m = 0; m < filter_size; ++m) {
                for (int n = 0; n < filter_size; ++n) {
                    sum += input[i + m][j + n] * filter[m][n];
                }
            }
            result[i][j] = sum;
        }
    }
    return result;
}

// Function to apply ReLU activation
vector<vector<double>> relu(const vector<vector<double>> &input) {
    vector<vector<double>> output = input;
    for (auto &row : output) {
        for (auto &val : row) {
            val = max(0.0, val);
        }
    }
    return output;
}

// Function to save image as PNG
void save_png(const vector<vector<double>> &image, const string &filename) {
    int height = image.size();
    int width = image[0].size();

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info = png_create_info_struct(png);
    if (setjmp(png_jmpbuf(png))) abort();

    FILE *fp = fopen(filename.c_str(), "wb");
    png_init_io(png, fp);

    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_GRAY,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    png_bytep row = (png_bytep) malloc(width * sizeof(png_byte));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            row[x] = static_cast<png_byte>(min(255.0, max(0.0, image[y][x])));
        }
        png_write_row(png, row);
    }

    png_write_end(png, nullptr);
    fclose(fp);

    if (png && info) png_destroy_write_struct(&png, &info);
    if (row) free(row);
}

int main() {
    // Sample 5x5 grayscale image
    vector<vector<double>> image = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };

    // Sharpening filter (Laplacian)
    vector<vector<double>> filter = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };

    // Apply convolution
    vector<vector<double>> conv_output = conv2d(image, filter);

    // Apply ReLU activation
    vector<vector<double>> relu_output = relu(conv_output);

    // Save the sharpened image as a PNG file
    save_png(relu_output, "sharpened_image.png");

    cout << "Image saved as sharpened_image.png" << endl;

    return 0;
}
