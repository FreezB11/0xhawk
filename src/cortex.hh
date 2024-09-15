#pragma once
#include <iostream>

// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "calculas.hh"
#include "color.h"
#define int8 unsigned char
#define log(x) std::cout << x << std::endl;

template <typename T>
class matrix {
private:
    T** data;
    int rows, cols;
public:
    // Constructor
    matrix(int rows, int cols) : rows(rows), cols(cols) {
        // Allocate memory for row pointers
        data = new T*[rows];

        // Allocate memory for each row
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }

        // Initialize matrix elements (optional, setting them to zero)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = 0;
            }
        }
    }

    // Copy Constructor
    matrix(const matrix& other) : rows(other.rows), cols(other.cols) {
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Assignment Operator
    matrix& operator=(const matrix& other) {
        if (this == &other) return *this; // Handle self-assignment

        // Clean up the existing data
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;

        // Copy the new data
        rows = other.rows;
        cols = other.cols;
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    // Destructor
    ~matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Access elements
    T& at(int row, int col) {
        if (row >= rows || col >= cols || row < 0 || col < 0) {
            throw std::out_of_range("Index out of range");
        }
        return data[row][col];
    }

    // Getters for rows and columns
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // Display the matrix
    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

class ark{
private:
    int width, height, channels;
    matrix<int8> rchan,gchan,bchan;
    int8 *img;
public:
    ark(const char *filename): width(0), height(0), channels(0), rchan(0, 0), gchan(0,0), bchan(0,0){
        img = stbi_load(filename, &width,&height,&channels,4);
        rchan,gchan,bchan = matrix<int8>(width,height);
        if(img == NULL){
            log("Failed to load the image.")
        }
        log("Image loaded successfully")
    };
    ~ark(){
        stbi_image_free(img);
    };
};
